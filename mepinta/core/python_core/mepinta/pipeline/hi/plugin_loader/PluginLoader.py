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

from mepinta.pipeline.hi.base import HiAutoBase
from common.abstract.decorators.context_singleton import context_singleton

@context_singleton
class PluginLoader(HiAutoBase):
  '''
  '''
  def __post_init__(self):
    #TODO: review ids later
    self.last_func_id = 0
    self.last_dtype_id = 0
    
  def get_new_func_id(self):
    self.last_func_id += 1
    return self.last_func_id
  
  def get_new_dtype_id(self):
    self.last_dtype_id += 1
    return self.last_dtype_id
  
  def unload_data_type_library(self, data_type):
    self.wrapped.unload_data_type_library(data_type.library_path, data_type.id)
    
  def load_data_type_library(self, data_type):
    if data_type.id == None: 
      data_type.id = self.get_new_dtype_id()
    self.wrapped.load_data_type_library(data_type.library_path, data_type.c_namespace, data_type.id)

  def dataTypeIsLoaded(self, data_type):
    return self.wrapped.dataTypeIsLoaded(data_type.library_path)
  
  def unload_processor_library(self, processor):
    self.wrapped.unload_processor_library(processor.library_path, processor.functions.values())
    
  def load_processor_library(self, processor):
    if processor.functions == None: #first time we are loading this library
      func_dict = {}
      #Iterate over the functions to register
      for func_name in processor.proxy.get_functions_dict().keys():
        func_id = self.get_new_func_id()
        func_dict[func_name] = func_id
      #let's save it for using when reloading the library
      processor.functions = func_dict
    else: #we are reloading this library, then use old ids
      func_dict = processor.functions    
    #finally load the library
    self.wrapped.load_processor_library(processor.library_path, func_dict)

  def processorIsLoaded(self, processor):
    return self.wrapped.processorIsLoaded(processor.library_path)

def test(argv):
  pass
      
if __name__ == '__main__':
  import sys
  test(sys.argv)

