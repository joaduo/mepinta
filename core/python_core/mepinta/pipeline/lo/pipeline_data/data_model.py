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
from pipeline_backend.solve_symbol.solve_symbol import solveSymbol
from copy import deepcopy
from pipeline_backend.logging.logging import logDebug, logWarning, \
    logCritical
from mepinta.pipeline.lo.constants import FUNCTION_PROPERTY_FLAG, \
    MEPINTA_C_NAMESPACE_PREFIX, NULL_UID
from mepinta.pipeline.lo.generic_data.DirectedGraph import DirectedGraph
from mepinta.pipeline.lo.pipeline_data.TopologyConnections import TopologyConnections
from mepinta.pipeline.lo.exceptions.MepintaLoError import MepintaLoError


class DataType(object):

    def __init__(self, name, lib_handle):
        self.name = name
        self.lib_handle = lib_handle
        #self.path = path
        self.symbols = {}

    def getFuncPtr(self, name):
        if name not in self.symbols:
            self.symbols[name] = self.solveSymbol(name)
        return self.symbols[name]

    def updateHandle(self, lib_handle):  # TODO: should check we never get a null pointer?
        self.lib_handle = lib_handle
        for name in self.symbols:
            self.symbols[name] = self.solveSymbol(name)

    def solveSymbol(self, name):
        return solveSymbol(self.lib_handle, '%s%s_' % (MEPINTA_C_NAMESPACE_PREFIX, self.name), name)

    def __repr__(self):  # TODO: remove
        return repr(self.__str__())

    def __str__(self):
        return self.name


class ProcessorFunction(object):

    def __init__(self, name, func_pointer):
        self.name = name
        self.func_pointer = func_pointer

    def getFuncPointer(self):
        return self.func_pointer

    def updateFuncPointer(self, func_pointer):
        self.func_pointer = func_pointer


class PropertyValuePointer(object):
    # TODO:Remove count?

    def __init__(self, value=None):
        self.count = 0
        self.value = value
        self.function_caller = FunctionCaller()

    def replaceValue(self, value, func_ptr_del):
        self.freeValue(func_ptr_del)
        self.value = value

    def freeValue(self, func_ptr_del):
        if self.value != None:
            if self.function_caller.callFunc(func_ptr_del, self.value) != None:
                msg = 'Couldn\'t free pipeline value for %s. This may mean a memory leak.' % self
                logCritical(msg)
                raise MepintaLoError(msg)

    def getValue(self):
        return self.value

    def incrementReferenceCount(self):
        self.count += 1
        logDebug('Reference count=%r for %r' % (self.count, self))

    def decrementReferenceCount(self, func_ptr_del):
        # TODO: make it thread safe
        self.count -= 1
        # DEBUG:
        if self.count == 0:
            self.freeValue(func_ptr_del)

    def notReferenced(self):
        return self.count == 0


class Property(object):

    def __init__(self, prop_type, name, dtype_id):
        #prop_type ~= prop_flags (flags determine the type of property)
        self.type = prop_type  # 0 Input 1 Output 2 Function 3 Property Set
        self.name = name
        # data type id for solving new,delete and copy
        self.dtype_id = dtype_id
        # Create value pointer, pointing to Null
        self.value_ptr = PropertyValuePointer(value=None)
        # Value pointers do implement reference counting for
        # memory management (and when "stealing" data from an outside property)
        self.value_ptr.incrementReferenceCount()

    def getValue(self):
        return self.value_ptr.getValue()

    def getValuePtr(self):
        return self.value_ptr

    def setValuePtr(self, value_ptr, func_ptr_del=None):
        # DEBUG: #SHEDSKIN:
        #if not isinstance(value_ptr, PropertyValuePointer): raise RuntimeError('PropertyValuePointer are only values allowed')
        if self.value_ptr != value_ptr:
            old_value_ptr = self.value_ptr
            self.value_ptr = value_ptr
            self.value_ptr.incrementReferenceCount()
            old_value_ptr.decrementReferenceCount(func_ptr_del)

    def __repr__(self):  # TODO: remove
        return repr(self.__str__())

    def __str__(self):
        return self.name


class Topology(object):
    # TODO: invariant: prop_id should exist in the pipeline
    # TODO: invariant connection rules?
    # TODO: invariant, check how shedskin deals with them

    def __init__(self, copied=None):
        if copied == None:
            # We are not copying => new topology
            self.__initValues()
        else:
            self.copyFrom(copied)

    def __initValues(self):
        self.properties = set()  # id
        self.connections = TopologyConnections()  # Id:Id tables
        self.cached = set()  # id
        self.changed_primary = set()  # id

    def copyFrom(self, copied_topo):
        # Deepcopies
        self.properties = deepcopy(copied_topo.properties)
        self.connections = deepcopy(copied_topo.connections)
        self.cached = deepcopy(copied_topo.cached)
        # Reset changed status (we are starting topology changes again)
        self.changed_primary = set()  # id

    def connect(self, dent_id, dency_id):
        self.connections.connect(dent_id, dency_id)
        self.changed_primary.add(dent_id)

    def connectDency(self, dent_id, dency_id):
        self.connections.connectDency(dent_id, dency_id)
        # there is no change, since there is no propagation of changes

    def connectDent(self, dent_id, dency_id):
        self.connections.connectDent(dent_id, dency_id)
        self.changed_primary.add(dent_id)

    def disconnect(self, dent_id, dency_id):
        self.connections.disconnect(dent_id, dency_id)
        self.changed_primary.add(dent_id)

    def disconnectAll(self, prop_id):
        # All dependents properties returned by disconnectAll
        # have changed => add to changed_primary
        self.changed_primary.update(
            set(self.connections.disconnectAll(prop_id)))

    def disconnectDpdencies(self, dent_id):
        # Since there is only dependencies affected
        # there is no affected property but only dent_id
        self.connections.disconnectDpdencies(dent_id)
        self.changed_primary.add(dent_id)

    def addPropId(self, prop_id):
        self.properties.add(prop_id)
        self.changed_primary.add(prop_id)

    def removePropId(self, prop_id):
        # Needs to check here because Pipeline won't check
        if prop_id in self.properties:
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
        # id:Property (all the properties, those deleted in a topology too)
        self.all_properties = {}
        # active topology in the pipeline
        self.current_topolgy_id = NULL_UID
        # count to give unique id for each topology
        self.topology_id_count = NULL_UID
        self.topologies = {}  # id:topology (all topologies dictionary
        # outputs that need to be marked when changed (for filtered propagation)
        self.marked_outputs = set()
        # general changed_primary before propagation (the  sum of all changed_primary in the topologies)
        self.changed_primary = set()
        # properties marked as changed (after propagation)
        self.changed_track = set()
        # TODO: check if a dict is better below
        # Its uses DirectedGraph for simplicity reasons, although it could be a
        # dictionary
        # id_dst_prop:id_src_prop #Here because it wont change according to the current topology?? (or it may?) #TODO: review
        self.cached_link = DirectedGraph()
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

    def startNewTopology(self):
        # TODO :review!
        base_topo = self.getTopology()
#    if 0 != len(base_topo.changed_primary):
        self.changed_primary.update(base_topo.changed_primary)
        self.current_topolgy_id = self.__newTopologyId()
        self.topologies[self.current_topolgy_id] = Topology(copied=base_topo)
        return self.current_topolgy_id

    def pendingChanges(self):
        # TODO: return bool(self.getTopology().changed_primary) #check with shedskin
        return 0 != len(self.getTopology().changed_primary)

    def popTopology(self, topo_id):
        if topo_id != self.getCurrentTopologyId():
            # TODO: review if raises exception
            return self.topologies.pop(topo_id)
        else:
            logWarning('You can\'t remove current topology ')
            return None

    def getTopology(self, topo_id=NULL_UID):
        if topo_id == NULL_UID:
            return self.topologies[self.current_topolgy_id]
        else:
            return self.topologies[topo_id]

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
            topo.removePropId(prop_id)
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
    dt.getFuncPtr('symbol searched')
    dt.updateHandle(lib_handle)
    dt.__repr__()
    func_pointer = None
    pf = ProcessorFunction(name, func_pointer)
    pf.getFuncPointer()
    pf.updateFuncPointer(func_pointer)

    pvp = PropertyValuePointer(value=None)
    func_ptr_del = func_pointer
    pvp.replaceValue(value=None, func_ptr_del=func_ptr_del)
    pvp.freeValue(func_ptr_del)
    pvp.getValue()
    pvp.incrementReferenceCount()
    pvp.decrementReferenceCount(func_ptr_del)
    pvp.notReferenced()

    dtype_id = 1
    prop = Property(FUNCTION_PROPERTY_FLAG, name, dtype_id)
    prop.getValue()
    prop.getValuePtr()
    prop.setValuePtr(pvp, func_ptr_del)
    prop.__repr__()

    pline = Pipeline(name='actiontree')
    pline.addProperty(prop)
    topo_id = 1
    pline.setCurrentTopologyId(topo_id)

    topo = Topology()
    topo = Topology(copied=topo)
    topo.copyFrom(copied_topo=topo)
    topo.addPropId(prop_id=1)
    topo.addPropId(prop_id=2)
    topo.connect(dent_id=1, dency_id=2)
    topo.disconnect(dent_id=1, dency_id=2)
    topo.disconnectAll(prop_id=1)
    topo.disconnectDpdencies(dent_id=1)
    topo.removePropId(prop_id=1)
    topo.__str__()

    pline.startNewTopology()
    pline.pendingChanges()
    pline.getTopology()
    # pline.set_current_topology() TODO
    pline.popTopology(pline.getCurrentTopologyId())
    prop_id = pline.addProperty(prop)
    pline.changed_track.add(prop_id)
    pline.cached_link.add(prop_id, prop_id)
    pline.marked_outputs.add(prop_id)
    pline.deleteProperty(prop_id)

    # Render a working pipeline
    prop_id = pline.addProperty(prop)

    return pline, prop_id

if __name__ == '__main__':
    shedskin_pipeline_data_model()
    # debugPrint("done")
