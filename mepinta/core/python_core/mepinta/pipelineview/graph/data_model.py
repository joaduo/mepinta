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
    Node don't have a twin representation on the lo layer.
  '''
  def __init__(self, name, processor):
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
    self.nodes = dict() #id:Node


