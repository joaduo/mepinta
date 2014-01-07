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

class DataTypeMetadataWrapper(MetadataWrapperBase):
  def __post_init__(self):
    self._pkg_mngr = PluginPackageManager(plugins_type='data_types',
                                          context=self.context)

  @property
  def manifest(self):
    if hasattr(self.module, 'manifest'):
      return MetadataWrapperBase.getManifest(self)
    else:
      return object()

def smokeTestModule():
#  from getDefaultContext import getDefaultContext
#  context = getDefaultContext()
  raise RuntimeWarning('No smoke test')

if __name__ == "__main__":
  smokeTestModule()
