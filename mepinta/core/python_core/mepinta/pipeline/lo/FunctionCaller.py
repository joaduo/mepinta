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

from pipeline_backend.void_pointer_casting.void_pointer_casting import voidpToFuncArgVoid, \
  voidpToFuncArgVoidp, voidpToProcessorFunc, voidpToCopyToFunc
from pipeline_backend.logging.logging import logError, logWarning
from mepinta.pipeline.lo.constants import PROCESSOR_FUNC_NULL
from mepinta.pipeline.lo.exceptions.MepintaLoError import MepintaLoError

class FunctionCaller(object):
  def callFuncNoArgs(self, func_ptr):
    '''Calls a function with the prototype "void* func_name(void)" '''
    if func_ptr != None:
      casted_func_ptr = voidpToFuncArgVoid(func_ptr)
      return casted_func_ptr()
    else:
      msg = 'func_ptr is NULL. Couldn\'t call function with prototype "void* func_name(void)".'
      logError(msg)
      raise MepintaLoError(msg)

  def callFunc(self, func_ptr, func_args):
    '''Calls a function with the prototype "void* func_name(void*)" '''
    if func_ptr != None:
      casted_func_ptr = voidpToFuncArgVoidp(func_ptr)
      return casted_func_ptr(func_args)
    else:
      msg = 'func_ptr is NULL. Couldn\'t call function with prototype "void* func_name(void*)".'
      logError(msg)
      raise MepintaLoError(msg)

  def callIntFuncVoidp(self, func_ptr, voidp):
    '''Calls a function with the prototype "int func_name(void*)"
    Since self.callProcessorFunc does the same it's reused
    '''
    if func_ptr != None:
      return self.callProcessorFunc(func_ptr, voidp)
    else:
      msg = 'func_ptr is NULL. Couldn\'t call function with prototype "int func_name(void*)".'
      logError(msg)
      raise MepintaLoError(msg)

  def callProcessorFunc(self, func_ptr, args):
    '''Calls a processor function with the prototype "int func_name(void*)" '''
    if func_ptr != None:
      casted_func_ptr = voidpToProcessorFunc(func_ptr)
      return casted_func_ptr(args)
    else:
      #A processor may be NULL since we can reload the processor
      logWarning("func_ptr is NULL. Couldn't call processor function.")
      return PROCESSOR_FUNC_NULL

  def callCopyToFunc(self, func_ptr, to_ptr, from_ptr):
    '''Calls a "copyTo" function with the prototype "void* func_name(void*,void*)" '''
    #raise RuntimeError("Implement!")
    if func_ptr != None and to_ptr != None and from_ptr != None:
      casted_func_ptr = voidpToCopyToFunc(func_ptr)
      #import pdb; pdb.set_trace()
      to_ptr = casted_func_ptr(to_ptr, from_ptr)
      if to_ptr == None:
        msg = 'copyTo function failed to copy values.'
        logError(msg)
        raise MepintaLoError(msg)
      return to_ptr
    else:
      msg = 'func_ptr, to_ptr o from_ptr is NULL. Couldn\'t call copyTo function with prototype "void* func_name(void*)".'
      logError(msg)
      raise MepintaLoError(msg)

def shedskin_FunctionCaller():
  fc = FunctionCaller()
  fc.callFuncNoArgs(None)
  fc.callFunc(None, None)
  fc.callProcessorFunc(None, None)

if __name__ == '__main__':
  shedskin_FunctionCaller()


