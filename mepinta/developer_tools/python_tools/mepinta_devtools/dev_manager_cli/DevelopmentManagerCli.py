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

class DevelopmentManagerCli(FrameworkBase):
  def __post_init__(self):
    self.shedskin_project_creator = ShedskinProjectCreator(self.context)
    self.backend_projects_creator = BackendProjectsCreator(self.context)
    self.mepinta_sdk_creator = MepintaSdkCreator(self.context)
    self.file_manager = FileManager(self.context)

  def _deployBackendProjects(self, sdk_path, libs_path, overwrite):
    projects_path = joinPath(self._getQtProjectsPath(), 'backend')
    for api in ('c', 'cpp'):
      backend_path = joinPath(projects_path, 'backend_api_%s' % api)
      self.file_manager.makedirs(backend_path, overwrite)
      self.backend_projects_creator.createProject(backend_path, api, sdk_path,
                                                  libs_path, overwrite)

  def _deployBuildShedskinModules(self, overwrite):
    project_path = joinPath(self._getDevPath(), 'build_shedksin_modules')
    self.shedskin_project_creator.createShedskinProject(project_path, overwrite)

  def _deploySdk(self, overwrite):
    sdk_path = joinPath(self._getDevPath(), 'sdk', 'c_and_cpp')
    self.file_manager.makedirs(sdk_path, overwrite)
    self.mepinta_sdk_creator.createProject(sdk_path, overwrite)
    return sdk_path

  def _delpoyLibsPath(self, overwrite):
    libs_path = joinPath(self._getDevPath(), 'libs')
    self.file_manager.makedirs(libs_path, overwrite)
    return libs_path

  def run(self):
    overwrite = True
#    overwrite = False
    self._testDeploymentSanity(overwrite)
    self._deployBuildShedskinModules(overwrite)
    sdk_path = self._deploySdk(overwrite)
    libs_path = self._delpoyLibsPath(overwrite)
    self._deployBackendProjects(sdk_path, libs_path, overwrite)
    #deploy shedskin
    #mepinta libraries projects
    #plugins projects
    #create waf script for building
    #deploy libargs load stand alone
    #deploy mepinta project (with

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
  DevelopmentManagerCli(context).run()

if __name__ == "__main__":
  smokeTestModule()
