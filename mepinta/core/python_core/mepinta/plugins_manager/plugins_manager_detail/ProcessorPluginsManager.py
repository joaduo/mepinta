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

from mepinta.plugins_manifest.proxy.data_model import DataPropertyProxy,\
  FunctumPropertyProxy
from bisect import bisect_left
from mepinta.plugins_manager.plugins_manager_detail.base import PluginsManagerBase
from mepinta.plugins_manager.data_model import ProcessorMetadata
from mepinta.plugins_manifest import PluginManifestBase

#TODO: review this mess below
FrameworkException = RuntimeError

class ProcessorPluginsManager(PluginsManagerBase):
  '''
  '''
  def load_processor_library(self,processor):
    self.context.log.info('Loading processor %r shared library'%processor)
    #Ask the lower lever C api to load this library, with local symbols, since we only call functions with pointers
    self.plugin_loader.load_processor_library(processor)
    #Add the processor as a dependant of the data_types
    for data_type_name in processor.data_types:
      self.data_types[data_type_name].processors.append(processor)
    #Add it to the loaded processors
    self.processors[processor.name][processor.version] = processor
  def unload_processor_library(self,processor):
    self.context.log.info('Unloading processor %r shared library'%processor)
    #Ask the lower lever C api to unload this library
    self.plugin_loader.unload_processor_library(processor)
    #Remove dependents from data types
    for data_type_name in processor.data_types:
      self.data_types[data_type_name].processors.remove(processor) #TODO: maybe later should use bisect_left
    #Processor is not loaded anymore
    del self.processors[processor.name][processor.version]
  def load_processors_data_types(self, processor_proxy):
    types_classes=[DataPropertyProxy, FunctumPropertyProxy]
    for data_type_name,data_type_versions in processor_proxy.getRequiredDataTypes(types_classes).items():
      #get the biggest version of a required datatype
      version = data_type_versions[-1]
      #Lets load it
      self.parent.load_data_type(data_type_name, version)
  def __getProcessorProxy(self,processor_module):
    if hasattr(processor_module, 'get_processor_proxy'):
      processor_proxy = processor_module.get_processor_proxy(self.context)
    elif hasattr(processor_module, 'plugin'):#TODO: delete this and above
      processor_proxy = processor_module.plugin(context=self.context).processor_proxy
    elif hasattr(processor_module, 'manifest'):
      manifest_class = processor_module.manifest
      if issubclass(manifest_class, PluginManifestBase):
        processor_proxy = manifest_class(context=self.context).processor_proxy
      else:
        raise RuntimeError('The manifest is not a subclass of PluginManifestBase. Instead it\'s %r'%manifest_class)
    else:
      raise FrameworkException('There is no definition on the module: %r.'%(processor_module))
    return processor_proxy
  def load_processor(self,processor,minor_version,replace,replace_version,reload_):
    self.context.log.debug('Loading processor: %r'%processor)
    processor_name, processor_package = self.processor_pkg_mngr.get_package_and_name(processor)
    build_modules = self.processor_pkg_mngr.get_revision_modules(processor_package)
    
    #TODO: should exist a PluginLoadingPolicy class to apply policies??? vv
    #Or should i leave this like this, and just encapsulate from line 63 on?
    #Check we don't have an empty plugin
    if len(build_modules['versions']) == 0:
      raise FrameworkException('Requested minor_version=%r for processor %r. There are no modules for such plugin.'%(minor_version,processor_name))
    #Check we have the minor_version or a later one
    #TODO: python3 breaks here!
    if minor_version > build_modules['versions'][-1]:
      raise FrameworkException('Requested minor_version=%r for processor %r is newer than the latest minor_version available.'%(minor_version,processor_name))
    
    #TODO: should exist a PluginLoadingPolicy class to apply policies
    #Which plugin minor minor_version should be loaded?
    if self.latest_processor or minor_version == None: #Load the latest one
      module_index = -1
    else: #Load the asked minor_version or the next one available
      module_index = bisect_left(build_modules['versions'], minor_version)
      
    #Let's get better naming #TODO: should came from PluginLoadingPolicy
    build_name = build_modules['names'][module_index]
    build_version = build_modules['versions'][module_index]
    if self.context.backend_name == 'python': 
      #On python the plugin module is the plugin itself #TODO: rename library_path to plugin_module
      library_path = self.processor_pkg_mngr.get_revision_module(processor_name, build_name)
    else: #then its shedskin. We still need to load the shared library
      library_path = processor_package.__path__[0] + '/%s.so.implementation'%build_name
    
    #Add the list to the dictionary if it's not already there.
    if processor_name not in self.processors:
      self.processors[processor_name] = {}
    elif build_version in  self.processors[processor_name] and not reload_:
      self.context.log.debug('Requested minor_version=%r for processor %r is already loaded.'%(build_version,processor_name))
      return self.processors[processor_name][build_version]
    
    #Do we need to create a processor or we use the existent one?
    if build_version not in self.processors[processor_name]:
      #New minor_version. Create the processor object.
      processor = ProcessorMetadata() #TODO: pass properties as arguments
      processor.name = processor_name
      processor.build_name = build_name
      processor.version = build_version
      processor.module = self.processor_pkg_mngr.get_revision_module(processor_name, build_name)
      processor.proxy = self.__getProcessorProxy(processor.module)
      processor.library_path = library_path
      #TODO: data types can be a property, then it queries the proxy? (what?)
      processor.data_types = processor.proxy.getRequiredDataTypes().keys()
      processor.package = processor_package
    else:      
      #It's an existent one. This means we are reloading. 
      processor = self.processors[processor_name][build_version]
      #Let's unload before reloading.
      self.unload_processor_library(processor)
      #reload manifest module too
      processor.module = self.processor_pkg_mngr.get_revision_module(processor_name, build_name)
      processor.proxy = self.__getProcessorProxy(processor.module)

    #First load required data types or reload new versions.
    self.load_processors_data_types(processor.proxy)
      
    #Finally load the processor library
    self.load_processor_library(processor)
    
    #Now that we loaded the data types and processor we can update 
      #the ids of the proxy
    self.set_processor_proxy_dtype_ids(processor)
    return processor
  def set_processor_proxy_dtype_ids(self, processor):
    #We need to re/set proxy's ids in a case of re/load
    self.set_containers_dtype_id(processor.proxy)
    processor.proxy.set_functions_id(processor.functions)
  def set_containers_dtype_id(self, proxy):
    #For each processor's property set its data type id
    for props_container in proxy.containers.values():
      for prop in props_container.get_properties(DataPropertyProxy,FunctumPropertyProxy).values():
        prop.dtype_id  = self.data_types[prop.data_type_name].id
