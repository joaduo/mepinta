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
import os
from common.path import joinPath
from ide_projects.eclipse.pydev_project.EclipsePydevProjectCreator import EclipsePydevProjectCreator

class EclipseCoreProjectCreator(EclipsePydevProjectCreator):
  '''
    Create a Eclipse Project for the Mepinta Python Core code given the path to place
    the project (could be the Eclipse workspace).
    Uses a template based creation.
  '''
  def _getMepintaCorePythonDir(self):
    return '/home/jduo/001-Mepinta/git/mepinta/mepinta/core/python_core'
  def _linkCodeDir(self, target_root):
    dst = joinPath(target_root, 'src')
    # if directory exists throughs an error
    if not self._pathExists(dst):
      os.symlink(self._getMepintaCorePythonDir(), dst)
    else:
      self.log.error("Directory %s already exists." % dst)
  def _createProjectDir(self, target_root):
    '''Create the project's new directory (and link src).'''
    if not self._pathExists(target_root):
      os.mkdir(target_root)

if __name__ == "__main__":
  pass
