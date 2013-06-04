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

from mepinta.pipeline.hi.base import unwrap_lo
from mepinta.pipeline.hi.topology_manager.TopologyManager import TopologyManager
from common.abstract.FrameworkBase import FrameworkBase
from mepinta.plugins_manifest.proxy.data_model import FunctionPropertyProxy,\
  InOutPropertyProxyBase

class GraphTopologyManager(FrameworkBase):
  def __post_init__(self, *a, **ad):
    self.topo_mngr = TopologyManager(context=self.context)
  def add_properties(self, pline, prop_ids):
    self.topo_mngr.add_properties(pline, prop_ids)
  def connect(self, pline, dpdent, dency):
    self.topo_mngr.connect(pline, dpdent, dency)
  def disconnect(self, pline, dpdent, dency=None):
    return self.topo_mngr.disconnect(pline, dpdent, dency)
  def connect_internally(self, pline, node):
    dpdents,dpdencies = self.__get_dpdents_dpdencies(node, direction='<>')
    self.topo_mngr.connect_properties(pline, dpdents,dpdencies)
    dpdents,dpdencies = self.__get_dpdents_dpdencies(node, direction='<')
    self.topo_mngr.connect_props_dents(pline, dpdents,dpdencies)
    dpdents,dpdencies = self.__get_dpdents_dpdencies(node, direction='>')
    self.topo_mngr.connect_props_dencies(pline, dpdents,dpdencies)
  def __get_dpdents_dpdencies(self, node, direction):
    dpdents = []; dpdencies = []
    self.__dpdents_dpdencies(node.inputs,    dpdents,dpdencies, direction)
    self.__dpdents_dpdencies(node.internals, dpdents,dpdencies, direction)
    self.__dpdents_dpdencies(node.outputs,   dpdents,dpdencies, direction)
    self.__dpdents_dpdencies(node.functions, dpdents,dpdencies, direction, type_=FunctionPropertyProxy)
    return dpdents,dpdencies
  def __dpdents_dpdencies(self, container, dpdents,dpdencies , direction, type_=InOutPropertyProxyBase): 
    for prop in container.get_properties(type_).values():
      for dency in prop.dpdencies:
        if dency.direction == direction:
          dpdents.append(prop)
          dpdencies.append(dency)
  def remove_node(self, pline, node):
    #prop_ids = [ prop.id for prop in node.inputs.get_properties() ]
    raise RuntimeError("Implement!") #TODO
  def enable_cached(self, pline, node):
    if not self.config.non_cached: #We may want to force non-caching on some node (since it does nothing to the data)    
      dst_src_non_cached = node.non_cached_capable
      if len(dst_src_non_cached) == 0:
        return    
      prop_dst_ids = []
      for dst_prop,_ in dst_src_non_cached:
        prop_dst_ids.append(unwrap_lo(dst_prop))
      #finally enabling them     
      self.topo_mngr.enable_cached(pline, prop_dst_ids)

    
