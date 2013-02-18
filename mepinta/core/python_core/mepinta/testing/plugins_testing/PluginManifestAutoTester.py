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
from mepinta.pipeline.hi.pipeline_data.data_model import Pipeline
from mepinta.pipelineview.graph.GraphManager import GraphManager
from mepinta.plugins_manager.PluginsManager import PluginsManager
from mepinta.pipelineview.graph.GraphTopologyManager import GraphTopologyManager
from mepinta.testing.plugins_testing.base import ModuleAutoTesterBase

class PluginManifestAutoTester(ModuleAutoTesterBase):
  def createNode(self, plugin_manifest):
    pline = Pipeline(context=self.context)
    #pline.grow()
    pline.endChangeSet()
    plinmngr = PluginsManager(context=self.context)
    plugin_package, minor_version = self._getPackageAndMinorVersion(plugin_manifest)
    processor_metadata = plinmngr.load_processor(plugin_package, minor_version) 
    gm = GraphManager(context=self.context)
    node = gm.create_node(pline, processor_metadata)
    self.logPline(pline)
    return pline,node

  def logPline(self, pline):
    self.context.log.debug(pline.all_properties)
    self.context.log.debug(pline.get_topology())

  def test(self, plugin_manifest_class, gui=True):
    plugin_manifest = plugin_manifest_class(self.context)
    self.context.set_config('non_cached', False, GraphTopologyManager)
    pline, _ = self.createNode(plugin_manifest)
    if gui:
      #import here to avoid unnecessary memory use and delays
      from mepinta.testing.plugins_testing.nodebox.NodeBoxSimplePipelineOutput import NodeBoxSimplePipelineOutput
      NodeBoxSimplePipelineOutput(pline, 600, 600).run()
        
if __name__ == "__main__":
  pass
