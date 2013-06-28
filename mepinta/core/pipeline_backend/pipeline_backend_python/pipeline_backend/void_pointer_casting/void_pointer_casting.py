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

#Data
def int_to_voidp(int_v):#TODO: remove
  return int_v

def double_to_voidp(float_v):
  return float_v

def str_to_voidp(str_):
  return str_

def str_charp_to_voidp(str_):
  return str_

def str_string_to_voidp(str_):
  return str_

def any_ptr_to_voidp(anything):
  return anything

def voidp_to_int(voidp):
  return voidp

def voidp_to_double(voidp):
  return voidp

def voidp_to_str(voidp):
  return voidp

def voidp_charp_to_str(voidp):
  return voidp

def voidp_string_to_str(voidp):
  return voidp

def voidp_to_list_int(voidp):
  return voidp

def voidp_to_FunctionPropertyValue(voidp):
  return voidp

def voidp_to_FunctumPropertyValue(voidp):
  return voidp

#Functions pointers
def voidp_to_func_arg_void(voidp):
  return voidp

def voidp_to_func_arg_voidp(voidp):
  return voidp

def voidp_to_processor_func(voidp):
  return voidp

def voidp_to_copy_to_func(voidp):
  return voidp

def shedskin_type_generation_voidp():
  voidp = None
  voidp_to_func_arg_void(voidp)
  voidp_to_func_arg_voidp(voidp)

  voidp_to_int(voidp)
  voidp_to_str(voidp)
  voidp_to_double(voidp)
  voidp_to_list_int(voidp)

  any_ptr_to_voidp(voidp)
  int_to_voidp(1)
  double_to_voidp(10.0)
  str_to_voidp('')

if __name__ == '__main__':
  shedskin_type_generation_voidp()

