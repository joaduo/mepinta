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

import copy
from bisect import bisect_left
from mepinta.plugins_manager.plugins_manager_detail.base import PluginsManagerBase,\
  DataTypeUnavaliable
from mepinta.plugins_manager.data_model import DataTypeMetadata


class DataTypePluginsManager(PluginsManagerBase):
  '''
  '''  
  def loadDataType(self,data_type,minor_version,reload_):
    #Let's get the python package so we can list later it's module.
    data_type_name, data_type_package = self.dtype_pkg_mngr.getPackageAndName(data_type)
    
    #Let's check first if we need to do all this stuff.
    if data_type_name in self.data_types and self.data_types[data_type_name].version >= minor_version: #We have a newer minor_version loaded
      self.log.debug('Loaded minor_version is equal or greater than required minor_version. Doing nothing.')
      return self.data_types[data_type_name]

    #Now we get the list of builds for this data type and their versions. 
    build_modules = self.dtype_pkg_mngr.getRevisionModules(data_type_package)
    
    #Check we don't have an empty plugin
    if len(build_modules['versions']) == 0:
      raise RuntimeError('Requested minor_version=%r for data_type %r. There are no modules for such plugin.'%(minor_version,data_type_name))    
    #Check we have the minor_version or a later one.
    if minor_version > build_modules['versions'][-1] and not reload_:
      raise DataTypeUnavaliable('Requested minor_version=%r for data type %r is newer than the latest minor_version available.'%(minor_version,data_type_name))

    #Which library minor_version should be loaded?
    if self.latest_data_type or minor_version == None: #Load the latest one
      module_index = -1
    else: #Load the asked minor_version or the next one available
      module_index = bisect_left(build_modules['versions'], minor_version)
      
    #Create the data_type object
    data_type = DataTypeMetadata()
    data_type.name = data_type_name
    data_type.build_name = build_modules['names'][module_index]
    data_type.version = build_modules['versions'][module_index]
    data_type.package = data_type_package
    if self.context.backend_name == 'python': #On python description package is the same data type package
      data_type.library_path = self.dtype_pkg_mngr.getRevisionModule(data_type, data_type.build_name)
    else: #then its cpp (shedskin)
      #OS:
      data_type.library_path = data_type_package.__path__[0] + '/%s.so.implementation'%data_type.build_name
      #Create the sym link for other dependent libraries
      #self.library_link_mgr.create_shared_lib_link(data_type.name, data_type.library_path)

    if data_type.name not in self.data_types: #The data type is not already loaded
      self.loadDataTypeLibrary(data_type)
    else: #Ok, its loaded. We need to reload_
      #save previous property_id
      data_type.property_id = self.data_types[data_type.name].property_id
      #Save unloaded processors before
      dependent_processors = copy.copy(self.data_types[data_type.name].processors)
      #Unload the data_type library #TODO: maybe later also data types could be dependents of other data types.
      self.unloadDataTypeLibrary(self.data_types[data_type.name])
      #Reload the data type library
      self.loadDataTypeLibrary(data_type)
      #Ok, let's reload_ the dependent processors, so that they are available for later use
      for processor in dependent_processors:
        self.loadProcessor(processor)
  def loadDataTypeLibrary(self,data_type):
    self.log.info('Loading %r,%r data type.'%(data_type.name,data_type.version))
    #Ask the lower lever C api to load this library, with global symbols, since they will be used by the processors
    self.plugin_loader.loadDataTypeLibrary(data_type)
    #data_type.name_in_backend = self.shared_library_loader.loadDataTypeLibrary(data_type) #TODO: comes from the backend
    #TODO: warn if there are equal names in backend?? (should be so for handling variable properties)
    #For future loading purposes
    self.data_types[data_type.name] = data_type
  def unloadDataTypeLibrary(self,data_type):
    #Unload processors depending on this data type (we need to reaload them later to use new API)
    for processor in data_type.processors:
      self.unloadProcessorLibrary(processor)
    self.log.info('Unloading %r data type.'%(data_type.name))
    #Ask the lower lever C api to unload this library
    self.plugin_loader.unloadDataTypeLibrary(data_type)
    #Delete previous version data_type
    del self.data_types[data_type.name]
