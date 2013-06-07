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

class ActionRootNode(object):
  def __init__(self):
    self.parent = None
    self.children = []

  def newChild(self, graph_node):
    node = ActionNode(self, graph_node)
    self.children.append(node)
    return node

class ActionNode(ActionRootNode):
  def __init__(self, parent, graph_node):
    self.parent = parent
    self.graph_node = graph_node
    self.children = []


class ActionTree(object):
  def __init__(self):
    self.root_node = ActionRootNode()
    self.current_node = self.root_node
    self.graph = None


  def appendActionNode(self, graph_node):
    self.current_node = self.current_node.newChild(graph_node)

#from mepinta.pipeline.lo.pipeline_data.data_model import Pipeline
#
##TODO: memory limits? other choices? or should they go to config?
#class ActionTree:
#  def __init__(self):
#    self.metapipeline = Pipeline(copied=True)
#    self.nodes = {} #id:Node
#    self.current_node = None
