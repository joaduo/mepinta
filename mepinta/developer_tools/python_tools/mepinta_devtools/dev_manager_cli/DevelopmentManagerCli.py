# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo

This file is part of Mepinta.

Mepinta is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Mepinta is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Mepinta. If not, see <http://www.gnu.org/licenses/>.
'''
from common.abstract.FrameworkBase import FrameworkBase
from mepinta_devtools.python_project.shedskin_project.ShedskinProjectCreator import ShedskinProjectCreator
from common.path import joinPath
from mepinta_devtools.ide_projects.FileManager import FileManager
from mepinta_devtools.ide_projects.qtcreator.BackendProjectsCreator import BackendProjectsCreator
from mepinta.abstract.MepintaError import MepintaError
import os
import argparse
from mepinta_devtools.ide_projects.generic.MepintaSdkCreator import MepintaSdkCreator
from mepinta_devtools.templates.TemplateManager import TemplateManager
from mepinta_devtools.deployment.PythonPathManager import PythonPathManager
from common.PackageClassesInspector import PackageClassesInspector
from mepinta.plugins_manifest import PluginManifestBase

class DevelopmentManagerCli(FrameworkBase):
  def __post_init__(self):
    self.shedskin_project_creator = ShedskinProjectCreator(self.context)
    self.backend_projects_creator = BackendProjectsCreator(self.context)
    self.mepinta_sdk_creator = MepintaSdkCreator(self.context)
    self.file_manager = FileManager(self.context)
    self.templates = TemplateManager(self.context, path_ref=__file__)
    self.package_inspector = PackageClassesInspector(self.context)
    self.python_path = PythonPathManager()

  def _deployBuildShedskinModules(self, overwrite):
    project_path = joinPath(self._getDevPath(), 'build_shedksin_modules')
    creator = self.shedskin_project_creator
    return creator.createShedskinProject(project_path, overwrite)

  def _deploySdk(self, backend, overwrite):
    sdk_path = joinPath(self._getDevPath(), 'sdk', backend)
    self.file_manager.makedirs(sdk_path, overwrite)
    self.mepinta_sdk_creator.createProject(sdk_path, overwrite)
    return sdk_path

  def _createLibsPath(self, backend, overwrite):
    libs_path = joinPath(self._getDevPath(), 'libs', backend)
    self.file_manager.makedirs(libs_path, overwrite)
    return libs_path

  def _deployCandCppProjects(self, overwrite):
    backend = 'c_and_cpp'
    build_scripts = self._deployBuildShedskinModules(overwrite)
    sdk_path = self._deploySdk(backend, overwrite)
    libs_path = self._createLibsPath(backend, overwrite)
    creator = self.backend_projects_creator
    build_scripts += creator.deployProjects(self._getQtProjectsPath(),
                                           sdk_path, libs_path, overwrite)
    plugins_set = 'k3dv1'
    build_scripts += self._deployPluginSet(plugins_set, backend, sdk_path,
                                           overwrite)
    return build_scripts

  def run(self, overwrite=False):
    self._testDeploymentSanity(overwrite)
    build_scripts = self._deployCandCppProjects(overwrite)
    self._createMakeFile(build_scripts, overwrite)

  def _getPluginProjectCreator(self, plugins_set, backend):
    class_str = 'PluginProjectCreator'
    mod_str = 'plugins.{backend}.devtools.{plugins_set}.qtcreator.{class_str}'
    mod_str = mod_str.format(**locals())
    module = __import__(mod_str, fromlist='dummy')
    if hasattr(module, class_str):
      class_ = getattr(module, class_str)
      return class_(self.context)
    else:
      msg = 'Could not find class {class_str} in module {mod_str}'
      msg = msg.format(locals())
      raise MepintaError(msg)

  def _getPluginsManifests(self, backend):
    manifests = []
    for plugin_t in ('data_types', 'processors'):
      package_str = 'plugins.{backend}.{plugin_t}'.format(**locals())
      plugins = __import__(package_str, fromlist='dummy')
      plugins = reload(plugins)
      mod_dict = self.package_inspector.builDict(plugins, PluginManifestBase)
      manifests += mod_dict.values()
#    for i in manifests:
#      print i.__name__

#    manifests = [ m for m in manifests if not m.__name__.endswith('Base')]
    for i in sorted([i.__name__ for i in manifests]):
      print i
    raise RuntimeWarning()
    #return manifests

  def _deployPluginSet(self, plugins_set, backend, sdk_path, overwrite):
    #Append the set to the python path
    mepinta_source_path = self.context.deployment_config.mepinta_source_path
    self.python_path.appendPlugins(mepinta_source_path, plugins_set, backend)
    #select the plugin project creator
    build_scripts = []
    creator = self._getPluginProjectCreator(plugins_set, backend)
    plugins_path = joinPath(self._getDevPath(), 'plugins_build')
    for manifest in self._getPluginsManifests(backend):
      s = creator.createProject(self._getQtProjectsPath(), plugins_path,
                                 sdk_path, manifest, overwrite)
      build_scripts.extend(s)
    #remove the set to the python path
    self.python_path.removePlugins(mepinta_source_path, plugins_set, backend)
    return build_scripts

  def _createMakeFile(self, build_scripts, overwrite):
    dependencies = ''
    build_str = ''
    for i, script in enumerate(build_scripts):
      if script.endswith('.py'):
        build_str += 'script%s:\n\tpython %s\n\n' % (i, script)
      else:
        build_str += 'script%s:\n\t%s\n\n' % (i, script)
      dependencies += 'script%s ' % i
    file_name = 'Makefile'
    content = self.templates.getTemplate(file_name,
                                         DEPENDENCIES=dependencies,
                                         BUILD_SCRIPTS=build_str)
    path = joinPath(self._getDevPath(), file_name)
    self.file_manager.saveTextFile(path, content, overwrite)

  def _testDeploymentSanity(self, overwrite):
    path = self.context.deployment_config.deployment_path
    if not os.path.exists(path) and not overwrite:
      raise MepintaError('Deployment path does not exist: %r' % path)

  def _getDevPath(self):
    return joinPath(self.context.deployment_config.deployment_path, 'build')

  def _getQtProjectsPath(self):
    return joinPath(self._getDevPath(), 'QtProjects')

  def __getParser(self):
    description = 'Mepinta Development Manager Command Line Interface.'
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('command', type=str, help='Specify the dev command.')
    #parser.add_argument('demo_number', type=int, nargs='*',
    #help='Specify the demo number(s) you would like to run.')
    parser.add_argument('--debug', action='store_true',
                        help='Enable debug output.')
    return parser

def smokeTestModule():
  from common.log.debugPrint import debugPrint
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()
  DevelopmentManagerCli(context).run(overwrite=True)

if __name__ == "__main__":
  smokeTestModule()
