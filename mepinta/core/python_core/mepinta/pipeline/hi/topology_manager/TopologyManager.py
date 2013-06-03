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
from mepinta.pipeline.lo.constants import INPUT_PROPERTY_FLAG
from mepinta.pipeline.hi.base import HiAutoBase, unwrap_decorator
from mepinta.abstract.MepintaError import MepintaError

def convert_pline_to_topo(method):
  method_name = method.__name__
  method = unwrap_decorator(method)
  def method_wrapper(self, *a, **ad):
    if method_name.startswith('_') and method_name.endswith('_safe'):
      if not ('topo' in ad and hasattr(ad['topo'], 'get_topology') \
      or len(a) > 0 and hasattr(a[0], 'get_topology')):
        raise MepintaError("You should provide a Pipeline instead of a Topology to safe checking functions")
      return method(self, *a, **ad)
    else:
      if 'topo' in ad and hasattr(ad['topo'], 'get_topology'):
        ad['topo'] = ad['topo'].get_topology()
      elif len(a) > 0 and hasattr(a[0], 'get_topology'):
        a = list(a)
        a[0] = a[0].get_topology()
      return method(self, *a, **ad)
  return method_wrapper

class TopologyManager(HiAutoBase):
  #Multiple Properties Functions, needs convert_pline_to_topo, to convert pline into topo
  @convert_pline_to_topo
  def remove_properties(self, pline, props): #There is no need for safe checking is already made at lower level
    return self.wrapped.remove_properties(pline, props)
  @convert_pline_to_topo
  def _add_properties_safe(self, pline, props):
    filter_func = lambda prop: prop not in pline.all_properties
    return {filter_func:props}
  @convert_pline_to_topo
  def add_properties(self, pline, props):
    self.wrapped.add_properties(pline, props)
  @convert_pline_to_topo
  def _connect_properties_safe(self, pline, dpdents, dpdencies):
    def filter_valid_connections(dent_id):
      if len(pline.get_topology().connections.dpdencies.__getitem__(dent_id)) > 0:
        dent_prop = pline.all_properties[dent_id]
        if dent_prop.type == INPUT_PROPERTY_FLAG:
          raise RuntimeError("You shouldn't connect one input property to more than one output.")
    filter_func = lambda prop: prop not in pline.get_topology().properties
    return {filter_func:dpdents + dpdencies, filter_valid_connections:dpdents}
  @convert_pline_to_topo
  def connect_properties(self, pline, dpdents, dpdencies):
    return self.wrapped.connect_properties(pline, dpdents, dpdencies)
  _connect_props_dencies_safe = _connect_properties_safe
  @convert_pline_to_topo
  def connect_props_dencies(self, pline, dpdents, dpdencies):
    return self.wrapped.connect_props_dencies(pline, dpdents, dpdencies)
  _connect_props_dents_safe = _connect_properties_safe
  @convert_pline_to_topo
  def connect_props_dents(self, pline, dpdents, dpdencies):
    return self.wrapped.connect_props_dents(pline, dpdents, dpdencies)
  @convert_pline_to_topo
  def disconnect_properties(self, pline, dpdents, dpdencies):
    return self.wrapped.disconnect_properties(pline, dpdents, dpdencies)
  @convert_pline_to_topo
  def enable_cached(self, pline, props):
    self.wrapped.enable_cached(pline, props)
  @convert_pline_to_topo
  def disable_cached(self, pline, props):
    self.wrapped.disable_cached(pline, props)

  #Single Property Functions, No need to unwrap HiAutoBase does the job
  def connect(self, pline, dpdent, dency):
    return self.connect_properties(pline, [dpdent], [dency])
  def disconnect(self, pline, dpdent, dency=None):
    if dency == None:
      return self.disconnect_properties(pline, [dpdent], [])
    else:
      return self.disconnect_properties(pline, [dpdent], [dency])
  def remove(self, pline, prop):
    return self.remove_properties(pline, [prop])
  def add(self, pline, prop):
    return self.add_properties(pline, [prop])

if __name__ == '__main__':
  from mepinta.context.MepintaContext import MepintaContext
  from mepinta.pipeline.hi.pipeline_data.data_model import Pipeline
  from mepinta.pipeline.hi.property_manager.PropertyManager import PropertyManager
  context = MepintaContext('python')
  pline = Pipeline(context=context)
  pline.grow()
  print(pline.get_topology())
  propm = PropertyManager(context=context)
  print(propm)
  print(propm.context.context_lo.data_types)
#  propm._create_properties_safe(pline, 'input', ['hello'], [1])
  print(pline.all_properties)
  prop_ids = propm.create_properties(pline, 'input', ['hello', 'bye'], [0, 0])
  print(pline.all_properties)
  topom = TopologyManager(context=context)
  print(topom)
  topom.add_properties(pline, prop_ids)
#  topom.connect_properties(pline, [1], [2])
#  topo = pline.get_topology()
#  print(topo)
#  topom.add(pline, 3)
##  topom.connect_properties(pline, [3,3,4,5], [4,5,7,8])
#  print(topo)
