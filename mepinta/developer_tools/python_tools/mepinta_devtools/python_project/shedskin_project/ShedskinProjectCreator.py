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
import os

class ShedskinProjectCreator(FrameworkBase):
  def __post_init__(self):
    self.file_manager = FileManager(self.context)
    self.package_creator = PackageCreator(self.context)

  def __linkPipelineBackend(self, mepinta_source_path, project_path, force):
    #Create the new shedskin library path (external, cpp and hpp are fixed)
    external_lib_path = joinPath(project_path, 'shedskin_builtin_lib')
    self.file_manager.makedirs(external_lib_path)
    #Link the library to the source folder
    backend_src_path = joinPath(mepinta_source_path, 'core/pipeline_backend/pipeline_backend_c_and_cpp/pipeline_backend')
    backend_dst_path = joinPath(external_lib_path, 'pipeline_backend')
    self.file_manager.symlink(backend_src_path, backend_dst_path, force)
    #Link the includes for external lib
    external_lib_includes_dst = joinPath(external_lib_path, 'pipeline_backend_implementation')
    self.file_manager.makedirs(external_lib_includes_dst)
    external_lib_includes_src = joinPath(mepinta_source_path, 'backend/c_and_cpp/backend_api_c')
    files_to_link = self.file_manager.loadTextFile(joinPath(backend_src_path, 'implementation/files_to_link'))
    for basename in files_to_link.splitlines():
      self.file_manager.symlink(joinPath(external_lib_includes_src, basename), joinPath(external_lib_includes_dst, basename), force)

  def __linkPipelineAndPipelineLoFacade(self, mepinta_source_path, python_src_path, force):
    #Create the mepinta package (alone)
    mepinta_package_path = joinPath(python_src_path, 'mepinta')
    self.package_creator.createSimple(mepinta_package_path)
    #Link the pipeline package
    pipeline_pkg_src = joinPath(mepinta_source_path, 'core/python_core/mepinta/pipeline')
    pipeline_pkg_dst = joinPath(mepinta_package_path, 'pipeline')
    self.file_manager.symlink(pipeline_pkg_src, pipeline_pkg_dst, force)
    #Link pipeline_lo_facade.py so that its in the
    pipeline_lo_facade_dst = joinPath(python_src_path, 'pipeline_lo_facade.py')
    self.file_manager.symlink('mepinta/pipeline/lo/pipeline_lo_facade.py', pipeline_lo_facade_dst, force)

  def __linkLoadLibraryStandAlone(self, mepinta_source_path, python_src_path, force):
    load_library_dst = joinPath(python_src_path, 'load_library_stand_alone.py')
    self.file_manager.symlink('mepinta/pipeline/lo_cpp/python_src/load_library_stand_alone.py', load_library_dst, force)

  def __copyScripts(self, python_src_path):
    #Copy scripts necessary for building the pipeline_lo_facade.so shedskin module
    repo_path = joinPath(os.path.dirname(__file__), 'templates_repository')
    scripts_names = os.listdir(repo_path)
    self.file_manager.copyFiles(repo_path, python_src_path, scripts_names)

  def createShedskinProject(self, project_path, force=False):
    #Get the code source path
    mepinta_source_path = self.context.deployment_config.mepinta_source_path
    #Create the mepinta package
    python_src_path = joinPath(project_path, 'src')
    #Where all the python code goes
    self.file_manager.makedirs(python_src_path)
    #Link pipeline package and pipeline_lo_facade module
    self.__linkPipelineAndPipelineLoFacade(mepinta_source_path, python_src_path, force)
    #Link pipeline_backend stuff
    self.__linkPipelineBackend(mepinta_source_path, project_path, force)
    #Link the load_library_stand_alone
    self.__linkLoadLibraryStandAlone(mepinta_source_path, python_src_path, force)
    #Copy the scripts to generate the skedskin modules
    self.__copyScripts(python_src_path)

def testModule():
  pass

if __name__ == "__main__":
  testModule()
