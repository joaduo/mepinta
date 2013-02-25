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

class PluginsDeploymentManager(FrameworkBase):
  def __post_init__(self):
    self.file_manager = FileManager(self.context)

  def createDeployment(self, repo_path, deploy_name):
    # create deployment directory
    deploy_path = joinPath(repo_path, deploy_name)
    directories = ['python_path']
    packages = []
    if not self.file_manager.pathExists(deploy_path):
      self.file_manager.makedirs(deploy_path)

  def addPluginsSet(self, repo_path, deploy_name, plugins_set_name):
    pass  # TODO:

  def updateDataTypesIncludeDir(self, repo_path, deploy_name, submodule=None):
    pass  # TODO:


def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  test_module()
