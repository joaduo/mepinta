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
Created on Nov 13, 2011

@author: jduo
'''

from pipeline.lower_level.constants import INPUT_PROPS, C_EXIT_SUCCESS

class MepintaArgs(object):
  def __init__(self):
    self.thread_id = 0
    self.inputs = None
    self.outputs = None

class MepintaProps(object):
  def __init__(self):
    self.prop_ids= []
    self.names   = []
    self.values  = []
    self.handles = []
    self.changed = set()

def delete_args(args):
  return C_EXIT_SUCCESS

def create_args(in_size, out_size):
  args = MepintaArgs()
  args.inputs = MepintaProps()
  args.outputs = MepintaProps()
  return args

args_per_thread={}
def get_thread_args(in_size, out_size,thread_id):
  global args_per_thread
  if thread_id not in args_per_thread:
    args = create_args(in_size, out_size)
    args_per_thread[thread_id] = args
  else:
    args = args_per_thread[thread_id]
    args_set_capacities(args, in_size, out_size)
  args_set_thread_id(args, thread_id)
  return args 

def args_set_thread_id(args,thread_id):
  args.thread_id = thread_id
  return C_EXIT_SUCCESS

def args_set_capacities(args, in_size, out_size):
  return C_EXIT_SUCCESS

def args_append_prop(args,in_out_id,index,prop_id,prop,data_type):
  if in_out_id == INPUT_PROPS:
    props = args.inputs
  else:
    props = args.outputs
  if len(props.prop_ids) == index:
    props.prop_ids.append(prop_id)
    props.names.append(prop.name)
    props.values.append(prop.get_value_ptr())
    props.handles.append(data_type.lib_handle)
  else:
    props.prop_ids[index] = prop_id
    props.names[index] = prop.name
    props.values[index] = prop.get_value_ptr()
    props.handles[index] = data_type.lib_handle
  return C_EXIT_SUCCESS

def args_set_changed(args, in_out_id, index):
  if in_out_id == INPUT_PROPS:
    props = args.inputs
  else:
    props = args.outputs
  props.changed.add(props.prop_ids[index])
  return C_EXIT_SUCCESS

def args_set_unchanged(args, in_out_id, index):
  if in_out_id == INPUT_PROPS:
    props = args.inputs
  else:
    props = args.outputs
  prop_id = props.prop_ids[index]
  if prop_id in props.changed:
    props.changed.remove(prop_id)
  return C_EXIT_SUCCESS

def args_build_changed_set(args):
  return args.outputs.changed

def shedskin_type_generation_argsm():
  delete_args(None)
  create_args(0, 0)
  args_set_capacities(None, 0, 0)
  #args_append_prop(None, 0, 0, 0, prop, data_type)
  args_set_changed(None, 0, 0)
  args_set_unchanged(None, 0, 0)
  args_build_changed_set(None)


