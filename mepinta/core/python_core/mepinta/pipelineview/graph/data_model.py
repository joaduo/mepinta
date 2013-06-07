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
from mepinta.pipeline.hi.pipeline_data.data_model import Pipeline
from common.abstract.FrameworkBase import FrameworkBase

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

  def __cloneFromManifest(self, processor_proxy):
    '''
      Given a processor proxy the node clones the processor's topology
      and options.
    '''
    #TODO: automate this in order to maintain it from the ProcessorProxy perspective ?
    processor_proxy = deepcopy(processor_proxy)
    self.containers = processor_proxy.containers
    self.inputs = processor_proxy.inputs
    self.internals = processor_proxy.internals
    self.outputs = processor_proxy.outputs
    self.functions = processor_proxy.functions
    self.non_cached_capable = processor_proxy.non_cached_capable
    self.marked_outputs = processor_proxy.marked_outputs
    self.getRequiredDataTypes = processor_proxy.getRequiredDataTypes

  def __str__(self):
    return 'Node(%r,%r)' % (self.name, self.processor)

  def __repr__(self):
    return '<%r %s>' % (self.name, object.__repr__(self))

class Graph(FrameworkBase):
  def __post_init__(self):
    self.pline = Pipeline(self.context)
    self.__node_count = 0
    self.topology_changed = False
    self.all_nodes = dict()#NodesDictionary(self.context)

  def addNode(self, node):
    node_id = self.__newNodeId()
    self.all_nodes[node_id] = node
    node.node_id = node_id

  def __newNodeId(self):
    self.__node_count += 1
    return self.__node_count


#TODO: remove
#class NodesDictionary(FrameworkBase):
#  def __post_init__(self):
#    self.__id_node_dict = dict()
#    self.__name_node_dict = dict()
#
#  def __contains__(self, x):
#    if isinstance(x, int):
#      return x in self.__id_node_dict
#    elif isinstance(x, str):
#      return x in self.__name_node_dict
#    elif isinstance(x, Node):
#      return x.node_id in self.__id_node_dict
#    else:
#      raise KeyError('Cannot check node %r of type %r' % (x, type(x)))
#
#  def __iter__(self):
#    raise NotImplementedError()
#
#  def addNode(self, node):
#    if node.node_id not in self.__id_node_dict:
#      self.__id_node_dict[node.node_id] = node
#      self.__name_node_dict[node.name] = node
#    else:
#      raise KeyError('Node %r already exists with that id' % node)
#
#  def removeNode(self, node):
#    #Remove from Id table
#    if node.node_id in self.__id_node_dict:
#      del self.__id_node_dict[node.node_id]
#    else:
#      raise KeyError('Node %r doesn\'t exist with that id' % node)
#    #Remove from names table
#    if node.name in self.__name_node_dict:
#      if node == self.__name_node_dict[node.name]:
#        del self.__name_node_dict[node.name]
#    elif node in self.__name_node_dict.values():
#      self.log.w('For node %r name and self.__name_node_dict is not in synchro' % node)
#      for nm, nd in self.__name_node_dict.items():
#        if nd == node:
#          del self.__name_node_dict[nm]
#          continue
#
#  def getNodeById(self, id_):
#    return self.__id_node_dict[id_]
#
#  def getNodeByName(self, name):
#    return self.__name_node_dict[name]
#
#  def getNodesList(self):
#    return self.__id_node_dict.values()
#
#  def getNodesNames(self):
#    return self.__name_node_dict.keys()
