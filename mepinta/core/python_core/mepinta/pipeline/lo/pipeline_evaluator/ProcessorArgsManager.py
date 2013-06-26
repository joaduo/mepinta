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
from pipeline_backend.args_management.args_management import createArgs, argsAppendProp,\
  argsSetChanged, argsSetUnchanged, argsBuildChangedSet,\
  argsSetCapacity, getThreadArgs, argsSetThreadId
from mepinta.pipeline.lo.constants import OUTPUT_PROPS, CUSTOM_OUTPUT_PROPS,\
  INPUT_PROPS, CUSTOM_INPUT_PROPS
#from pipeline_backend.args_management.argsSetProcessorContext import argsSetProcessorContext

#TODO: Rename ProcessorArgsManager ProcessorArgsBuilder
#TODO: check getThreadArgs and threading
class ProcessorArgsManager(object):
  def __init__(self, context_lo, func_prop_value, thread_id):
    self.context_lo = context_lo
    self.args = self.createArgs(func_prop_value, thread_id)
    self.indexes = {INPUT_PROPS:0, 
                        OUTPUT_PROPS:0, 
                        CUSTOM_INPUT_PROPS:0, 
                        CUSTOM_OUTPUT_PROPS:0}
    self.marked = False

  def setInOut(self, in_out_id):
    self.in_out_id = in_out_id
    
  def __getCurrentIndex(self):
    return self.indexes[self.in_out_id]
  
  def __incrementCurrentIndex(self, delta=1):
    self.indexes[self.in_out_id] += delta
    
  def createArgs(self, func_prop_value, thread_id):
#    if cached:
    if func_prop_value.args == None:
      self.new_args = True
      #func_prop_value.args = createArgs(in_size,out_size)
      func_prop_value.args = createArgs(0,0)
    else:
      self.new_args = False
    argsSetThreadId(func_prop_value.args,thread_id)
    return func_prop_value.args
#    else:
#      self.new_args = True
#      return getThreadArgs(in_size,out_size,thread_id)
  def getArgs(self):
    return self.args
  
#  def setProcessorContext(self, processor_context):
#    argsSetProcessorContext(self.args, processor_context)
  
  def nextProp(self): #useful for skipping a property too
    self.__incrementCurrentIndex(1)
    
  def append(self, prop_id, prop, prop_real):
    data_type = self.context_lo.data_types[prop_real.dtype_id]
    argsAppendProp(self.args,self.in_out_id,self.__getCurrentIndex(),prop_id,prop,prop_real,data_type)
#  def update(self, in_prop_ids, out_prop_ids):
#    raise RuntimeError("Implement")
  def changedValue(self):
    argsSetChanged(self.args,self.in_out_id,self.__getCurrentIndex())
  def unchangedValue(self):
    argsSetUnchanged(self.args,self.in_out_id,self.__getCurrentIndex())
  def buildChangedSet(self):
    changed = set()
    argsBuildChangedSet(self.args, OUTPUT_PROPS, changed)
    argsBuildChangedSet(self.args, CUSTOM_OUTPUT_PROPS, changed)
    return changed

def shedskin_ProcessorArgsManager(context_lo,func_prop_value,prop):
  pam = ProcessorArgsManager(context_lo, func_prop_value, thread_id=0)
  prop_id=100
  pam.setInOut(in_out_id=1)
  pam.append(prop_id, prop, prop)
  pam.getArgs()
  pam.nextProp()
  pam.append(prop_id, prop, prop)
  pam.changedValue()
  pam.unchangedValue()
  pam.buildChangedSet()
  return pam

