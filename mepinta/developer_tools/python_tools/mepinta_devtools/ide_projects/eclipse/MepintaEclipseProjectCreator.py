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
from mepinta_devtools.ide_projects.eclipse.EclipseProjectCreator import EclipseProjectCreator
from mepinta_devtools.ide_projects.FileManager import FileManager
from common.path import joinPath, splitPath, getObjectModulePath
from mepinta_devtools.templates.mappers.FileToFileMap import FileToFileMap

class MepintaEclipseProjectCreator(FrameworkBase):
  def __post_init__(self):
    self.ep_creator = EclipseProjectCreator(self.context)
    self.file_manager = FileManager(self.context)

  def _getMepintaRoot(self):
    return splitPath(getObjectModulePath(self))[:-6]

  def _getAbsoluteSrcPath(self, relative_path):
    return joinPath(self._getMepintaRoot() + splitPath(relative_path))

  def _createPydevLinked(self, projects_dir, project_name, mepinta_src_dir):
    self.ep_creator.createPydev(projects_dir, project_name, create_src=False)
    dst = joinPath(projects_dir, project_name, 'src')
    self.file_manager.symlink(self._getAbsoluteSrcPath(mepinta_src_dir), dst)

  def createMepintaCoreProject(self, projects_dir):
    mepinta_core_path = 'core/python_core'
    self._createPydevLinked(projects_dir, 'MepintaCorePythonBackend', mepinta_core_path)
    # self._createPydevLinked(projects_dir, 'MepintaCoreCPPBackend', mepinta_core_path)
    # TODO: _mepintaShedskinReal (link dirs, link files
    # TODO: _mepintaShedskinDummy

  def createMepintaCommonProject(self, projects_dir):
    self._createPydevLinked(projects_dir, 'MepintaCommon', 'common_libs/python/common')

  def _createCDTLinked(self, projects_dir, project_name, mepinta_src_dir):
    templates_config = [FileToFileMap('cproject.xml', '.cproject')]
    self.ep_creator.createCDT(projects_dir, project_name, templates_config=templates_config, create_src=False)
    dst = joinPath(projects_dir, project_name, 'src')
    self.file_manager.symlink(self._getAbsoluteSrcPath(mepinta_src_dir), dst)

  def createMepintaArgsApiCProject(self, projects_dir):
    self._createCDTLinked(projects_dir, 'MepintaBackendApiC', 'backend/c_and_cpp/backend_api_c')

  def createMepintaArgsApiCPPProject(self, projects_dir):
    self._createCDTLinked(projects_dir, 'MepintaBackendApiCPP', 'backend/c_and_cpp/backend_api_cpp')

  def createPluginsRepoProject(self, projects_dir):
    pass  # TODO: #return repo dir

  def createPluginDataTypeIncludesProject(self, projects_dir):
    pass  # TOOD:

def test_module():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()
  mepc = MepintaEclipseProjectCreator(context)
  #  print mepc.__class__.__module__
  #  print "%r" % mepc.file_manager.__class__.__module__
  #  print type(mepc.file_manager.__class__.__module__)
  #  print mepc._getMepintaRoot()
  #  print mepc._getAbsoluteSrcPath('core/python_core')
  projects_dir = '/home/jduo/001-Mepinta/EclipseProjects_GitRepo/mepinta_test_folders/EclipseProjects'
  mepc.createMepintaCoreProject(projects_dir)
  mepc.createMepintaCommonProject(projects_dir)
  mepc.createMepintaArgsApiCProject(projects_dir)
  mepc.createMepintaArgsApiCPPProject(projects_dir)

if __name__ == "__main__":
  test_module()
