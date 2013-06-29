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
from mepinta_devtools.templates.DictionaryBasedTranslator import DictionaryBasedTranslator
from common.path import joinPath
import os

class DeploymentManager(FrameworkBase):
  def __post_init__(self):
    self.file_manager = FileManager(self.context)

  def __getConfigTemplate(self, template_name):
    template_path = joinPath(self.__getScriptsRepoPath(), template_name)
    template = self.file_manager.loadTextFile(template_path)
    return template

  def createDeploymentConfig(self, deployment_path, translation_dict, template_name='deployment_config.py', overwrite=False):
    file_path = joinPath(deployment_path, 'deployment_config.py')
    content = DictionaryBasedTranslator().getContent(self.__getConfigTemplate(template_name), translation_dict)
    self.file_manager.saveTextFile(file_path, content, overwrite)

  def __getScriptsRepoPath(self):
    return joinPath(os.path.dirname(__file__), 'scripts_repository')

  def copyScriptsTo(self, deployment_path):
    scripts_names = ['mepinta_demo.py', 'mepinta_tests.py', 'mepinta_dev.py']
    repo_path = self.__getScriptsRepoPath()
    self.file_manager.copyFiles(repo_path, deployment_path, scripts_names)


def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  testModule()
