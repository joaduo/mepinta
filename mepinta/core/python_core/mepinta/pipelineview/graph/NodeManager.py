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
from mepinta.pipelineview.graph.data_model import Node
from common.abstract.FrameworkBase import FrameworkBase

class NodeManager(FrameworkBase):
  def __post_init__(self):
    self.names_counter = {}
  def new_name(self, processor_name):
    if processor_name not in self.names_counter:
      self.names_counter[processor_name] = 0
    self.names_counter[processor_name] += 1
    count = self.names_counter[processor_name]
    return '%s %s'%(processor_name,count)
  def new(self, processor):
    #makes a copy of the proxy and assigns values to 
    #its properties (id and node proxy)
    #and node (id)
    #adds properties to the context_lo_hi
    #
    node_name = self.new_name(processor.proxy.name)
    self.context.log.debug('Creating a new node %r of type %s'%(node_name, processor))
    node_proxy = Node(node_name, processor)
    return node_proxy
