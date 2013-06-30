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
import argparse
from mepinta_devtools.python_project.shedskin_project.ShedskinProjectCreator import ShedskinProjectCreator
from common.path import joinPath
from mepinta_devtools.ide_projects.FileManager import FileManager

class DevelopmentManagerCli(FrameworkBase):
  def __post_init__(self):
    self.shedskin_project_creator = ShedskinProjectCreator(self.context)
    self.file_manager = FileManager(self.context)

  def createShedskinProject(self, proj):
    pass

  def run(self):
    self.deployDevelopmentProjects()

  def deployDevelopmentProjects(self):
    dev_deployment_path = joinPath(self.context.deployment_config.deployment_path, 'build')
    shedskin_project_path = joinPath(dev_deployment_path, 'build_shedksin_modules')
    self.shedskin_project_creator.createShedskinProject(shedskin_project_path)
    #deploy shedskin
    #mepinta libraries projects
    #plugins projects
    #create waf script for building
    #deploy libargs load stand alone
    #deploy mepinta project (with

  def __createCAndCppPluginsProjects(self, dev_deployment_path, plugins_set):
    pass

  def __createBackendQtProjects(self, dev_deployment_path):
    qt_projects_path = joinPath(dev_deployment_path, 'QtProjects')
    backend_c_path = joinPath(qt_projects_path, 'backend/backend_api_c')
    backend_cpp_path = joinPath(qt_projects_path, 'backend/backend_api_cpp')
    for path in [qt_projects_path, backend_c_path, backend_cpp_path]:
      self.file_manager.makedirs(path)


  def __createQtBackendProjects(self):
    pass

  def __getParser(self):
    parser = argparse.ArgumentParser(description='Mepinta Development Manager Command Line Interface.')
    parser.add_argument('command', type=str, help='Specify the dev command.')
    #parser.add_argument('demo_number', type=int, nargs='*', help='Specify the demo number(s) you would like to run.')
    parser.add_argument('--debug', action='store_true', help='Enable debug output.')
    return parser

def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  testModule()
