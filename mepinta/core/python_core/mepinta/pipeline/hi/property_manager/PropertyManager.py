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
Created on Mar 9, 2012

@author: jduo
'''
from mepinta.pipeline.hi.base import HiAutoBase, unwrap_lo, unwrap_decorator
from mepinta.pipeline.lo.constants import INPUT_PROPERTY_FLAG, INTERNAL_PROPERTY_FLAG,\
  OUTPUT_PROPERTY_FLAG

class PropertyManager(HiAutoBase): 
  def __post_init__(self, non_cached_enabled=False):
    self.non_cached_enabled = non_cached_enabled
  def _create_properties_safe(self, pline, prop_type, names, data_types, prop_flags=0):
    filter_func = lambda dtype: unwrap_lo(dtype) not in self.context.context_lo.data_types
    return {filter_func:data_types}
  @unwrap_decorator
  def create_properties(self, pline, prop_type, names, data_types, prop_flags=0):
    #better alias (was unwrapped)
    dtype_ids = data_types
    if prop_type == 'input':
      prop_ids = self.wrapped.create_properties(pline, names, dtype_ids, INPUT_PROPERTY_FLAG|prop_flags)
    elif prop_type == 'internal':
      prop_ids = self.wrapped.create_properties(pline, names, dtype_ids, INTERNAL_PROPERTY_FLAG|prop_flags)            
    elif prop_type == 'output':
      prop_ids = self.wrapped.create_properties(pline, names, dtype_ids, OUTPUT_PROPERTY_FLAG|prop_flags)
    else:
      raise RuntimeError('unsupported property type: %r'%type)
    return prop_ids
  def _create_func_properties_safe(self, pline, names, func_ptr_ids):
    filter_func = lambda function: unwrap_lo(function) not in self.context.context_lo.functions
    return {filter_func:func_ptr_ids}
  @unwrap_decorator
  def create_func_properties(self, pline, names, func_ptr_ids):
    prop_ids = self.wrapped.create_func_properties(pline, names, func_ptr_ids)
    return prop_ids
  def _create_functum_properties_safe(self, pline, names, func_ptr_ids, data_types, prop_flags=0):
    filter_functions = lambda function: unwrap_lo(function) not in self.context.context_lo.functions
    filter_dtype = lambda dtype: unwrap_lo(dtype) not in self.context.context_lo.data_types
    return {filter_functions:func_ptr_ids, filter_dtype: data_types}  
  @unwrap_decorator
  def create_functum_properties(self, pline, names, func_ptr_ids, dtype_ids, prop_flags=0):
    prop_ids = self.wrapped.create_functum_properties(pline, names, func_ptr_ids, dtype_ids, prop_flags)
    return prop_ids

if __name__ == '__main__':
  from mepinta.context.MepintaContext import MepintaContext
  from mepinta.pipeline.hi.pipeline_data.data_model import Pipeline
  context = MepintaContext('python')
  pline = Pipeline(context=context)
  pline.grow()
  print(pline.get_topology())
  propm = PropertyManager(context=context)
  print( getattr(propm, 'create_properties'))
  print(propm)
  print(propm.context.context_lo.data_types)
  propm.create_properties(pline, 'input', ['hello'], [0])
  print(pline.all_properties)
  propm.create_properties(pline, 'input', ['hello','bye'], [0,0])
  print(pline.all_properties)
  propm.create_func_properties(pline, ['bla'], [0])
  print(pline.all_properties)

