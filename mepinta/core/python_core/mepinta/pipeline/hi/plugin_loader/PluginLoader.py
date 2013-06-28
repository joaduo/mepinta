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
    
  def getNewFuncId(self):
    self.last_func_id += 1
    return self.last_func_id
  
  def getNewDtypeId(self):
    self.last_dtype_id += 1
    return self.last_dtype_id
  
  def unloadDataTypeLibrary(self, data_type):
    self.wrapped.unloadDataTypeLibrary(data_type.library_path, data_type.property_id)
    
  def loadDataTypeLibrary(self, data_type):
    if data_type.property_id == None: 
      data_type.property_id = self.getNewDtypeId()
    self.wrapped.loadDataTypeLibrary(data_type.library_path, data_type.c_namespace, data_type.property_id)

  def dataTypeIsLoaded(self, data_type):
    return self.wrapped.dataTypeIsLoaded(data_type.library_path)
  
  def unloadProcessorLibrary(self, processor):
    self.wrapped.unloadProcessorLibrary(processor.library_path, processor.functions.values())
    
  def loadProcessorLibrary(self, processor):
    if processor.functions == None: #first time we are loading this library
      func_dict = {}
      #Iterate over the functions to register
      for func_name in processor.proxy.getFunctionsDict().keys():
        func_id = self.getNewFuncId()
        func_dict[func_name] = func_id
      #let's save it for using when reloading the library
      processor.functions = func_dict
    else: #we are reloading this library, then use old ids
      func_dict = processor.functions    
    #finally load the library
    self.wrapped.loadProcessorLibrary(processor.library_path, func_dict)

  def processorIsLoaded(self, processor):
    return self.wrapped.processorIsLoaded(processor.library_path)

def test(argv):
  pass
      
if __name__ == '__main__':
  import sys
  test(sys.argv)

