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
    #self.context.log.debug("Exists: %r (writable)"%path)
    return True
  elif os.access(path, os.R_OK):
    #self.context.log.debug("Exists: %r  (readable)"%path)
    return True
  #self.context.log.debug("Doesn't exist: %r"%path)
  return False

def splitPath(path):
  return str(path).split(os.sep)

def joinPath(path, *path_list):
  if isinstance(path, list):
    path = os.sep.join(path)
  if len(path_list) != 0:
    for path_chunk in path_list:
      if isinstance(path,list):
        path = os.sep.join((path,joinPath(path_chunk)))
      else:
        path = os.sep.join((path,path_chunk))
  return path

#  new_path_list = []
#  for path in path_list:
#    if isinstance(path,list):
#      path = joinPath(path)
#    new_path_list.append(path)
#  return os.sep.join(new_path_list)

def conditionalPathJoin( str_list, split=False):
  if split:
    return str_list
  else:
    return os.sep.join(str_list)
  

        
if __name__ == "__main__":
  print pathHead('/path/to/file')
  print pathIsDir('/home/jduo')
  print pathIsDir('/home/jduo/output.k3d')
