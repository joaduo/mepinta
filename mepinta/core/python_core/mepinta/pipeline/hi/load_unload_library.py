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


def _getFunction(name):
  lo_facade = 'mepinta.pipeline.lo_cpp.pipeline_lo_facade'
  if lo_facade in sys.modules:
    from mepinta.pipeline.lo.pipeline_lo_facade import FactoryLo
    mod = FactoryLo()
  else:
    from mepinta.pipeline.lo_cpp.load_library_stand_alone import loadLibraryStandAlone as mod
  return getattr(mod, name)

#TODO: keep count with which module which library was loaded with
def loadLibrary(path, symbol):
  return _getFunction('loadLibrary')(path, symbol)

def unloadLibrary(path):
  return _getFunction('loadLibrary')(path)

def smokeTestModule():
#  from getDefaultContext import getDefaultContext
#  context = getDefaultContext()
  raise RuntimeWarning('No smoke test')

if __name__ == "__main__":
  smokeTestModule()
