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
from common.abstract.FrameworkBase import FrameworkBase
from mepinta.pipelineview.graph.GraphManager import GraphManager
from mepinta.pipeline.hi.value_manager.AbstractValueManager import AbstractValueManager
from mepinta.pipeline.hi.FactoryLo import unwrapLo
from mepinta.plugins_manager.PluginsManager import PluginsManager
from mepinta.plugins_manager.data_model import ProcessorMetadata
from mepinta.pipelineview.graph.data_model import Graph
from mepinta.pipeline.hi.pipeline_data.data_model import Pipeline


class UndoableGraphManager(FrameworkBase):

    def __post_init__(self):
        self.graph_manager = GraphManager(self.context)
        self.value_manager = AbstractValueManager(self.context)
        self._plugins_manager = PluginsManager(context=self.context)

    def initGraph(self, u_graph):
        u_graph.setGraph(Graph(Pipeline(self.context)))

    def connect(self, u_graph, dent_prop, dency_prop):
        return self.graph_manager.connect(u_graph, dent_prop, dency_prop)

    def disconnect(self, u_graph, dent_prop, dency_prop):
        return self.graph_manager.disconnect(u_graph, dent_prop, dency_prop)

    def disconnectAll(self, u_graph, dent_prop):
        raise NotImplementedError()  # return self.graph_manager.di

    def autoConnect(self, u_graph, dent_node, dency_node):
        return self.graph_manager.autoConnect(u_graph, dent_node, dency_node)

    def createNode(self, u_graph, processor, name=''):
        if not isinstance(processor, ProcessorMetadata):
            processor = self._plugins_manager.loadProcessor(processor)
        node = self.graph_manager.createNode(u_graph, processor)
        return node

    def deleteNode(self, u_graph, node):
        self.graph_manager.deleteNode(u_graph, node)

    def resetTopology(self, u_graph):
        '''
        When receiving a topology_changed signal, we need to reset the topology.
        :param u_graph:
        '''
        pass

    def getValue(self, u_graph, prop):
        return self.value_manager.getValue(u_graph.pline, prop)

    def setValue(self, u_graph, prop, value):
        old_value = self.value_manager.getValue(u_graph.pline, prop)
        u_graph.old_properties[unwrapLo(prop)] = old_value
        self.value_manager.setValue(u_graph.pline, prop, value)

    def undoValuesChanges(self, u_graph):
        for prop_id, old_value in u_graph.old_properties:
            self.value_manager.setValue(u_graph.pline, prop_id, old_value)

    def getNodeById(self, u_graph, node_id):
        return u_graph.nodes[node_id]


def testModule():
    ugm = UndoableGraphManager()
    from mepinta.pipelineview.actiontree.undoable_graph.data_model import UndoableGraph
    u_graph = UndoableGraph()
    ugm.initGraph(u_graph)
    import plugins.python.processors.demov1.Geometry2D.generator.Circle as processor
    ugm.createNode(u_graph, processor)
    print u_graph.graph.pline.getTopology()
    print u_graph.createdNodes[0]
    n = u_graph.createdNodes[0]
    print n.inputs


if __name__ == "__main__":
    testModule()
