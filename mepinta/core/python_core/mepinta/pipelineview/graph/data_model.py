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
from copy import deepcopy
from common.abstract.FrameworkObject import FrameworkObject

class Node(FrameworkObject):
  '''
    A Graph node.
    It's composed by groups of properties (lo.pipeline's properties)
  '''
  def __init__(self, name, processor):
    #There is no superior object to store the id (Node has to store it itself)
    self.node_id = 0
    self.name = name
    #TODO: rename to processor_metadata
    self.processor = processor
    self.__cloneFromManifest(self.processor.proxy)

  def __cloneFromManifest(self, proxy):
    '''
      Given a processor proxy the node clones the processor's topology
      and options.
    '''
    #TODO: automate this in order to maintain it from the ProcessorProxy perspective ?
    #TODO: the code below makes the debugger useless!! Why?
    proxy = deepcopy(proxy)
    self.containers = proxy.containers
    self.inputs = proxy.inputs
    self.internals = proxy.internals
    self.outputs = proxy.outputs
    self.functions = proxy.functions
    self.non_cached_capable = proxy.non_cached_capable
    self.marked_outputs = proxy.marked_outputs
    self.getRequiredDataTypes = proxy.getRequiredDataTypes

  def getPropertiesIds(self):
    pass #for container in self.containers.getProperties()

  def __str__(self):
    return 'Node(%r,%r)' % (self.name, self.processor)

  def __repr__(self):
    return '<%r %s>' % (self.name, object.__repr__(self))

class Graph(FrameworkObject):
  def __init__(self, pline):
    self.pline = pline
    self.__node_count = 0
    self.topologyChanged = False
    self.allNodes = dict()#id:Node

  def addNode(self, node):
    #Repr Check
    assert node not in self.allNodes.values(), 'node already in this graph'
    #Add the new node
    node_id = self.__newNodeId()
    self.allNodes[node_id] = node
    node.node_id = node_id

  def __newNodeId(self):
    self.__node_count += 1
    return self.__node_count


