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
from mepinta_devtools.ide_projects.FileManager import FileManager
from mepinta_devtools.ide_projects.qtcreator.BackendProjectsCreator import BackendProjectsCreator
from mepinta.abstract.MepintaError import MepintaError
from mepinta_devtools.ide_projects.generic.MepintaCppSdkCreator import MepintaCppSdkCreator
from mepinta_devtools.templates.TemplateManager import TemplateManager
from mepinta_devtools.deployment.PythonPathManager import PythonPathManager
from mepinta_devtools.plugins.PluginsBrowser import PluginsBrowser
from common.path import joinPath
import os
import argparse
from mepinta_devtools.ide_projects.qtcreator.QtProjectPluginCreator import QtProjectPluginCreatorBase

class DevelopmentManagerCli(FrameworkBase):
  def __post_init__(self):
    self.shedskin_project_creator = ShedskinProjectCreator(self.context)
    self.backend_projects_creator = BackendProjectsCreator(self.context)
    self.mepinta_sdk_creator = MepintaCppSdkCreator(self.context)
    self.file_manager = FileManager(self.context)
    self.templates = TemplateManager(self.context, path_ref=__file__)
    self.plugins_browser = PluginsBrowser(self.context)
    self.python_path = PythonPathManager()

  def _deployBuildShedskinModules(self, overwrite):
    ''' Deploy python projects to build shedskin modules
    (pipeline_lo and load_library)
    '''
    project_path = joinPath(self._getBuildPath(), 'shedksin_modules_build')
    creator = self.shedskin_project_creator
    return creator.createShedskinProject(project_path, overwrite)

  def _deploySdk(self, backend, overwrite):
    ''' Create the sdk path with the headers to include.
    Algo in that folder go the data_types, but they are created by plugins_set
    basis.
    '''
    sdk_path = joinPath(self._getBuildPath(), 'sdk', backend)
    self.file_manager.makedirs(sdk_path)
    self.mepinta_sdk_creator.createProject(sdk_path, overwrite)
    return sdk_path

  def _createLibsPath(self, backend, overwrite):
    '''Create the directory where the common libs will be stored.
    Libs needed to start up mepinta. Mepinta core libs specially.
    (but not support libs)
    '''
    libs_path = joinPath(self._getBuildPath(), 'libs', backend)
    self.file_manager.makedirs(libs_path)
    return libs_path

  def _deployCandCppProjects(self, overwrite):
    '''Deploy projects related with the c_and_cpp backend.
        -shedskin modules
        -backend core libraries (c and cpp)
        -sdk path (link to sdk sources)
        -all c_and_cpp plugins
    '''
    backend = 'c_and_cpp'
    make = {}
    make['shedskin'] = self._deployBuildShedskinModules(overwrite)
    sdk_path = self._deploySdk(backend, overwrite)
    libs_path = self._createLibsPath(backend, overwrite)
    creator = self.backend_projects_creator
    make['backend'] = creator.deployProjects(self._getQtProjectsPath(),
                                             sdk_path, libs_path, overwrite)
    plugins_sets = ['k3dv1', 'basic']
    mepinta_source_path = self.context.deployment_config.mepinta_source_path
    for plugins_set in plugins_sets:
      #Append the set to the python path
      self.python_path.appendPlugins(mepinta_source_path, plugins_set, backend)
      target = 'plugins_' + plugins_set
      make[target] = self._deployPluginSet(plugins_set, backend, sdk_path,
                                         overwrite)
      #remove the set to the python path
      self.python_path.removePlugins(mepinta_source_path, plugins_set, backend)
    return make

  def run(self, overwrite=False):
    self._testDeploymentSanity(overwrite)
    make = self._deployCandCppProjects(overwrite)
    self._createMakeFile(make, overwrite)

  def _getPluginProjectCreator(self, plugins_set, backend):
    '''Get the project creator for a plugins_set.
    So each plugins_set can manage the building
    '''
    class_str = 'PluginProjectCreator'
    mod_str = 'plugins.{backend}.devtools.{plugins_set}.qtcreator.{class_str}'
    mod_str = mod_str.format(**locals())
    try:
      module = __import__(mod_str, fromlist='dummy')
      if hasattr(module, class_str):
        class_ = getattr(module, class_str)
        return class_(self.context)
      else:
        msg = 'Could not find class {class_str} in module {mod_str}'
        msg = msg.format(**locals())
        raise MepintaError(msg)
    except ImportError:
      return QtProjectPluginCreatorBase(self.context)


  def _deployPluginSet(self, plugins_set, backend, sdk_path, overwrite):
    '''Deploy all plugins projects for a certain plugins_set'''
    #select the plugin project creator
    mk_cmds = []
    creator = self._getPluginProjectCreator(plugins_set, backend)
    plugins_path = joinPath(self._getBuildPath(), 'plugins_build')
    for plugin_type in ('data_types', 'processors'):
      projects_path = joinPath(self._getQtProjectsPath(), plugins_set)
      manifests = self.plugins_browser.getManifests(plugins_set, backend,
                                                    plugin_type)
      for manifest in manifests:
        manifest = manifest(self.context)
        if not hasattr(manifest, 'build') or manifest.build:
          s = creator.createProject(projects_path, plugins_path,
                                     sdk_path, manifest, overwrite)
          mk_cmds.extend(s)
    self.mepinta_sdk_creator.createDataTypesInclude(sdk_path, plugins_set,
                                                    overwrite)
    return mk_cmds

  def __createSubMakefile(self, name, mk_targets):
    dep_str = ' '
    make_str = ''
    for target, mk_cmd in sorted(mk_targets):
      if mk_cmd.endswith('.py'):
        mk_cmd = 'python %s' % mk_cmd
      make_str += '%s:\n\t@%s\n\n' % (target, mk_cmd)
      dep_str += '%s ' % target
    return make_str, dep_str

  def _createMakeFile(self, make, overwrite):
    '''Create the Makefile from the building scripts
    :param make: dictionary of building scripts
    :param overwrite: overwrite existing scripts
    '''
    dep_str = ''
    mk_str = ''
    for name in sorted(make.keys()):
      mk_targets = make[name]
      #all dep
      dep_str += '%s ' % name
      mk, dep = self.__createSubMakefile(name, mk_targets)
      mk_str += '%s: %s\n\n' % (name, dep)
      mk_str += mk
    file_name = 'Makefile'
    content = self.templates.getTemplate(file_name,
                                         DEPENDENCIES=dep_str,
                                         BUILD_SCRIPTS=mk_str)
    path = joinPath(self._getBuildPath(), file_name)
    self.file_manager.saveTextFile(path, content, overwrite)

  def _testDeploymentSanity(self, overwrite):
    '''Check that the deployment directory exists'''
    path = self.context.deployment_config.deployment_path
    if not os.path.exists(path) and not overwrite:
      raise MepintaError('Deployment path does not exist: %r' % path)

  def _getBuildPath(self):
    '''Get the build path of all mepinta deployment'''
    return joinPath(self.context.deployment_config.deployment_path, 'build')

  def _getQtProjectsPath(self):
    '''Get the Qt Projects of the deployment'''
    return joinPath(self._getBuildPath(), 'QtProjects')

  def __getParser(self):
    '''Get the command arguments parser of the CLI development manager'''
    description = 'Mepinta Development Manager Command Line Interface.'
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('command', type=str, help='Specify the dev command.')
    #parser.add_argument('demo_number', type=int, nargs='*',
    #help='Specify the demo number(s) you would like to run.')
    parser.add_argument('--debug', action='store_true',
                        help='Enable debug output.')
    return parser

def smokeTestModule():
#  from common.log.debugPrint import debugPrint
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()
  DevelopmentManagerCli(context).run(overwrite=False)

if __name__ == "__main__":
  smokeTestModule()
