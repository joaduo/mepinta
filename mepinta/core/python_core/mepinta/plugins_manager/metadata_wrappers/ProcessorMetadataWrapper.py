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
from mepinta.plugins_manager.metadata_wrappers.base import MetadataWrapperBase
from mepinta.plugins_manager.plugins_manager_detail.PluginPackageManager import PluginPackageManager
from mepinta.plugins_manifest.proxy.data_model import DataPropertyProxy, \
  FunctumPropertyProxy
from mepinta.plugins_manifest import ProcessorManifestBase

class ProcessorMetadataWrapper(MetadataWrapperBase):
  def __post_init__(self):
    self._pkg_mngr = PluginPackageManager(plugins_type='processors',
                                          context=self.context)

  def refresh(self):
    MetadataWrapperBase.refresh(self)
    self._proxy = None

  def getManifestType(self):
    return ProcessorManifestBase

  @property
  def proxy(self):
    '''
    Detects Processor Manifest Inside module and returns the Proxy of the
      processor.
    '''
    if not self._proxy:
      self._proxy = self.manifest.processor_proxy
    return self._proxy


  @property
  def data_types(self):
    return self.proxy.getRequiredDataTypes().keys()

  def setIds(self, data_types):
    #We need to re/set proxy's ids in a case of re/load
    self._setContainersIds(self.proxy, data_types)
    self.proxy.setFunctionsId(self._meta_data.functions)

  def _setContainersIds(self, proxy, data_types):
    #For each processor's property set its data type property_id
    for props_container in proxy.containers.values():
      for prop in props_container.getProperties(DataPropertyProxy,
                                                FunctumPropertyProxy).values():
        prop.dtype_id = data_types[prop.data_type_name].property_id


def smokeTestModule():
#  from getDefaultContext import getDefaultContext
#  context = getDefaultContext()
  raise RuntimeWarning('No smoke test')

if __name__ == "__main__":
  smokeTestModule()
