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

from pipeline_backend.void_pointer_casting.void_pointer_casting import voidp_to_func_arg_void,\
  voidp_to_func_arg_voidp, voidp_to_processor_func
from pipeline_backend.logging.logging import log_error
from mepinta.pipeline.lo.constants import PROCESSOR_FUNC_NULL

class FunctionCaller(object):
  def call_func_no_args(self, func_ptr):
    '''Calls a function with the prototype "void* func_name(void)" '''
    if func_ptr != None:
      casted_func_ptr = voidp_to_func_arg_void(func_ptr)
      return casted_func_ptr()
    else:
      log_error('func_ptr is NULL. Couldn\'t call function with prototype "void* func_name(void)".')
      return None

  def call_func(self, func_ptr, func_args):
    '''Calls a function with the prototype "void* func_name(void*)" '''
    if func_ptr != None:
      casted_func_ptr = voidp_to_func_arg_voidp(func_ptr)
      return casted_func_ptr(func_args)
    else:
      log_error('func_ptr is NULL. Couldn\'t call function with prototype "void* func_name(void*)".')
      return None

  def call_processor_func(self, func_ptr, args):
    '''Calls a processor function with the prototype "int func_name(void*)" '''
    if func_ptr != None:
      casted_func_ptr= voidp_to_processor_func(func_ptr)
      return casted_func_ptr(args)
    else:
      log_error("func_ptr is NULL. Couldn't call processor function.")
      return PROCESSOR_FUNC_NULL

  def call_copy_to_func(self, func_ptr, to_ptr, from_ptr):
    '''Calls a "copy_to" function with the prototype "void* func_name(void*,void*)" '''
    raise RuntimeError("Implement!")
#    if func_ptr != None:
#      casted_func_ptr= voidp_to_copy_to_func(func_ptr)
#      return casted_func_ptr(to_ptr,from_ptr)
#    else:
#      log_error("func_ptr is NULL. Couldn't call copy to function.")
#      return None  

def shedskin_type_generation_fc():
  fc = FunctionCaller()
  fc.call_func_no_args(None)
  fc.call_func(None, None)
  fc.call_processor_func(None, None)

if __name__ == '__main__':
  shedskin_type_generation_fc()

