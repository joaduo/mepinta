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

from pipeline_backend.logging.logging import logWarning


def solveSymbol(handle, namespace, symbol):
    '''
      On python this function looks for a variable "symbol" in the module "handle"
        We don't use the namespace on python
      In a shedskin, and thus, in a C counterpart we should look for a symbol named
        "namspace+symbol" on the library handler (void*) 
    '''
    # Beware, when namespace = '', we are searching for a processor function
    if hasattr(handle, symbol):
        return getattr(handle, symbol)
    else:
        logWarning('Symbol %r not found with lib handler %r for namescape %r'%(symbol, handle, namespace))
        return None
