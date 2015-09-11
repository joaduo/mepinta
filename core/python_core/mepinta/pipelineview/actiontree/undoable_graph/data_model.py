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
from common.abstract.FrameworkObject import FrameworkObject
from mepinta.pipeline.lo.constants import NULL_UID


class UndoableGraph(FrameworkObject):
    '''
    UndoableGraph is a graph in which can be "undone" inside an ActionTree
    We keep track of changes so we can propagate them when we undo-redo things
    
    TODO: __init__(graph)
    '''

    def __init__(self):
        # Wrapped graph (we start with None since we need to wait to copyTo
        # to get the underlying graph)
        self._graph = None
        # List of Nodes (pipelineview)
        # On each action in ActionTree we save the list of nodes created (and any other data)
        # So we later can find them (by order of creation)
        self._data_bag = {}
        # old_properties what for? (TODO: remove, we will schedule for deletion)
        self.old_properties = dict()  # prop_id:value
        # Action's topology id (State of the graph at Action's stage)
        self.topology_id = NULL_UID  # graph.startTopologyChangeSet()
        # last topology changed signal number
        self.last_topology_changed = -1

    @property
    def changed_signal_id(self):
        return self._graph.changed_signal_id

    def hasTopologyChanged(self):
        return self.graph.changed_signal_id != self.last_topology_changed

    def acceptTopologyChanged(self):
        self.last_topology_changed = self.graph.changed_signal_id

    def getTopology(self):
        return self.pline.getTopology(self.topology_id)

    def startTopologyChangeSet(self):
        if self.topology_id == NULL_UID:
            self.topology_id = self._graph.pline.startTopologyChangeSet()

    def resetTopology(self, input_graph):
        '''
        In a modifier processor (for example) we need to reset the
        output_undoable_graph with the value of the input_undoable_graph
        this method lets you do exactly that.
        '''
        pline = input_graph.pline
        #if pline.pendingChanges():  # TODO: remove? (No need to propagate primary_changes, they are kept!)
        #    raise RuntimeError(
        #        'There are pending changes you should propagate changes')
        # Copy the current topology into the topology pointed by this
        # undoable_graph
        # We directly operato over the input pipeline, since this
        # data is intended to operate non-cached
        copied_topo = pline.getTopology()
        topo = pline.getTopology(self.topology_id)
        topo.copyFrom(copied_topo)
        pline.setCurrentTopologyId(self.topology_id)

    @property
    def addNode(self):
        return self._graph.addNode

    #TODO: delete?
    #def deleteNode(self, node):
    #    if node in self._data_bag and \
    #       node in self._graph.nodes:
    #        self._data_bag.remove(node)
    #        self._graph.nodes.removeNode(node)
    #    raise KeyError(
    #        'Node %r seems not to be consistent in the _graph' % node)

    @property
    def nodes(self):
        return self._graph.nodes

    @property
    def pline(self):
        return self._graph.pline

    @property
    def graph(self):
        return self._graph

    @property
    def data_bag(self):
        return self._data_bag

    def setGraph(self, graph):
        if self._graph == None:
            self._graph = graph
            self.startTopologyChangeSet()
        elif self._graph != graph:
            # TODO: remove?
            raise RuntimeError('Graph should always be the same')
    
    def __wrapped__(self):
        return self._graph


def testModule():
    from getDefaultContext import getDefaultContext
    context = getDefaultContext()

if __name__ == "__main__":
    testModule()
