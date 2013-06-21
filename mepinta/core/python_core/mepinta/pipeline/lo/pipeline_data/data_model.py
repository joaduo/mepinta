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
from mepinta.pipeline.lo.FunctionCaller import FunctionCaller
from pipeline_backend.solve_symbol.solve_symbol import solve_symbol
from copy import deepcopy
from pipeline_backend.logging.logging import log_debug, log_warning, \
  log_critical
from mepinta.pipeline.lo.constants import FUNCTION_PROPERTY_FLAG, \
  MEPINTA_C_NAMESPACE_PREFIX, NULL_UID
from mepinta.pipeline.lo.generic_data.DirectedGraph import DirectedGraph
from mepinta.pipeline.lo.pipeline_data.TopologyConnections import TopologyConnections
from mepinta.pipeline.lo.exceptions.MepintaLoError import MepintaLoError

class DataType(object):
  def __init__(self, name, lib_handle):
    self.name = name
    self.lib_handle = lib_handle
    self.symbols = {}
  def get_func_ptr(self, name):
    if name not in self.symbols:
      self.symbols[name] = self.solve_symbol(name)
    return self.symbols[name]
  def update_handle(self, lib_handle): #TODO: should check we never get a null pointer?
    self.lib_handle = lib_handle
    for name in self.symbols:
      self.symbols[name] = self.solve_symbol(name)
  def solve_symbol(self, name):
    return solve_symbol(self.lib_handle, '%s%s_' % (MEPINTA_C_NAMESPACE_PREFIX, self.name), name)
#  def __repr__(self): #TODO: remove
#    return repr(self.__str__())
  def __str__(self):
    return self.name

class ProcessorFunction(object):
  def __init__(self, name, func_pointer):
    self.name = name
    self.func_pointer = func_pointer
  def get_func_pointer(self):
    return self.func_pointer
  def update_func_pointer(self, func_pointer):
    self.func_pointer = func_pointer

class PropertyValuePointer(object):
  #TODO:Remove count?
  def __init__(self, value=None):
    self.count = 0
    self.value = value
    self.function_caller = FunctionCaller()
  def replace_value(self, value, func_ptr_del):
    self.free_value(func_ptr_del)
    self.value = value
  def free_value(self, func_ptr_del):
    if self.value != None:
      if self.function_caller.call_func(func_ptr_del, self.value) != None:
        msg = 'Couldn\'t free pipeline value for %s. This may mean a memory leak.' % self
        log_critical(msg)
        raise MepintaLoError(msg)
  def get_value(self):
    return self.value
  def increment_reference_count(self):
    self.count += 1
    log_debug('Reference count=%r for %r' % (self.count, self))
  def decrement_reference_count(self, func_ptr_del):
    #TODO: make it thread safe
    self.count -= 1
    #DEBUG:
    if self.count == 0:
      self.free_value(func_ptr_del)
  def not_referenced(self):
    return self.count == 0

class Property(object):
  def __init__(self, prop_type, name, dtype_id):
    self.type = prop_type #0 Input 1 Output 2 Function 3 Property Set
    self.name = name
    self.dtype_id = dtype_id #None #Need this for new,delete,copy
    self.value_ptr = PropertyValuePointer(value=None)
    self.value_ptr.increment_reference_count()
  def get_value(self):
    return self.value_ptr.get_value()
  def get_value_ptr(self):
    return self.value_ptr
  def set_value_ptr(self, value_ptr, func_ptr_del=None):
    #DEBUG: #SHEDSKIN:
    #if not isinstance(value_ptr, PropertyValuePointer): raise RuntimeError('PropertyValuePointer are only values allowed')
    if self.value_ptr != value_ptr:
      old_value_ptr = self.value_ptr
      self.value_ptr = value_ptr
      self.value_ptr.increment_reference_count()
      old_value_ptr.decrement_reference_count(func_ptr_del)
#  def __repr__(self): #TODO: remove
#    return repr(self.__str__())
  def __str__(self):
    return self.name

class Topology(object):
  #TODO: invariant: nodes should exist in the pipeline
  #TODO: invariant connection rules?
  #TODO: invariant, check how shedskin deals with them
  def __init__(self, copied=None):
    self.changed_primary = set() #id
    if copied == None: #In order to avoid copied whe copying
      self.__initValues()
    else:
      self.copyFrom(copied)
  def __initValues(self):
    self.properties = set() #id
    self.connections = TopologyConnections() # Id:Id tables
    self.cached = set() #id
  def copyFrom(self, copied_topo):
    #Deepcopies
    self.properties = deepcopy(copied_topo.properties)
    self.connections = deepcopy(copied_topo.connections)
    self.cached = deepcopy(copied_topo.cached)
  def connect(self, dent_id, dency_id):
    self.connections.connect(dent_id, dency_id)
    self.changed_primary.add(dent_id)
  def connectDency(self, dent_id, dency_id):
    self.connections.connectDency(dent_id, dency_id)
    #there is no change, since there is no propagation of changes
  def connectDent(self, dent_id, dency_id):
    self.connections.connectDent(dent_id, dency_id)
    self.changed_primary.add(dent_id)
  def disconnect(self, dent_id, dency_id):
    self.connections.disconnect(dent_id, dency_id)
    self.changed_primary.add(dent_id)
  def disconnectAll(self, prop_id):
    self.changed_primary.update(set(self.connections.disconnectAll(prop_id)))
  def disconnectDpdencies(self, dent_id):
    self.connections.disconnectDpdencies(dent_id)
    self.changed_primary.add(dent_id)
  def addElementId(self, prop_id):
    self.properties.add(prop_id)
    self.changed_primary.add(prop_id)
  def removeElementId(self, prop_id):
    if prop_id in self.properties: #Needs to check here because Pipeline won't check
      self.properties.remove(prop_id)
      self.connections.disconnectAll(prop_id)
      self.__removeFromSet(prop_id, self.cached)
      self.__removeFromSet(prop_id, self.changed_primary)
  def __removeFromSet(self, prop_id, set_):
    if prop_id in set_:
      set_.remove(prop_id)
  def __str__(self):
    if len(self.properties) == 0:
      return 'Empty Topology'
    elif len(self.connections) == 0:
      return '%r with no connections' % self.properties
    else:
      return self.connections.__str__()

class Pipeline(object):
  def __init__(self, name='default'):
    self.name = name
    self.property_id_count = NULL_UID
    self.all_properties = {} #id:Property (all the properties, those deleted in a topology too)
    self.current_topolgy_id = NULL_UID #count to give unique id for each property
    self.topology_id_count = NULL_UID #count to give unique id for each topology
    self.topologies = {} #id:topology (all topologies dictionary
    self.marked_outputs = set() #outputs that need to be marked when changed (for filtered propagation)
    self.changed_track = set() #properties marked as changed
    self.changed_primary = set() #general changed_primary before propagation (the  sum of all changed_primary in the topologies)
    #TODO: check if a dict is better below
    #Its uses DirectedGraph for simplicity reasons, although it could be a dictionary
    self.cached_link = DirectedGraph() #id_dst_prop:id_src_prop #Here because it wont change according to the current topology?? (or it may?) #TODO: review
    self.__initTopo()
  def __initTopo(self):
    self.current_topolgy_id = self.__newTopologyId()
    self.topologies[self.current_topolgy_id] = Topology()
  def __newTopologyId(self):
    self.topology_id_count += 1
    return self.topology_id_count
  def __newPropertyId(self):
    self.property_id_count += 1
    return self.property_id_count
  def startTopologyChangeSet(self):
    #TODO :review!
    base_topo = self.getTopology()
#    if 0 != len(base_topo.changed_primary):
    self.changed_primary.update(base_topo.changed_primary)
    self.current_topolgy_id = self.__newTopologyId()
    self.topologies[self.current_topolgy_id] = Topology(copied=base_topo)
    return self.current_topolgy_id
  def pendingChanges(self):
    return 0 != len(self.getTopology().changed_primary)
  def popTopology(self, topo_id):
    if topo_id != self.getCurrentTopologyId():
      #TODO: review if raises exception
      return self.topologies.pop(topo_id)
    else:
      log_warning('You can\'t remove current topology ')
      return None
  def getTopology(self, topo_id=NULL_UID):
    if topo_id == NULL_UID:
      return self.topologies[self.current_topolgy_id]
    else:
      return self.topologies[topo_id]
  #  def set_current_topology(self, topo_id): #TODO. provide a list of visited topologies #TODO: remove
  #    self.current_topolgy_id = topo_id
  def setCurrentTopologyId(self, topo_id):
    self.current_topolgy_id = topo_id
  def getCurrentTopologyId(self):
    return self.current_topolgy_id
  def addProperty(self, prop):
    prop_id = self.__newPropertyId()
    self.all_properties[prop_id] = prop
    self.changed_track.add(prop_id)
    return prop_id
  def deleteProperty(self, prop_id):
    prop = self.all_properties.pop(prop_id)
    for topo in self.topologies.values():
      topo.removeElementId(prop_id)
    self.cached_link.__delitem__(prop_id)
    if prop_id in self.marked_outputs:
      self.marked_outputs.remove(prop_id)
    if prop_id in self.changed_track:
      self.changed_track.remove(prop_id)
    return prop

def shedskin_pipeline_data_model():
  lib_handle = None
  name = 'name'
  dt = DataType(name, lib_handle)
  dt.get_func_ptr('symbol searched')
  dt.update_handle(lib_handle)
  dt.__repr__()
  func_pointer = None
  pf = ProcessorFunction(name, func_pointer)
  pf.get_func_pointer()
  pf.update_func_pointer(func_pointer)

  pvp = PropertyValuePointer(value=None)
  func_ptr_del = func_pointer
  pvp.replace_value(value=None, func_ptr_del=func_ptr_del)
  pvp.free_value(func_ptr_del)
  pvp.get_value()
  pvp.increment_reference_count()
  pvp.decrement_reference_count(func_ptr_del)
  pvp.not_referenced()

  dtype_id = 1
  prop = Property(FUNCTION_PROPERTY_FLAG, name, dtype_id)
  prop.get_value()
  prop.get_value_ptr()
  prop.set_value_ptr(pvp, func_ptr_del)
  prop.__repr__()

  pline = Pipeline(name='actiontree')
  pline.addProperty(prop)
  topo_id = 1
  pline.setCurrentTopologyId(topo_id)

  topo = Topology()
  topo = Topology(copied=topo)
  topo.copyFrom(copied_topo=topo)
  topo.addElementId(prop_id=1)
  topo.addElementId(prop_id=2)
  topo.connect(dent_id=1, dency_id=2)
  topo.disconnect(dent_id=1, dency_id=2)
  topo.disconnectAll(prop_id=1)
  topo.disconnectDpdencies(dent_id=1)
  topo.removeElementId(prop_id=1)
  topo.__str__()

  pline.startTopologyChangeSet()
  pline.pendingChanges()
  pline.getTopology()
  #pline.set_current_topology() TODO
  pline.popTopology(pline.getCurrentTopologyId())
  prop_id = pline.addProperty(prop)
  pline.changed_track.add(prop_id)
  pline.cached_link.add(prop_id, prop_id)
  pline.marked_outputs.add(prop_id)
  pline.deleteProperty(prop_id)

  #Render a working pipeline
  prop_id = pline.addProperty(prop)

  return pline, prop_id

if __name__ == '__main__':
  shedskin_pipeline_data_model()
  print("done")
