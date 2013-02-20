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
from common.path import joinPath, splitPath

class MepintaEclipseProjectCreator(FrameworkBase):
  def __post_init__(self):
    self.eclipse_project_creator = EclipseProjectCreator(self.context)
    self.file_manager = FileManager(self.context)

  def _getMepintaRoot(self):
    if self.__class__.__module__ == '__main__':
      import __main__
      package = __main__
    else:
      package = __import__(self.__class__.__module__, fromlist="dummy")
    return splitPath(package.__file__)[:-6]

  def _getAbsoluteSrcPath(self, relative_path):
    return joinPath(self._getMepintaRoot() + splitPath(relative_path))

  def _createPydevLinked(self, projects_dir, project_name, mepinta_src_dir):
    self.eclipse_project_creator.createPydev(projects_dir, project_name, create_src=False)
    dst = joinPath(projects_dir, project_name, 'src')
    self.file_manager.symlink(self._getAbsoluteSrcPath(mepinta_src_dir), dst)

  def createMepintaCoreProject(self, projects_dir):
    self._createPydevLinked(projects_dir, 'MepintaCore', 'core/python_core')

  def createMepintaCommonProject(self, projects_dir):
    self._createPydevLinked(projects_dir, 'MepintaCore', 'common_libs/python/common')

def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()
  mepc = MepintaEclipseProjectCreator(context)
  print mepc.__class__.__module__
  print "%r" % mepc.file_manager.__class__.__module__
  print type(mepc.file_manager.__class__.__module__)
  print mepc._getMepintaRoot()
  print mepc._getAbsoluteSrcPath('core/python_core')
  mepc.createMepintaCoreProject('/home/jduo/001-Mepinta/EclipseProjects_GitRepo/mepinta_test_folders/EclipseProjects')

if __name__ == "__main__":
  test_module()
