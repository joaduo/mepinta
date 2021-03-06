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


def unwrap(wrapper):
    if hasattr(wrapper, '__wrapped__'):
        return wrapper.__wrapped__()
    elif isinstance(wrapper, list):
        return [unwrap(item) for item in wrapper]
    else:
        return wrapper


def topologyChanged(method):
    # TODO check type?
    def newMethod(self, *args, **kwargs):
        if args and hasattr(args[0], 'changed_signal_id'):
            args = list(args)
            graph = args[0] = unwrap(args[0])
        elif 'graph' in kwargs:
            graph = kwargs['graph'] = unwrap(kwargs['graph'])
        else:
            raise TypeError('You should provide an graph to the method %r. args:(%r,%r)' % (
                method, args, kwargs))
        return_value = method(self, *args, **kwargs)
        graph.markTopologyChanged()
        return return_value
    return newMethod

# TODO
# deleteCustomProperty
# appendAppendProperty
# deleteNodePermanently
# deleteNodePermanentlyFast (use a fast method to delete node created in
# an action node)


class GraphManager(FrameworkBase):

    def __post_init__(self):
        self.prop_mngr = GraphPropertyManager(self.context)
        self.topo_mngr = GraphTopologyManager(self.context)
        self.node_mngr = NodeManager(self.context)
        self.plugins_mngr = PluginsManager(self.context)

    @topologyChanged
    # TODO: add support for debugging version
    def createNode(self, graph, processor):
        # create the node proxy
        node = self.node_mngr.new(processor)
        # Add the node to the graph
        graph.addNode(node)
        # sychronize node and inner pipeline
        self._syncNode(graph.pline, node)
        # return new node
        return node

    @topologyChanged
    def deleteNode(self, graph, node):
        node_id = node.node_id
        raise NotImplementedError()

    def _syncNode(self, pline, node):
        # Create the properties on the pline
        prop_ids = self.prop_mngr.createProperties(pline, node)
        # add properties to topology and connect them
        self._syncInTopology(pline, node, prop_ids)
        # Return the node
        return node

    def syncInTopology(self, graph, node):
        prop_ids = node.getPropertiesIds()
        # Sync in new topology an already created node
        self._syncInTopology(graph.pline, node, prop_ids)

    def _syncInTopology(self, pline, node, prop_ids):
        # Connect dpdencies
        self.topo_mngr.addProperties(pline, prop_ids)
        # Make intranode connections
        self.topo_mngr.connectInternally(pline, node)
        # Enable Caching
        self.topo_mngr.enableCached(pline, node)

    @topologyChanged
    def connect(self, graph, dent_prop, dency_prop):
        return self.topo_mngr.connect(graph.pline, dent_prop, dency_prop)

    @topologyChanged
    def disconnect(self, graph, dent_prop, dency_prop=None):
        return self.topo_mngr.disconnect(graph.pline, dent_prop, dency_prop)

    @topologyChanged
    def autoConnect(self, graph, dent_node, dency_node):
        inputs_names = dent_node.inputs.getProperties().keys()
        outputs_names = dency_node.outputs.getProperties().keys()
        self.log.debug('Autoconnecting in:%s out:%s' %
                       (inputs_names, outputs_names))
        for name in outputs_names:
            if name in inputs_names:
                self.topo_mngr.connect(graph.pline, getattr(dent_node.inputs, name)
                                       , getattr(dency_node.outputs, name))

# def syncNode(self, graph, node): #TODO: what is this used for? for node reloading?
# update the new data types to be loaded
#    self.plugins_mngr.processor_plugins_manager.loadProcessorsDataTypes(node)
# Set the new data types property_id to the node
#    self.plugins_mngr.processor_plugins_manager.setContainersDtypeId(node)
# Now we can sync the node as if it were a new one
#    self._syncNode(graph.pline, node)
