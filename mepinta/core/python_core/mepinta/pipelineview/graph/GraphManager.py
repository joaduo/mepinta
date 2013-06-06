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
from mepinta.pipelineview.graph.GraphPropertyManager import GraphPropertyManager
from common.abstract.FrameworkBase import FrameworkBase
from mepinta.pipelineview.graph.NodeManager import NodeManager
from mepinta.pipelineview.graph.GraphTopologyManager import GraphTopologyManager
from mepinta.plugins_manager.PluginsManager import PluginsManager

class GraphManager(FrameworkBase):
  def __post_init__(self):
    self.prop_mngr = GraphPropertyManager(self.context)
    self.topo_mngr = GraphTopologyManager(self.context)
    self.node_mngr = NodeManager(self.context)
    self.plugins_mngr = PluginsManager(self.context)

  def create_node(self, pline, processor): #TODO: add support for debugging version
    #create the node proxy
    node = self.node_mngr.new(processor)
    #sychronize node and inner pipeline
    self.__syncNode(pline, node)
    #return new node
    return node

  def syncNode(self, pline, node):
    #update the new data types to be loaded
    self.plugins_mngr.processor_plugins_manager.load_processors_data_types(node)
    #Set the new data types id to the node
    self.plugins_mngr.processor_plugins_manager.set_containers_dtype_id(node)
    #Now we can sync the node as if it were a new one
    self.__syncNode(pline, node)

  def __syncNode(self, pline, node):
    #Create the properties on the pline
    prop_ids = self.prop_mngr.create_properties(pline, node)
    #Connect dpdencies
    self.topo_mngr.add_properties(pline, prop_ids)
    #Make intranode connections
    self.topo_mngr.connect_internally(pline, node)
    #Enable Caching
    self.topo_mngr.enable_cached(pline, node)
    #Return the node
    return node
  def connect(self, pline, dent_prop, dency_prop):
    return self.topo_mngr.connect(pline, dent_prop, dency_prop)

  def disconnect(self, pline, dent_prop, dency_prop=None):
    return self.topo_mngr.disconnect(pline, dent_prop, dency_prop)

  def auto_connect(self, pline, dent_node, dency_node):
    inputs_names = dent_node.inputs.get_properties().keys()
    outputs_names = dency_node.outputs.get_properties().keys()
    self.log.debug('Autoconnecting in:%s out:%s' % (inputs_names, outputs_names))
    for name in outputs_names:
      if name in inputs_names:
        self.topo_mngr.connect(pline
                                  , getattr(dent_node.inputs, name)
                                  , getattr(dency_node.outputs, name))
