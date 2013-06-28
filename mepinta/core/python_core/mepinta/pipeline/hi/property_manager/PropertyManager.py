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
from mepinta.pipeline.hi.base import HiAutoBase, unwrapLo, unwrap_decorator
from mepinta.pipeline.lo.constants import INPUT_PROPERTY_FLAG, INTERNAL_PROPERTY_FLAG, \
  OUTPUT_PROPERTY_FLAG

class PropertyManager(HiAutoBase):
  def __post_init__(self, non_cached_enabled=False):
    self.non_cached_enabled = non_cached_enabled
  def _createPropertiesSafe(self, pline, prop_type, names, data_types, prop_flags=0):
    #filterFunc = lambda dtype: unwrapLo(dtype) not in self.context.context_lo.data_types
    def filterFunc(dtype):
      if unwrapLo(dtype) not in self.context.context_lo.data_types:
        self.log(dtype)
        self.log(self.context.context_lo.data_types)
        return False
      else:
        return False
    return {filterFunc:data_types}
  @unwrap_decorator
  def createProperties(self, pline, prop_type, names, data_types, prop_flags=0):
    #better alias (was unwrapped)
    dtype_ids = data_types
    if prop_type == 'input':
      prop_ids = self.wrapped.createProperties(pline, names, dtype_ids, INPUT_PROPERTY_FLAG | prop_flags)
    elif prop_type == 'internal':
      prop_ids = self.wrapped.createProperties(pline, names, dtype_ids, INTERNAL_PROPERTY_FLAG | prop_flags)
    elif prop_type == 'output':
      prop_ids = self.wrapped.createProperties(pline, names, dtype_ids, OUTPUT_PROPERTY_FLAG | prop_flags)
    else:
      raise RuntimeError('unsupported property type: %r' % type)
    return prop_ids
  def _createFuncPropertiesSafe(self, pline, names, func_ptr_ids):
    filterFunc = lambda function: unwrapLo(function) not in self.context.context_lo.functions
    return {filterFunc:func_ptr_ids}
  @unwrap_decorator
  def createFuncProperties(self, pline, names, func_ptr_ids):
    prop_ids = self.wrapped.createFuncProperties(pline, names, func_ptr_ids)
    return prop_ids
  def _createFunctumPropertiesSafe(self, pline, names, func_ptr_ids, data_types, prop_flags=0):
    filter_functions = lambda function: unwrapLo(function) not in self.context.context_lo.functions
    filter_dtype = lambda dtype: unwrapLo(dtype) not in self.context.context_lo.data_types
    return {filter_functions:func_ptr_ids, filter_dtype: data_types}
  @unwrap_decorator
  def createFunctumProperties(self, pline, names, func_ptr_ids, dtype_ids, prop_flags=0):
    prop_ids = self.wrapped.createFunctumProperties(pline, names, func_ptr_ids, dtype_ids, prop_flags)
    return prop_ids

if __name__ == '__main__':
  from mepinta.context.MepintaContext import MepintaContext
  from mepinta.pipeline.hi.pipeline_data.data_model import Pipeline
  context = MepintaContext('python')
  pline = Pipeline(context=context)
  pline.grow()
  debugPrint(pline.getTopology())
  propm = PropertyManager(context=context)
  debugPrint(getattr(propm, 'createProperties'))
  debugPrint(propm)
  debugPrint(propm.context.context_lo.data_types)
  propm.createProperties(pline, 'input', ['hello'], [0])
  debugPrint(pline.all_properties)
  propm.createProperties(pline, 'input', ['hello', 'bye'], [0, 0])
  debugPrint(pline.all_properties)
  propm.createFuncProperties(pline, ['bla'], [0])
  debugPrint(pline.all_properties)

