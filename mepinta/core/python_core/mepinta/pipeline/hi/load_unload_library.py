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

path_mod = {}


def _getCachedFunction(path, name, primitive_lib):
    if path not in path_mod:
        path_mod[path] = _getFunction(name, primitive_lib)
    mod, name = path_mod[path]
    return getattr(mod, name)


def _getFunction(name, primitive_lib):
    lo_facade = 'mepinta.pipeline.lo_cpp.pipeline_lo_facade'
    if lo_facade in sys.modules and not primitive_lib:
        from mepinta.pipeline.lo_cpp.pipeline_lo_facade import FactoryLo
        mod = FactoryLo()
    elif primitive_lib:
        import mepinta.pipeline.lo_cpp.load_library_stand_alone as mod
        name += 'StandAlone'
    else:
        msg = ('You can\'t load a non-primitive lib without pipeline_lo_facade '
               'module loaded. If it is a primitive lib mark it as such')
        raise MepintaError(msg)
    return mod, name


def loadLibrary(path, symbol, primitive_lib=False):
    function = _getCachedFunction(path, 'loadLibrary', primitive_lib)
    return function(path, symbol)


def unloadLibrary(path, primitive_lib=False):
    function = _getCachedFunction(path, 'unloadLibrary', primitive_lib)
    return function(path)


def smokeTestModule():
    #  from getDefaultContext import getDefaultContext
    #  context = getDefaultContext()
    raise RuntimeWarning('No smoke test')

if __name__ == "__main__":
    smokeTestModule()
