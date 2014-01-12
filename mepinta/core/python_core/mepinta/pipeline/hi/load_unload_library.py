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
from mepinta.abstract.MepintaError import MepintaError


def _getFunction(name, primitive_lib):
  lo_facade = 'mepinta.pipeline.lo_cpp.pipeline_lo_facade'
  if lo_facade in sys.modules and not primitive_lib:
    from mepinta.pipeline.lo_cpp.pipeline_lo_facade import FactoryLo
    mod = FactoryLo()
    return getattr(mod, name)
  elif primitive_lib:
    from mepinta.pipeline.lo_cpp.load_library_stand_alone import loadLibraryStandAlone
    if name == 'loadLibrary':
      return loadLibraryStandAlone
    else:
      raise NotImplementedError()
  else:
    msg = ('You can\'t load a non-primitive lib without pipeline_lo_facade '
           'module loaded. If it is a primitive lib mark it as such')
    raise MepintaError(msg)

#TODO: keep count with which module which library was loaded with
def loadLibrary(path, symbol, primitive_lib=False):
  return _getFunction('loadLibrary', primitive_lib)(path, symbol)

def unloadLibrary(path, primitive_lib=False):
  return _getFunction('unloadLibrary', primitive_lib)(path)

def smokeTestModule():
#  from getDefaultContext import getDefaultContext
#  context = getDefaultContext()
  raise RuntimeWarning('No smoke test')

if __name__ == "__main__":
  smokeTestModule()
