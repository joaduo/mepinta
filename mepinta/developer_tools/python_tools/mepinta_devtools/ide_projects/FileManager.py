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
import os
import shutil
from common.path import joinPath

class FileManager(FrameworkBase):
  def listDir(self, path):
    return os.listdir(path)
  def symlink(self, src, dst, force=False):
    if self.pathExists(dst) and force:
      os.remove(dst)
    self.log.debug('linking %r to %r' % (dst, src))
    os.symlink(src, dst)
  def mkdir(self, path):
    os.mkdir(path)
  def makedirs(self, path):
    os.makedirs(path)
  def pathExists(self, path, package=False):
    if os.access(path, os.W_OK):
      if package and not os.access("%s/__init__.py" % path, os.W_OK):
        self.log.debug("The package path %r exist but there is no %r file." % (path, "%s/__init__.py" % path))
        return False
      self.log.debug("Exists %r" % path)
      return True
    self.log.debug("Doesn't exist %r" % path)
    return False
  def saveTextFile(self, path, content, overwrite):
    ''' '''
    self.log.debug('Writing %r with overwrite %s' % (path, overwrite))
    if not self.pathExists(path) or overwrite:
      target_file = open(path, 'w')
      target_file.write(content)
      target_file.close()
  def loadTextFile(self, path):
    fr = open(path, 'r')
    text = fr.read()
    fr.close()
    return text
  def copy(self, src, dst):
    shutil.copy(src, dst)
  def copyFiles(self, src_path, dst_path, file_names):
    for file_name in file_names:
      self.log.d('Copying %r to %r' % (joinPath(src_path, file_name), joinPath(dst_path, file_name)))
      self.copy(joinPath(src_path, file_name), joinPath(dst_path, file_name))

def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  testModule()
