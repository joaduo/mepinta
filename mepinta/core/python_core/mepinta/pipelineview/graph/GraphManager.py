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

def topology_changed(method):
  def newMethod(*args, **kwargs):
    if len(args) > 2 and hasattr(args[1], 'topology_changed'):
      graph = args[1]
    elif 'graph' in kwargs:
      graph = kwargs['graph']
    else:
      raise TypeError('You should provide an graph to the method %r. args:(%r,%r)' % (method, args, kwargs))
    return_value = method(*args, **kwargs)
    graph.topology_changed = True
    return return_value
  return newMethod

#TODO
#deleteCustomProperty
#appendAppendProperty
#deleteNodePermanently
#deleteNodePermanentlyFast (use a fast method to delete node created in an action node)
class GraphManager(FrameworkBase):
  def __post_init__(self):
    self.prop_mngr = GraphPropertyManager(self.context)
    self.topo_mngr = GraphTopologyManager(self.context)
    self.node_mngr = NodeManager(self.context)
    self.plugins_mngr = PluginsManager(self.context)

  @topology_changed
  def createNode(self, graph, processor): #TODO: add support for debugging version
    #create the node proxy
    node = self.node_mngr.new(processor)
    #Add the node to the graph
    graph.addNode(node)
    #sychronize node and inner pipeline
    self.__syncNode(graph.pline, node)
    #return new node
    return node

  @topology_changed
  def deleteNode(self, graph, node):
    node_id = node.node_id
    raise NotImplementedError()

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

  @topology_changed
  def connect(self, graph, dent_prop, dency_prop):
    return self.topo_mngr.connect(graph.pline, dent_prop, dency_prop)

  @topology_changed
  def disconnect(self, graph, dent_prop, dency_prop=None):
    return self.topo_mngr.disconnect(graph.pline, dent_prop, dency_prop)

  @topology_changed
  def auto_connect(self, graph, dent_node, dency_node):
    inputs_names = dent_node.inputs.get_properties().keys()
    outputs_names = dency_node.outputs.get_properties().keys()
    self.log.debug('Autoconnecting in:%s out:%s' % (inputs_names, outputs_names))
    for name in outputs_names:
      if name in inputs_names:
        self.topo_mngr.connect(graph.pline
                                  , getattr(dent_node.inputs, name)
                                  , getattr(dency_node.outputs, name))

#  def syncNode(self, graph, node): #TODO: what is this used for? for node reloading?
#    #update the new data types to be loaded
#    self.plugins_mngr.processor_plugins_manager.load_processors_data_types(node)
#    #Set the new data types property_id to the node
#    self.plugins_mngr.processor_plugins_manager.set_containers_dtype_id(node)
#    #Now we can sync the node as if it were a new one
#    self.__syncNode(graph.pline, node)
