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

from mepinta.pipeline.hi.plugin_loader.PluginLoader import PluginLoader
from mepinta.plugins_manager.plugins_manager_detail.PluginPackageManager import PluginPackageManager
from common.abstract.FrameworkBase import FrameworkBase

# TODO: review Design, it's a control class with attr/properties (although its "singleton")
# this attrs/props should be stored in the real singleton PluginsManager
class PluginsManagerBase(FrameworkBase):
  def __post_init__(self, data_types, processors, parent):
    self.parent = parent
    self.data_types = data_types
    self.processors = processors
    self.plugin_loader = PluginLoader(context=self.context)
    # self.library_link_mgr = LibraryLinkManager(context=self.context)
    # TODO: rename this, it is confusing
    self.dtype_pkg_mngr = PluginPackageManager(plugins_type='data_types', context=self.context)
    self.processor_pkg_mngr = PluginPackageManager(plugins_type='processors', context=self.context)
    self.latest_data_type = False  # TODO: this should come from config
    self.latest_processor = False  # TODO: this should come from config

