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

def convertPlineToTopo(method):
  method_name = method.__name__
  method = unwrap_decorator(method)
  def methodWrapper(self, *a, **ad):
    if method_name.startswith('_') and method_name.endswith('_safe'):
      if not ('topo' in ad and hasattr(ad['topo'], 'getTopology') \
              or len(a) > 0 and hasattr(a[0], 'getTopology')):
        raise MepintaError("You should provide a Pipeline instead of a Topology to safe checking functions")
      return method(self, *a, **ad)
    else:
      if 'topo' in ad and hasattr(ad['topo'], 'getTopology'):
        ad['topo'] = ad['topo'].getTopology()
      elif len(a) > 0 and hasattr(a[0], 'getTopology'):
        a = list(a)
        a[0] = a[0].getTopology()
      return method(self, *a, **ad)
  return methodWrapper

class TopologyManager(HiAutoBase):
  #Multiple Properties Functions, needs convertPlineToTopo, to convert pline into topo
  @convertPlineToTopo
  def removeProperties(self, pline, props): #There is no need for safe checking is already made at lower level
    return self.wrapped.removeProperties(pline, props)
  @convertPlineToTopo
  def _addPropertiesSafe(self, pline, props):
    filterFunc = lambda prop: prop not in pline.all_properties
    return {filterFunc:props}
  @convertPlineToTopo
  def addProperties(self, pline, props):
    self.wrapped.addProperties(pline, props)
  @convertPlineToTopo
  def _connectPropertiesSafe(self, pline, dpdents, dpdencies):
    def filterValidConnections(dent_id):
      if len(pline.getTopology().connections.dpdencies.__getitem__(dent_id)) > 0:
        dent_prop = pline.all_properties[dent_id]
        if dent_prop.type == INPUT_PROPERTY_FLAG:
          raise RuntimeError("You shouldn't connect one input property to more than one output.")
    filterFunc = lambda prop: prop not in pline.getTopology().properties
    return {filterFunc:dpdents + dpdencies, filterValidConnections:dpdents}
  @convertPlineToTopo
  def connectProperties(self, pline, dpdents, dpdencies):
    return self.wrapped.connectProperties(pline, dpdents, dpdencies)
  _connect_props_dencies_safe = _connectPropertiesSafe
  @convertPlineToTopo
  def connectPropsDencies(self, pline, dpdents, dpdencies):
    return self.wrapped.connectPropsDencies(pline, dpdents, dpdencies)
  _connect_props_dents_safe = _connectPropertiesSafe
  @convertPlineToTopo
  def connectPropsDents(self, pline, dpdents, dpdencies):
    return self.wrapped.connectPropsDents(pline, dpdents, dpdencies)
  @convertPlineToTopo
  def disconnectProperties(self, pline, dpdents, dpdencies):
    return self.wrapped.disconnectProperties(pline, dpdents, dpdencies)
  @convertPlineToTopo
  def enableCached(self, pline, props):
    self.wrapped.enableCached(pline, props)
  @convertPlineToTopo
  def disableCached(self, pline, props):
    self.wrapped.disableCached(pline, props)

  #Single Property Functions, No need to unwrap HiAutoBase does the job
  def connect(self, pline, dpdent, dency):
    return self.connectProperties(pline, [dpdent], [dency])
  def disconnect(self, pline, dpdent, dency=None):
    if dency == None:
      return self.disconnectProperties(pline, [dpdent], [])
    else:
      return self.disconnectProperties(pline, [dpdent], [dency])
  def remove(self, pline, prop):
    return self.removeProperties(pline, [prop])
  def add(self, pline, prop):
    return self.addProperties(pline, [prop])

if __name__ == '__main__':
  from mepinta.context.MepintaContext import MepintaContext
  from mepinta.pipeline.hi.pipeline_data.data_model import Pipeline
  from mepinta.pipeline.hi.property_manager.PropertyManager import PropertyManager
  context = MepintaContext('python')
  pline = Pipeline(context=context)
  pline.grow()
  debugPrint(pline.getTopology())
  propm = PropertyManager(context=context)
  debugPrint(propm)
  debugPrint(propm.context.context_lo.data_types)
#  propm._createPropertiesSafe(pline, 'input', ['hello'], [1])
  debugPrint(pline.all_properties)
  prop_ids = propm.createProperties(pline, 'input', ['hello', 'bye'], [0, 0])
  debugPrint(pline.all_properties)
  topom = TopologyManager(context=context)
  debugPrint(topom)
  topom.addProperties(pline, prop_ids)
#  topom.connectProperties(pline, [1], [2])
#  topo = pline.getTopology()
#  debugPrint(topo)
#  topom.add(pline, 3)
##  topom.connectProperties(pline, [3,3,4,5], [4,5,7,8])
#  debugPrint(topo)
