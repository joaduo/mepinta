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
from mepinta_devtools.templates.DictionaryBasedTranslator import DictionaryBasedTranslator

default_template = '''# -*- coding: utf-8 -*-
class deployment_config(object):
  mepinta_source_path = '${mepinta_source_path}'
  eclipse_projects_path = '${eclipse_projects_path}'
  qt_projects_path = '${qt_projects_path}'
  libk3dsdk_path = '${libk3dsdk_path}'
  libgsigc2_path = '${libgsigc2_path}'
  libboost_unit_test_framework_path = '${libboost_unit_test_framework_path}'

def configurePythonPaths(create_context=True):
  import sys
  config = deployment_config()
  sys.path.append(config.mepinta_source_path + '/developer_tools/python_tools')
  from mepinta_devtools.deployment.PythonPathManager import PythonPathManager
  PythonPathManager().appendAll(config.mepinta_source_path)
  from getDefaultContext import getDefaultContext
  if create_context:
    return getDefaultContext()

'''

class DeploymentConfigCreator(FrameworkBase):
  def __post_init__(self):
    self.file_manager = FileManager(self.context)

  def createDeploymentConfig(self, deployment_path, translation_dict, template=default_template, overwrite=False):
    file_path = joinPath(deployment_path, 'deployment_config.py')
    content = DictionaryBasedTranslator().getContent(template, translation_dict)
    self.file_manager.saveTextFile(file_path, content, overwrite)

def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  testModule()
