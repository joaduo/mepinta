# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo

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
from mepinta.plugins_manifest.proxy.data_model import DataPropertyProxy, \
  FunctumPropertyProxy
from bisect import bisect_left
from mepinta.plugins_manager.plugins_manager_detail.base import PluginsManagerBase
from mepinta.plugins_manager.data_model import ProcessorMetadata
from mepinta.plugins_manager.plugins_manager_detail.PluginImportError import PluginImportError
from mepinta.plugins_manager.metadata_wrappers.ProcessorMetadataWrapper import ProcessorMetadataWrapper


class ProcessorPluginsManager(PluginsManagerBase):
  '''
  '''
  def loadProcessorLibrary(self, processor):
    self.log.info('Loading processor %r shared library' % processor)
    #Ask the lower lever C api to load this library, with local symbols, since we only call functions with pointers
    self.plugin_loader.loadProcessorLibrary(processor)
    #Add the processor as a dependant of the data_types
    for data_type_name in processor.data_types:
      self.data_types[data_type_name].processors.append(processor)
    #Add it to the loaded processors
    self.processors[processor.name][processor.version] = processor

  def unloadProcessorLibrary(self, processor):
    self.log.info('Unloading processor %r shared library' % processor)
    #Ask the lower lever C api to unload this library
    self.plugin_loader.unloadProcessorLibrary(processor)
    #Remove dependents from data types
    for data_type_name in processor.data_types:
      self.data_types[data_type_name].processors.remove(processor) #TODO: maybe later should use bisect_left
    #Processor is not loaded anymore
    del self.processors[processor.name][processor.version]

  def loadProcessorsDataTypes(self, processor):
    proxy = processor.proxy
    types_classes = (DataPropertyProxy, FunctumPropertyProxy)
    for data_type_name, data_type_versions in proxy.getRequiredDataTypes(types_classes).items():
      #get the biggest version of a required datatype
      version = data_type_versions[-1]
      #Lets load it
      self.parent.loadDataType(data_type_name, version)

  def _getMinorVersion(self, minor_version, package, processor_name):
    #TODO: should exist a PluginLoadingPolicy class to apply policies?
    modules = self.processor_pkg_mngr.getRevisionModules(package)

    #TODO: python3 breaks here!
    #Check we don't have an empty plugin dir
    #and we have the minor_version or a later one
    if not modules['versions'] or minor_version > modules['versions'][-1]:
      raise PluginImportError('No minor version equal or newer than %r for %r'
                              'versions=%r' % (minor_version, processor_name,
                                               modules['versions']))

    #Which plugin minor minor_version should be loaded?
    if self.latest_processor or minor_version == None: #Load the latest one
      module_index = -1
    else: #Load the asked minor_version or the next one available
      module_index = bisect_left(modules['versions'], minor_version)

    #Let's get better naming #TODO: should came from PluginLoadingPolicy
    build_name = modules['names'][module_index]
    minor_version = modules['versions'][module_index]
    return build_name, minor_version

  def loadProcessor(self, processor, minor_version, replace, replace_version, reload_):
    self.log.debug('Loading processor: %r' % processor)
    processor_name, package = self.processor_pkg_mngr.getPackageAndName(processor)

    build_name, minor_version = self._getMinorVersion(minor_version, package, processor_name)

    #Add the processor to the dictionary if it's not already there.
    if minor_version in  self.processors.setdefault(processor_name, {}) \
    and not reload_:
      self.log.debug('Requested minor_version=%r for processor %r is already '
                     'loaded.' % (minor_version, processor_name))
      return self.processors[processor_name][minor_version]

    #Do we need to create a processor or we use the existent one?
    if minor_version not in self.processors[processor_name]:
      #New minor_version. Create the processor object.
      meta_data = ProcessorMetadata(
          name=processor_name,
          build_name=build_name,
          version=minor_version,
          )
      processor = ProcessorMetadataWrapper(self.context, meta_data=meta_data)
    else:
      #It's an existent one. This means we are reloading.
      processor = self.processors[processor_name][minor_version]
      #Let's unload before reloading.
      self.unloadProcessorLibrary(processor)
      #Reset proxy, module and package (keeps functions ids)
      processor.refresh()

    #First load required data types or reload new versions.
    self.loadProcessorsDataTypes(processor)

    #Finally load the processor library
    self.loadProcessorLibrary(processor)

    #Now update the data types' and functions' ids in the proxy
    processor.setIds()
    return processor

