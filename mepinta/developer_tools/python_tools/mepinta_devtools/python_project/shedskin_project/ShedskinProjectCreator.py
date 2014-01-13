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

  def __linkPipelineBackend(self, mepinta_source_path, project_path, overwrite):
    #Create the new shedskin library path (external, cpp and hpp are fixed)
    external_path = joinPath(project_path, 'shedskin_builtin_lib')
    self.file_manager.makedirs(external_path)
    #Link the library to the source folder
    backend_rel = ('core', 'pipeline_backend', 'pipeline_backend_c_and_cpp',
                   'pipeline_backend')
    backend_src = joinPath(mepinta_source_path, backend_rel)
    backend_dst = joinPath(external_path, 'pipeline_backend')
    self.file_manager.symlink(backend_src, backend_dst, overwrite)
    #Link the includes for external lib
    includes_dst = joinPath(external_path, 'pipeline_backend_implementation')
    self.file_manager.makedirs(includes_dst)
    includes_src = joinPath(mepinta_source_path, 'backend',
                                         'c_and_cpp', 'backend_api_c')
    list_path = joinPath(backend_src, 'implementation', 'files_to_link')
    files_list = self.file_manager.loadTextFile(list_path).splitlines()
    for basename in files_list:
      self.file_manager.symlink(joinPath(includes_src, basename),
                                joinPath(includes_dst, basename),
                                overwrite)

  def __linkPipelineAndPipelineLoFacade(self, mepinta_source_path, python_src_path, overwrite):
    #Create the mepinta package (alone)
    package_path = joinPath(python_src_path, 'mepinta')
    self.package_creator.createSimple(package_path, overwrite)
    #Link the pipeline package
    package_src = joinPath(mepinta_source_path, 'core', 'python_core',
                           'mepinta', 'pipeline')
    package_dst = joinPath(package_path, 'pipeline')
    self.file_manager.symlink(package_src, package_dst, overwrite)
    #Link pipeline_lo_facade.py so that its in the
    facade_src = joinPath('mepinta', 'pipeline', 'lo', 'pipeline_lo_facade.py')
    facade_dst = joinPath(python_src_path, 'pipeline_lo_facade.py')
    self.file_manager.symlink(facade_src, facade_dst, overwrite)

  def __linkLoadLibraryStandAlone(self, mepinta_source_path, python_src_path, overwrite):
    load_dst = joinPath(python_src_path, 'load_library_stand_alone.py')
    load_src = joinPath('mepinta', 'pipeline', 'lo', 'load_library_stand_alone.py')
    self.file_manager.symlink(load_src, load_dst, overwrite)

  def __copyScripts(self, python_src_path):
    #Copy scripts necessary for building the pipeline_lo_facade.so shedskin module
    repo_path = joinPath(os.path.dirname(__file__), 'templates_repository')
    scripts_names = os.listdir(repo_path)
    self.file_manager.copyFiles(repo_path, python_src_path, scripts_names)
    mk_cmds = [s for s in scripts_names if 'build' in s and
                                                  not 'common' in s]
    def strip(s):
      if s.endswith('.py'): return s[:-len('.py')]
      else: return s
    mk_targets = [(strip(s), joinPath(python_src_path, s)) for s in mk_cmds]
    return mk_targets

  def createProject(self, project_path, overwrite=False):
    #Get the code source path
    mepinta_source_path = self.context.deployment_config.mepinta_source_path
    #Create the mepinta package
    python_src_path = joinPath(project_path, 'src')
    #Where all the python code goes
    self.file_manager.makedirs(python_src_path)
    #Link pipeline package and pipeline_lo_facade module
    self.__linkPipelineAndPipelineLoFacade(mepinta_source_path, python_src_path, overwrite)
    #Link pipeline_backend stuff
    self.__linkPipelineBackend(mepinta_source_path, project_path, overwrite)
    #Link the load_library_stand_alone
    self.__linkLoadLibraryStandAlone(mepinta_source_path, python_src_path, overwrite)
    #Copy the scripts to generate the skedskin modules
    mk_targets = self.__copyScripts(python_src_path)
    #return the build scripts
    return mk_targets

def testModule():
  pass

if __name__ == "__main__":
  testModule()
