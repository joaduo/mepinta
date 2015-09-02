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
import re


class FileManager(FrameworkBase):

    def listDir(self, path):
        return os.listdir(path)

    def symlink(self, src, dst, force=False):
        if self.pathExists(dst) and force:
            os.remove(dst)
        self.log.debug('linking %r to %r' % (dst, src))
        try:
            os.symlink(src, dst)
        except OSError as error:
            msg = str(error) + '. Dst %r' % dst
            raise OSError(msg)

    def mkdir(self, path, ignore_existing=False):
        if not (ignore_existing and os.path.exists(path) and os.path.isdir(path)):
            os.mkdir(path)

    def makedirs(self, path):
        if not (os.path.exists(path) and os.path.isdir(path)):
            os.makedirs(path)
        else:
            self.log.d('Ignoring %s' % path)

    def pathExists(self, path, package=False):
        if os.path.exists(path):  # os.access(path, os.W_OK):
            if package and not os.access("%s/__init__.py" % path, os.W_OK):
                self.log.d("The package path %r exist but there is no %r file." %
                           (path, "%s/__init__.py" % path))
                return False
            self.log.d("Exists %r" % path)
            return True
        self.log.d("Doesn't exist %r" % path)
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
            self.log.d('Copying %r to %r' % (joinPath(src_path, file_name),
                                             joinPath(dst_path, file_name)))
            self.copy(
                joinPath(src_path, file_name), joinPath(dst_path, file_name))

    def findFilesSplit(self, directory, pattern, followlinks=True):
        if isinstance(pattern, str):
            pattern = re.compile(pattern)
        for root, _, files in os.walk(directory, followlinks=True):
            for basename in files:
                if pattern.match(basename):
                    yield root, basename

    def findFilesRel(self, directory, pattern, followlinks=True):
        for root, basename in self.findFilesSplit(directory, pattern, followlinks):
            root = os.path.relpath(root, directory)
            if os.path.realpath(root) == os.path.realpath(os.path.curdir):
                yield basename
            else:
                yield joinPath(root, basename)

    def findFiles(self, directory, pattern, followlinks=True):
        for root, basename in self.findFilesSplit(directory, pattern, followlinks):
            yield joinPath(root, basename)


def testModule():
    from common.log.debugPrint import debugPrint
    from getDefaultContext import getDefaultContext
    context = getDefaultContext()
    fm = FileManager(context)
    fs = fm.findFilesRel('./eclipse/', '.*\.py')
    for f in fs:
        debugPrint(f)

if __name__ == "__main__":
    testModule()
