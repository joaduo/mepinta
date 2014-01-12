# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

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
'''
This Module purpose is to load the libmepintacore.so library.
  (since mepinta_shedskin.so depends on this library, and then we have a chicken-egg
  problem if we would like to load the from pipeline_lo_facade.so)
This way avoids having to use mepinta_laucher to run the pipeline_lo_facade.so
module.

To compile this module with Shedskin the variable STAND_ALONE_LOAD_UNLOAD
should be defined. (so that logging isn't coupled with all libMepintaArgsApi.so)
g++ -D STAND_ALONE_LOAD_UNLOAD

'''

import sys
from pipeline_backend.load_unload_library.load_unload_library import loadLibrary

loaded_libraries = {}

def localLogInfo(msg):
  sys.stdout.write(msg + '\n')

def localLogError(msg):
  sys.stderr.write(msg + '\n')

def loadLibraryStandAlone(path, symbol):
  #TODO: unify with pipeline_lo_facade.FactoryLo
  if path in loaded_libraries:
    symbol = loaded_libraries[path][1]
    localLogInfo("Library at %r already loaded with symbol %r" % (path, symbol))
    return True
  handle = loadLibrary(path, symbol)
  if handle == None:
    localLogError("ERROR: Couldn't load the library at %r with symbol %r" % (path, symbol))
    return False
  loaded_libraries[path] = (handle, symbol)
  localLogInfo("Successfully loaded the library at %r with symbol %r" % (path, symbol))
  return True

def shedskin_load_library_stand_alone():
  loadLibraryStandAlone("", "")

if __name__ == "__main__":
  shedskin_load_library_stand_alone()
