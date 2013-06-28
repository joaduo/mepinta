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

def get_functum_struct_voidp(func_ptr, args):
  return None

args_per_thread={}
def get_thread_args(in_size, out_size,thread_id):
  global args_per_thread
  if thread_id not in args_per_thread:
    args = create_args(in_size, out_size)
    args_per_thread[thread_id] = args
  else:
    args = args_per_thread[thread_id]
    args_set_capacity(args, 1, in_size)
    args_set_capacity(args, 2, out_size)
  args_set_thread_id(args, thread_id)
  return args 

def delete_args(args):
  return 0

def create_args(in_size, out_size):
  return None 

def args_set_thread_id(args,thread_id):
  return 0

def args_set_capacity(args, in_out_id, props_size):
  return 0

def args_append_prop(args,in_out_id,index,prop_id,prop,prop_real,data_type):
  return 0    

def args_set_changed(args, in_out_id, index):
  return 0

def args_set_unchanged(args, in_out_id, index):
  return 0

def args_build_changed_set(args, in_out_id, changed):
  changed.add(10)
  return changed

def shedskin_type_generation_argsm():
#  args = None
#  size = 0
#  thread_id = 0
#  in_out_id = 1
#  index = 0
#  delete_args(args)
#  create_args(size, size)
#  args_set_capacity(args, in_out_id, size)
#  args_set_thread_id(args, thread_id)
#  #args_append_prop(None, 0, 0, 0, prop, data_type)
#  args_set_changed(args, in_out_id, index)
#  args_set_unchanged(args, in_out_id, index)
#  args_build_changed_set(args)
  args = create_args(in_size=1, out_size=1)
  delete_args(args)
  args_set_capacity(args, in_out_id=1, props_size=1)
#  class Misc(object):
#    def get_value_ptr(self): return None
#  data_type = Misc(); data_type.lib_handle = None
#  prop = Misc(); prop.name = 'bla'
#  args_append_prop(args, in_out_id=INPUT_PROPS, index=0, prop_id=0, prop=prop, data_type=data_type)
  args_set_changed(args, in_out_id=1, index=0)
  args_set_unchanged(args, in_out_id=1, index=0)
  changed = set()
  changed.add(0)
  args_build_changed_set(args, in_out_id=1, changed=changed)
  
  get_thread_args(in_size=1, out_size=1, thread_id=1)
  

