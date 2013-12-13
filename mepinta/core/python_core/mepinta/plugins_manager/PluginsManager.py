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
from mepinta.plugins_manager.plugins_manager_detail.DataTypePluginsManager import DataTypePluginsManager
from mepinta.plugins_manager.plugins_manager_detail.ProcessorPluginsManager import ProcessorPluginsManager
from common.abstract.FrameworkBase import FrameworkBase
from common.abstract.decorators.context_singleton import context_singleton

@context_singleton
class PluginsManager(FrameworkBase):
  '''
    This class loads (and unloads) data types and processors plugins and keeps
  their dependencies in synch.
    The main goal is to load a processor, but for this we need to load the data
  types used by it. Then this class takes care of the dependencies between
  processors and data types and having them synchronized. This means, loading
  the correct versions of data types when changing a processor's version.
  '''
  def __post_init__(self):
    #Shared information between data_type and processor plugins managers
    self._data_types = {}
    self.processors = {}
    #Let's instance each plugins manager
    self.data_type_plugins_manager = DataTypePluginsManager(data_types=self._data_types, processors=self.processors, parent=self, context=self.context)
    self.processor_plugins_manager = ProcessorPluginsManager(data_types=self._data_types, processors=self.processors, parent=self, context=self.context)
    #TODO: set for all contexts
#    self._setImportHook()

#  def _setImportHook(self):
#    plugins_root = joinPath(self.context.deployment_config.mepinta_source_path, 'plugins')
#    sys.meta_path.append(PluginImportHook(plugins_root))

  def loadDataType(self, data_type, minor_version=None, reload_=False):
    return self.data_type_plugins_manager.loadDataType(data_type, minor_version, reload_)
  def loadProcessor(self, processor, minor_version=None, replace=False, replace_version=None, reload_=False):
    return self.processor_plugins_manager.loadProcessor(processor, minor_version, replace, replace_version, reload_)
  def unloadProcessorLibrary(self, processor):
    return self.processor_plugins_manager.unloadProcessorLibrary(processor)

def smokeTestModule():
  from common.log.debugPrint import debugPrint
  from mepinta.context.MepintaContext import MepintaContext
  context = MepintaContext('python')
  pm = PluginsManager(context=context)
  debugPrint(pm)


if __name__ == "__main__":
  smokeTestModule()
