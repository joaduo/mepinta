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

from mepinta.pipeline.lo.FunctionCaller import FunctionCaller
from mepinta.pipeline.lo.pipeline_data.data_model import PropertyValuePointer
from mepinta.pipeline.lo.constants import FUNCTION_PROPERTY_FLAG
from pipeline_backend.args_management.args_management import delete_args
from pipeline_backend.void_pointer_casting.void_pointer_casting import voidp_to_FunctionPropertyValue
from pipeline_backend.logging.logging import log_critical, log_debug

#TODO: make it thread safe
class PropertyValueManager(object):
  def __init__(self, context_lo):
    self.context_lo = context_lo
    self.func_caller = FunctionCaller()
  def new_prop_value(self, prop, value):
    log_debug('New prop value for prop %r.'%prop)
    if prop.get_value_ptr().get_value() == None:
      prop.get_value_ptr().replace_value(value,None)
    else:
      data_type = self.context_lo.data_types[prop.dtype_id]
      func_ptr_del = data_type.get_func_ptr('delete')
      prop.get_value_ptr().replace_value(value,func_ptr_del)
  def init_prop_value(self, prop):
    '''
    '''
    #For properties stored inside the void* this function
    #may be redundant, but since there is caching for solving functions
    #the impact shoudln't be too big
    #TODO:if prop.get_value_ptr().get_value() == None and prop.changed_value_ptr(): #No need to free
    log_debug('Initializing value for prop %r.'%prop)
    if prop.get_value_ptr().get_value() == None: #No need to free
      func_ptr_del = None
      data_type = self.context_lo.data_types[prop.dtype_id]
      func_ptr_new = data_type.get_func_ptr('new')
      value = self.func_caller.call_func_no_args(func_ptr_new)
      prop.get_value_ptr().replace_value(value, func_ptr_del)   
  def init_set_prop_value(self, prop, value_ptr):
    '''
      If the property doesn't own already that value pointer
      then set the new value.
      Then check if the value was initialized or not.
    '''
    log_debug('Init and set value for prop %r.'%prop)
    if prop.get_value_ptr() != value_ptr:
      self.set_prop_value(prop, value_ptr)
      
    self.init_prop_value(prop)

  def set_prop_value(self, prop, value_ptr):
    log_debug('Setting value for prop %r.'%prop)
    #TODO: delete this? Or add it as a debug feature?
    #    if prop.type == FUNCTION_PROPERTY_FLAG: #Functions have data_type = 0
    #      log_warning('You shouldn\'t set a function property value pointer. Doing nothing.')
    #    else:
    if prop.get_value_ptr().get_value() == None: #No need to free
      func_ptr_del = None
    else:#We need to free
      data_type = self.context_lo.data_types[prop.dtype_id]
      func_ptr_del = data_type.get_func_ptr('delete')
    #We finally set the value          
    prop.set_value_ptr(value_ptr,func_ptr_del)
  def copy_prop_value(self, prop, value_ptr):
    log_debug('Copying value for prop %r.'%prop)
    #Get the function pointer
    data_type = self.context_lo.data_types[prop.dtype_id]
    func_ptr_copy = data_type.get_func_ptr('copy_to')
    if func_ptr_copy != None:
      #the "copy_to" function is implemented
      if (None != self.func_caller.call_copy_to_func(func_ptr_copy
                                         , prop.get_value_ptr().get_value()
                                         , value_ptr.get_value())):
        log_critical('Couldn\'t copy to prop:%r from value_ptr:%r'%(prop,value_ptr))
    else:
      #the "copy_to" function is not implemented, 
      #then copy to a new value and delete prior one
      func_ptr_copy = data_type.get_func_ptr('copy')
      value_copy = self.func_caller.call_func(func_ptr_copy
                                              , value_ptr.get_value())
      self.set_prop_value(prop, PropertyValuePointer(value_copy))
  def delete_properties(self, props):
    for prop in props:
      log_debug('Deleting value for prop %r.'%prop)
      value = prop.get_value_ptr().get_value()
      if value != None: #We need to free the value
        if prop.type == FUNCTION_PROPERTY_FLAG: #We need to free the args nothing else
          delete_args(voidp_to_FunctionPropertyValue(value).args)
        else: #We need to free the value with the data type lib
          data_type = self.context_lo.data_types[prop.dtype_id]
          func_ptr_del = data_type.get_func_ptr('delete')          
          prop.get_value_ptr().decrement_reference_count(func_ptr_del)


def shedskin_PropertyValueManager(context_lo, prop):
  pvm = PropertyValueManager(context_lo)
  value = None
  pvm.new_prop_value(prop, value)
  pvm.init_prop_value(prop)
  value_ptr = PropertyValuePointer()
  pvm.init_set_prop_value(prop, value_ptr)
  pvm.set_prop_value(prop, value_ptr)
  pvm.copy_prop_value(prop, value_ptr)
  pvm.delete_properties([prop])
  
if __name__ == '__main__':
  pass
#  from mepinta.pipeline.lo.pipeline_data.data_model import Property  
#  from mepinta.pipeline.lo.context_lo.ContextLo import ContextLo
#  context_lo = ContextLo()
#  prop = Property(1, 'hello', 0)
#  shedskin_type_generation_pvm(context_lo, prop)

