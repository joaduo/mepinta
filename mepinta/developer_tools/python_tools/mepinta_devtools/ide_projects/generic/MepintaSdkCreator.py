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
from mepinta_devtools.ide_projects.qtcreator.BackendProjectsCreator import BackendProjectsCreator

class MepintaSdkCreator(FrameworkBase):
  def __post_init__(self):
    self.backend_projects_creator = BackendProjectsCreator(self.context)
    self.file_manager = FileManager(self.context)

  def __getSourcesPath(self, api):
    return self.backend_projects_creator.getSourcesPath(api)

  def createProject(self, project_path, overwrite=False):
    #TODO: this is a hack, since there will be a link inside the source files
    #should be mepintasdk/c and mepintasdk/cpp but mepintasdk/c = mepintasdk now
    #make mepintasdk/ dir
    mepintasdk_path = joinPath(project_path, 'mepintasdk')
    #self.file_manager.mkdir(sdk_path, overwrite)
    api_c_path = self.__getSourcesPath('c')
    #link c directory
    self.file_manager.symlink(api_c_path, mepintasdk_path, overwrite)
    #link cpp directory
    api_cpp_path = self.__getSourcesPath('cpp')
    cpp_dst = joinPath(mepintasdk_path, 'cpp')
    self.file_manager.symlink(api_cpp_path, cpp_dst, force=True)


def smokeTestModule():
#  from getDefaultContext import getDefaultContext
#  context = getDefaultContext()
  raise RuntimeWarning('No smoke test')

if __name__ == "__main__":
  smokeTestModule()
