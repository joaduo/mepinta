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

class UndoableGraphManager(object):
  def connect(self, graph, dent_prop, dency_prop):
    pass
  def disconnect(self, graph, dent_prop, dency_prop):
    pass
  def disconnectAll(self, graph, dent_prop):
    pass
  def autoConnect(self, graph, dent_node, dency_node):
    pass
  def setPropValue(self, graph, prop, value):
    pass
  def createNode(self, graph, processor, name=''):
    pass
  def deleteNodeByName(self, graph, name):
    pass
  def deleteNode(self, graph, node):
    pass
  def resetTopology(self, graph):
    pass
  def undoPropertiesChanges(self, graph):
    pass

def test_module():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  test_module()
