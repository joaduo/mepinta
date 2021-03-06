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
from pipeline_backend.logging.logging import LOG_INFO, LOG_DEBUG
from mepinta.context.MepintaContext import MepintaContext
import sys

called_once = False


def getDefaultContext(log_level=LOG_INFO, name='python'):
    '''Creates a default context to reduce code verbosity for starting.'''
    print >> sys.stderr, 'Calling getDefaultContext is deprecated.'
    global called_once
    if called_once:
        raise RuntimeError('You should call the default context only once. (in the'
                           ' main script)')
    else:
        called_once = True
    context = MepintaContext(name)
    context.log.setLevel(log_level)
    return context


def smokeTestModule():
    from common.log.debugPrint import debugPrint
    ctxc = getDefaultContext(name='python')
    debugPrint(ctxc.getConfigDict())

if __name__ == "__main__":
    smokeTestModule()
