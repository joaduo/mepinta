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

default_template = '''
class deployment_config(object):
  mepinta_source_path = '##MEPINTA_SOURCE_PATH'
  eclipse_projects_path = '##ECLIPSE_PROJECTS_PATH'
  qt_projects_path = '##QT_PROJECTS_PATH'
'''

class DeploymentConfigCreator(FrameworkBase):
  def __post_init__(self):
    self.file_manager = FileManager(self.context)
  def createDeploymentConfig(self, path, template=default_template, overwrite=False):
    content = ''
    self.file_manager.saveTextFile(path, content, overwrite)

def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  test_module()
