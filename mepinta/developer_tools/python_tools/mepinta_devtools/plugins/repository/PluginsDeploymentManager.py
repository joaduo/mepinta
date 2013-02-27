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
from mepinta_devtools.ide_projects.FileManager import FileManager
from common.path import joinPath
from mepinta_devtools.python_project.ModuleCreator import ModuleCreator
from mepinta_devtools.python_project.PackageCreator import PackageCreator

class PluginsDeploymentManager(FrameworkBase):
  def __post_init__(self):
    self.file_manager = FileManager(self.context)
    self.module_creator = ModuleCreator(self.context)
    self.package_creator = PackageCreator(self.context)

  def createDeployment(self, deploy_path, force=False):
    # Check if already created
    if self.file_manager.pathExists(deploy_path) and not force:
      self.log.warning('This deployment already exists, skipping creation')
      return
    # Create deployment directory
    self.file_manager.makedirs(deploy_path)
    # Create subdirs
    plugins_dir = 'python_modules/plugins'
    for direc in [plugins_dir, 'libs', 'data_types_include']:
      self.file_manager.makedirs(joinPath(deploy_path, direc))
    # Create first package
    base_package_path = joinPath(deploy_path, plugins_dir)
    self.module_creator.create(joinPath(base_package_path, '__init__.py'))
    # Create other packages
    backends = ['c_and_cpp', 'python']  # TODO: get from context
    python_packages = ['%s.data_types',
                       '%s.processors']
    # Create packages for plugins modules
    for backend in backends:
      for package in python_packages:
        self.package_creator.create(joinPath(base_package_path, (package % backend).split('.')))

  def addPluginsSet(self, deploy_path, repo_path, backend_language, plugins_set_name):
    ''' Links data_types and processors packages from a plugins' set to a specific deployment.'''
    plugins_types = ['data_types', 'processors']
    for p_type in plugins_types:
      sub_path = 'python_modules/plugins/%s/%s' % (backend_language, p_type)
      plugins_path = joinPath(repo_path, backend_language, plugins_set_name, sub_path)
      for package_name in self.file_manager.listDir(plugins_path):
        package_path = joinPath(plugins_path, package_name)
        if self.file_manager.pathExists(package_path, package=True):
          dst_package_path = joinPath(deploy_path, sub_path, package_name)
          self.file_manager.symlink(package_path, dst_package_path)

  def createCompiledDirectories(self, deploy_path, plugins_manifests):
    for p_manifest in plugins_manifests:
      path = joinPath(deploy_path, 'python_modules', p_manifest.__module__.split('.'))
      path = '%s_compiled' % path
      self.file_manager.mkdir(path)

  def updateDataTypesIncludeDir(self, deploy_path, submodule=None):
    pass  # TODO: need to have better data_types manifest


def test_module():
  from default_context import getDefaultContext
  from pipeline_backend.logging.logging import LOG_INFO
  from mepinta_devtools.plugins.PluginsBrowser import PluginsBrowser
  context = getDefaultContext(LOG_INFO)
  pdm = PluginsDeploymentManager(context)
  deploy_path = '/home/jduo/001-Mepinta/EclipseProjects_GitRepo/mepinta_test_folders/EclipseProjects/K3dv1DeployTest'
  pdm.createDeployment(deploy_path, force=False)
  repo_path = '/home/jduo/001-Mepinta/git/mepinta/mepinta/plugins'
  pdm.addPluginsSet(deploy_path, repo_path, backend_language='c_and_cpp', plugins_set_name='k3dv1')
  import plugins.c_and_cpp as plugins_package
  plugins_manifests = PluginsBrowser(context).getAllManifests(plugins_package)
  pdm.createCompiledDirectories(deploy_path, plugins_manifests)


if __name__ == "__main__":
  test_module()
