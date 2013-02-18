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
Created on Sep 10, 2011

@author: jduo
'''

from mepinta.pipeline.lo.pipeline_data.data_model import DataType, ProcessorFunction
from pipeline_backend.logging.logging import log_info, log_debug
from pipeline_backend.solve_symbol.solve_symbol import solve_symbol
from pipeline_backend.load_unload_library.load_unload_library import unload_library, load_library

class PluginLoader(object):
  '''
  This library will do:
    -Check the correct symbols are in place
    -Get the functions pointer for those symbols
      -Update the table of functions pointers
  '''
  def __init__(self, context_lo):
    self.context_lo = context_lo

  def unload_data_type_library(self, path, dtype_id):
    if path in self.context_lo.data_types_paths:#unload library
      log_info('Unloading data type library at %r with dtype_id=%r'%(path, dtype_id))
      unload_library(self.context_lo.data_types_paths[path])
      self.context_lo.data_types_paths.__delitem__(path)
    else:
      log_debug('Data type library already unloaded.(at %r with dtype_id=%r)'%(path, dtype_id))

  def load_data_type_library(self, path, data_type_name, dtype_id):
    if path not in self.context_lo.data_types_paths: #Ok, the library isnt loaded
      log_info('Loading data type library at %r with data_type_name=%r and dtype_id=%r'%(path, data_type_name, dtype_id))
      #TODO: get real name set it and return it!
      handle = load_library(path, symbol='global')
      self.context_lo.data_types_paths[path] = handle
      if dtype_id not in self.context_lo.data_types:
        self.context_lo.data_types[dtype_id] = DataType(data_type_name,handle)
      else:
        self.context_lo.data_types[dtype_id].update_handle(handle)
    else:
      log_debug('Loading data type library already loaded. At %r with data_type_name=%r and dtype_id=%r'%(path, data_type_name, dtype_id))

  def dataTypeIsLoaded(self, path):
    return self.context_lo.data_types_paths.__contains__(path)

  def unload_processor_library(self, path, func_ids):
    if path in self.context_lo.processors_paths:#unload library
      log_info('Unloading processor library at %r with func_ids=%r'%(path, func_ids))
      unload_library(self.context_lo.processors_paths[path])
      #Unregister functions
      for f_id in func_ids:
        self.context_lo.functions[f_id].update_func_pointer(None)
      #delete the unloaded library (to avoid uncorrect lib handle lookup)
      self.context_lo.processors_paths.__delitem__(path)
    else:
      log_debug('Processor library already unloaded. (at %r with func_ids=%r)'%(path, func_ids))

  def load_processor_library(self, path, func_dict):
    if path not in self.context_lo.processors_paths: #Ok, the library isn't loaded
      log_info('Loading processor library at %r with func_dict=%r '%(path,func_dict))
      handle = load_library(path, symbol='local')
      self.context_lo.processors_paths[path] = handle
      #Register functions:
      for func_name in func_dict:
        func_id = func_dict[func_name]
        #Here there is no need of namespace since symbols are not global
        func_ptr = solve_symbol(handle, '', func_name)
        #func_ptr = self.function_loader.load(handle, func_name)
        if func_id in self.context_lo.functions:
          self.context_lo.functions[func_id].update_func_pointer(func_ptr)
        else:
          self.context_lo.functions[func_id] =  ProcessorFunction(func_name, func_ptr)
    else:
      log_debug('Processor library already loaded. (at %r with func_dict=%r)'%(path,func_dict))

  def processorIsLoaded(self, path):
    return self.context_lo.processors_paths.__contains__(path)

def shedskin_PluginLoader(context_lo):
  soll = PluginLoader(context_lo)
  soll.load_data_type_library('/path/to.so', 'Data Type Name', 1)
  soll.unload_data_type_library('/path/to.so', 1)
  soll.load_processor_library('/path/to.so', {'Func Name':1})
  soll.unload_processor_library('/path/to.so', [1])
  soll.processorIsLoaded('/path/to.so')
  soll.dataTypeIsLoaded('/path/to.so')

def shedskin_test():
  pass
  
if __name__ == '__main__':
#  shedskin_type_generation_soll()
  shedskin_test()

