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
    '''

    def __init__(self):
        #Wrapped graph
        self._graph = None
        self.topology_changed = False
        # List of Nodes (pipelineview)
        # On each action in ActionTree we save the list of nodes created
        # So we later can find them (by order of creation)
        self._created_nodes = list()  # (node)
        # old_properties what for? (TODO: remove, we will schedule for deletion)
        self.old_properties = dict()  # prop_id:value
        # Action's topology id (State of the graph at Action's stage)
        self.topology_id = NULL_UID  # graph.growTopologies()

    def startTopologyChangeSet(self):
        if self.topology_id == NULL_UID:
            self.topology_id = self._graph.pline.startTopologyChangeSet()

    def resetTopology(self, u_graph):
        '''
        In a modifier processor (for example) we need to reset the
        output_undoable_graph with the value of the input_undoable_graph
        this method lets you do exactly that.
        '''
        pline = u_graph.pline
        if pline.pendingChanges():  # TODO: remove?
            raise RuntimeError(
                'There are pending changes you should propagate changes')
        # Copy the current topology into the topology pointed by this
        # undoable_graph
        # We directly operato over the input pipeline, since this
        # data is intended to operate non-cached
        copied_topo = pline.getTopology()
        topo = pline.getTopology(self.topology_id)
        topo.copyFrom(copied_topo)
        pline.setCurrentTopologyId(self.topology_id)

    def addNode(self, node):
        self._created_nodes.append(node)
        self._graph.addNode(node)

    def deleteNode(self, node):
        if node in self._created_nodes and \
           node in self._graph.nodes:
            self._created_nodes.remove(node)
            self._graph.nodes.removeNode(node)
        raise KeyError(
            'Node %r seems not to be consistent in the _graph' % node)

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
    def createdNodes(self):
        return self._created_nodes

    def setGraph(self, graph):
        if self._graph == None:
            self._graph = graph
            self.startTopologyChangeSet()
        elif self._graph != graph:
            # TODO: remove?
            raise RuntimeError('Graph should always be the same')


def testModule():
    from getDefaultContext import getDefaultContext
    context = getDefaultContext()

if __name__ == "__main__":
    testModule()
