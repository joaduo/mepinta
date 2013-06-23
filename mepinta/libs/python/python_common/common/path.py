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
import time

def getPackagePath(package):
  if isinstance(package, str):
    package = __import__(package, fromlist="dummy")
  return package.__path__[0]

def getObjectModulePath(instace):
  if instace.__class__.__module__ == '__main__':
    import __main__
    module = __main__
  else:
    module = __import__(instace.__class__.__module__, fromlist="dummy")
  return module.__file__

def realPath(path, retry=True):
  try:
    return os.path.realpath(path)
  except Exception as e:
    if retry:
      time.sleep(0.1)
      return os.path.realpath(path)
    else:
      raise e

def pathIsDir(path):
  return os.path.isdir(path)

def pathHead(path):
  return os.path.split(path)[0]

def pathExists(path, write=False):
  if write and os.access(path, os.W_OK):
    # self.log.debug("Exists: %r (writable)"%path)
    return True
  elif os.access(path, os.R_OK):
    # self.log.debug("Exists: %r  (readable)"%path)
    return True
  # self.log.debug("Doesn't exist: %r"%path)
  return False

def splitPath(path, *path_list):
  split_path = []
  if isinstance(path, list) or isinstance(path, tuple):
    for p in path:
      split_path += splitPath(p)
  else:
    split_path += str(path).split(os.sep)
  if len(path_list) > 0:
    split_path += splitPath(path_list)
  return split_path

def joinPath(path, *path_list):
  if isinstance(path, list) or isinstance(path, tuple):
    joint_path = os.sep.join(map(joinPath, path))
  else:
    joint_path = path
  if len(path_list) > 1:
    joint_path = joinPath(joint_path, joinPath(path_list))
  elif len(path_list) == 1:
    joint_path = os.sep.join((joint_path, joinPath(path_list[0])))
  return joint_path

def conditionalPathJoin(str_list, split=False): #TODO: remove this?
  if split:
    return str_list
  else:
    return os.sep.join(str_list)

if __name__ == "__main__":
  debugPrint(pathHead('/path/to/file'))
  debugPrint(pathIsDir('/home/jduo'))
  debugPrint(pathIsDir('/home/jduo/output.k3d'))
