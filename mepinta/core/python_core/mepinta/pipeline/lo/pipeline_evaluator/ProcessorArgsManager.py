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
from pipeline_backend.args_management.args_management import create_args, args_append_prop,\
  args_set_changed, args_set_unchanged, args_build_changed_set,\
  args_set_capacity, get_thread_args, args_set_thread_id
from mepinta.pipeline.lo.constants import OUTPUT_PROPS, CUSTOM_OUTPUT_PROPS,\
  INPUT_PROPS, CUSTOM_INPUT_PROPS
#from pipeline_backend.args_management.argsSetProcessorContext import argsSetProcessorContext

#TODO: Rename ProcessorArgsManager ProcessorArgsBuilder
#TODO: check get_thread_args and threading
class ProcessorArgsManager(object):
  def __init__(self, context_lo, func_prop_value, thread_id):
    self.context_lo = context_lo
    self.args = self.create_args(func_prop_value, thread_id)
    self.indexes = {INPUT_PROPS:0, 
                        OUTPUT_PROPS:0, 
                        CUSTOM_INPUT_PROPS:0, 
                        CUSTOM_OUTPUT_PROPS:0}
    self.marked = False

  def set_in_out(self, in_out_id):
    self.in_out_id = in_out_id
    
  def __getCurrentIndex(self):
    return self.indexes[self.in_out_id]
  
  def __incrementCurrentIndex(self, delta=1):
    self.indexes[self.in_out_id] += delta
    
  def create_args(self, func_prop_value, thread_id):
#    if cached:
    if func_prop_value.args == None:
      self.new_args = True
      #func_prop_value.args = create_args(in_size,out_size)
      func_prop_value.args = create_args(0,0)
    else:
      self.new_args = False
    args_set_thread_id(func_prop_value.args,thread_id)
    return func_prop_value.args
#    else:
#      self.new_args = True
#      return get_thread_args(in_size,out_size,thread_id)
  def get_args(self):
    return self.args
  
#  def setProcessorContext(self, processor_context):
#    argsSetProcessorContext(self.args, processor_context)
  
  def next_prop(self): #useful for skipping a property too
    self.__incrementCurrentIndex(1)
    
  def append(self, prop_id, prop, prop_real):
    data_type = self.context_lo.data_types[prop_real.dtype_id]
    args_append_prop(self.args,self.in_out_id,self.__getCurrentIndex(),prop_id,prop,prop_real,data_type)
#  def update(self, in_prop_ids, out_prop_ids):
#    raise RuntimeError("Implement")
  def changed_value(self):
    args_set_changed(self.args,self.in_out_id,self.__getCurrentIndex())
  def unchanged_value(self):
    args_set_unchanged(self.args,self.in_out_id,self.__getCurrentIndex())
  def build_changed_set(self):
    changed = set()
    args_build_changed_set(self.args, OUTPUT_PROPS, changed)
    args_build_changed_set(self.args, CUSTOM_OUTPUT_PROPS, changed)
    return changed

def shedskin_ProcessorArgsManager(context_lo,func_prop_value,prop):
  pam = ProcessorArgsManager(context_lo, func_prop_value, thread_id=0)
  prop_id=100
  pam.set_in_out(in_out_id=1)
  pam.append(prop_id, prop, prop)
  pam.get_args()
  pam.next_prop()
  pam.append(prop_id, prop, prop)
  pam.changed_value()
  pam.unchanged_value()
  pam.build_changed_set()
  return pam

