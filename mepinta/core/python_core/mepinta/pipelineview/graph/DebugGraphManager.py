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
from common.abstract.FrameworkBase import FrameworkBase
from mepinta.pipelineview.graph.GraphManager import GraphManager

class DebugGraphManager(FrameworkBase):
  def __post_init__(self):
    self.graph_mngr = GraphManager(self.context)

  def __checkRepr(self, graph, node):
    assert node in graph.allNodes.keys()
    #every prop has its id in the pipeline and in the topology
    #assert node.
  def createNode(self, graph, processor): #TODO: add support for debugging version
    node = self.graph_mngr.createNode(graph, processor)
    #return new node
    return node

  def deleteNode(self, graph, node):
    ret_val = self.deleteNode(graph, node)
    raise ret_val

  def connect(self, graph, dent_prop, dency_prop):
    return self.graph_mngr.connect(graph, dent_prop, dency_prop)

  def disconnect(self, graph, dent_prop, dency_prop=None):
    return self.graph_mngr.disconnect(graph, dent_prop, dency_prop)

  def autoConnect(self, graph, dent_node, dency_node):
    return self.graph_mngr.autoConnect(graph, dent_node, dency_node)
