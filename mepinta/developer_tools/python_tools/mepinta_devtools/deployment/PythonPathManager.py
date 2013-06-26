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
import sys
import os

class PythonPathManager(object):
  def getPythonRelativePathsDict(self):
    relative_paths = {'mepinta':'core/python_core',
                  'mepinta_devtools':'developer_tools/python_tools',
                  'common':'libs/python/python_common',
                  'pipeline_backend': 'core/pipeline_backend/pipeline_backend_python',
                  }
    return relative_paths

  def getPluginsRelativePathsDict(self):
    relative_paths = {'demo':'plugins/python/demo/python_modules'}
    return relative_paths

  def appendAll(self, mepinta_source_path):
    self.appendMepintaPaths(mepinta_source_path)
    self.appendPluginsPath(mepinta_source_path)

  def appendMepintaPaths(self, mepinta_source_path):
    for path in self.getPythonRelativePathsDict().values():
      self.__appendPath(mepinta_source_path, path)

  def __appendPath(self, *args):
    sys.path.append(os.sep.join(args))

  def appendPluginsPath(self, mepinta_source_path, plugins_set='demo'):
    relative_paths = self.getPluginsRelativePathsDict()
    self.__appendPath(mepinta_source_path, relative_paths[plugins_set])

def test_module():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  test_module()
