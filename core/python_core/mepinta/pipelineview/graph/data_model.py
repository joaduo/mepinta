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
from common.abstract.FrameworkObject import FrameworkObject


class Node(FrameworkObject):

    '''
      A Graph node.
      It's composed by groups of properties (lo.pipeline's properties)
    '''

    def __init__(self, name, processor):
        # There is no superior object to store the id (Node has to store
        # itself)
        self.node_id = 0
        self.name = name
        # TODO: rename to processor_metadata (mdata?)
        self.processor = processor
        # Clone attributes from the proxy
        # (so we can access the inner properties?)
        self.processor.proxy.spawnIntoNode(self)

    def getPropertiesIds(self):
        pass  # for container in self.containers.getProperties()

    def __str__(self):
        return 'Node(%r,%r)' % (self.name, self.processor)

    def __repr__(self):
        return '<%r %s>' % (self.name, object.__repr__(self))


class Graph(FrameworkObject):
    '''
    A graph is an abstract view of a Pipeline (where pline's node are grouped)
    '''

    def __init__(self, pline):
        # Wrapped pipeline from mepinta.pipeline package
        self.pline = pline
        # Node Id count
        self._node_count = 0
        # Increase if topology changed signal
        self._changed_signal_id = 0
        # {id:Node} dict
        self.nodes = dict()

    @property
    def changed_signal_id(self):
        return self._changed_signal_id

    def markTopologyChanged(self):
        self._changed_signal_id += 1

    def addNode(self, node):
        # Repr Check
        assert not node.node_id , 'node already has node_id'
        # Add the new node
        node_id = self.__newNodeId()
        self.nodes[node_id] = node
        node.node_id = node_id

    def __newNodeId(self):
        self._node_count += 1
        return self._node_count
