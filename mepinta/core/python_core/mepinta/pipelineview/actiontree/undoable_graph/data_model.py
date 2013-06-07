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
  def __init__(self):
    self.__graph = None
    self.topology_changed = False
    self.created_nodes = set() #(node)
    self.old_properties = dict() #prop_id:value
    self.topology_id = NULL_UID #graph.growTopologies()

  def startTopologyChangeSet(self):
    if self.topology_id == NULL_UID:
      self.topology_id = self.__graph.pline.startTopologyChangeSet()

  def resetTopology(self, u_graph):
    if self.topology_id != NULL_UID:
      pline = u_graph.pline
      if pline.pendingChanges(): #TODO: remove?
        raise RuntimeError('There are pending changes you should propagate changes')
      copied_topo = pline.getTopology()
      topo = pline.getTopology(self.topology_id)
      topo.copyFrom(copied_topo)
      pline.setCurrentTopologyId(self.topology_id)

  def addNode(self, node):
    self.created_nodes.add(node)
    self.__graph.addNode(node)

  def deleteNode(self, node):
    if node in self.created_nodes and \
       node in self.__graph.all_nodes:
      self.created_nodes.remove(node)
      self.__graph.all_nodes.removeNode(node)
    raise KeyError('Node %r seems not to be consistent in the __graph' % node)

  @property
  def all_nodes(self):
    return self.__graph.all_nodes

  @property
  def pline(self):
    return self.__graph.pline

  @property
  def graph(self):
    return self.__graph

  def setGraph(self, graph):
    self.__graph = graph

def test_module():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  test_module()
