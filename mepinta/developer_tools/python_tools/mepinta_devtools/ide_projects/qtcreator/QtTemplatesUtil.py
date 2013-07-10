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
from common.path import joinPath
from mepinta_devtools.ide_projects.FileManager import FileManager
import os

class QtTemplatesUtil(FrameworkBase):
  def __post_init__(self):
    self.file_manager = FileManager(self.context)

  def _getTemplatesRepoPath(self):
    return joinPath(os.path.dirname(__file__), 'templates_repository')

  def _getTemplateInRepo(self, templates_set, template_name):
    file_path = joinPath(self._getTemplatesRepoPath(), templates_set, template_name)
    fr = open(file_path, 'r')
    file_text = fr.read()
    fr.close()
    return file_text

  def _copyTemplatesInRepo(self, templates_set, templates_names, dst_dir_path):
    templates_set_path = joinPath(self._getTemplatesRepoPath(), templates_set)
    self.file_manager.copyFiles(templates_set_path, dst_dir_path, templates_names)

  def createLibProject(self, project_path, translation_dict):
    pass

def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  testModule()
