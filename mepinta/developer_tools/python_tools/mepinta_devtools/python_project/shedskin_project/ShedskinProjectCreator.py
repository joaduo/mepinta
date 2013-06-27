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
from mepinta_devtools.python_project.PackageCreator import PackageCreator
from mepinta_devtools.ide_projects.FileManager import FileManager
from common.path import joinPath
from mepinta_devtools.templates.mappers.FileToFileMap import FileToFileMap

class ShedskinProjectCreator(FrameworkBase):
  def __post_init__(self):
    self.file_manager = FileManager(self.context)
    self.package_creator = PackageCreator(self.context)

  def __createBackendImplementationLinks(self):
    pass

  def __linkPipelineAndPipelineLoFacade(self, mepinta_package_path):
    pass

#  def __getProjectTemplates(self):
#    templates_config = [
#      FileToFileMap('build_pipeline_lo_facade.py', 'build_pipeline_lo_facade.py',),
#      FileToFileMap('clean_shedskin_cpp_code.py', 'clean_shedskin_cpp_code.py',),
#      #FileToFileMap('test_modules.py', 'test_modules.py',),
#    ]
#    return templates_config

  def createShedskinProject(self, project_src_path):
    #Create the mepinta package
    mepinta_package_path = joinPath(project_src_path, 'mepinta')
    self.package_creator.create(mepinta_package_path)
    #Link pipeline package and pipeline_lo_facade module
    self.__linkPipelineAndPipelineLoFacade(mepinta_package_path)
    #create mepinta folder
    #link pipeline folder and pipeline_lo_facade
    #linkear pipeline_backend/implementation/files_to_link
    #hacer .gitignore
    pass

def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  testModule()
