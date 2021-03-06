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

from mepinta.pipeline.lo.generic_data.DirectedGraph import DirectedGraph
from pipeline_backend.logging.logging import logDebug
from mepinta.pipeline.lo.generic_data.BiDirectedGraph import BiDirectedGraph


class TopologyConnections:

    '''Stores the Topology's Graph connections. (navigatable in both directions)

    Since these connections can be arbitrary directed, this Object stores a second
    copy of the Graph (self.navigation) with bidirectional information for each
    connection, for navigation through the graph.
    '''

    def __init__(self):
        # TODO: invariants: dpdencies, dpdents should be read-only from outside
        # For navigation purposes (in some cases you may lack the information
        # to navigate in both ways
        self.navigation = BiDirectedGraph()
        # dent_id : dency_id Graph
        self.dpdencies = DirectedGraph()
        # dency_id : dent_id Graph
        self.dpdents = DirectedGraph()

    def connectDency(self, dent_id, dency_id):
        '''
        Unidirectional connection. (dency only: gets the property in its args)
        :param dent_id: dependent property id
        :param dency_id: dependency property id
        '''
        self.navigation.connect(dent_id, dency_id)
        if not self.dpdencies.has(dent_id, dency_id):
            self.dpdencies.add(dent_id, dency_id)

    def connectDent(self, dent_id, dency_id):
        '''
        Unidirectional connection. (dent only: is notified of changes)
        :param dent_id: dependent property id
        :param dency_id: dependency property id
        '''
        self.navigation.connect(dent_id, dency_id)
        if not self.dpdents.has(dency_id, dent_id):
            self.dpdents.add(dency_id, dent_id)

    def connect(self, dent_id, dency_id):
        '''
        Bidirectional connection. (dent + dency)
            (gets the property in its args + is notified of changes)
        :param dent_id: dependent property id
        :param dency_id: dependency property id
        '''
        self.navigation.connect(dent_id, dency_id)
        if not self.dpdencies.has(dent_id, dency_id):
            self.dpdencies.add(dent_id, dency_id)
        if not self.dpdents.has(dency_id, dent_id):
            self.dpdents.add(dency_id, dent_id)

    def disconnect(self, dent_id, dency_id):
        '''
        Disconnect bidirectional, dent or dency connection
        :param dent_id: dependent property id
        :param dency_id: dependency property id
        '''
        self.navigation.disconnect(dent_id, dency_id)
        if self.dpdencies.has(dent_id, dency_id):
            self.dpdencies.remove(dent_id, dency_id)
        if self.dpdents.has(dency_id, dent_id):
            self.dpdents.remove(dency_id, dent_id)

    def disconnectAll(self, prop_id):
        '''
        Disconnect any connection that comes or leaves the property given
        :param prop_id: property id of the property to be totally disconnected
        :returns: the set of dependents affected by the disconnection
        '''
        self.disconnectDpdencies(prop_id)
        # return changed ids
        return self.disconnectDpdents(prop_id)

    def disconnectDpdencies(self, dent_id):
        '''
        Disconnect all dependencies connected to this (dependent) property
        :param dent_id: property id of dependent property
        :returns: None, because there is no dependent affected
        '''
        self.navigation.disconnectDpdencies(dent_id)
        logDebug('Disconnecting property: %s' % dent_id)
        # for each dependency we delete the dency_id:dent_id relations
        for dency_id in self.dpdencies[dent_id]:
            if self.dpdents.has(dency_id, dent_id):
                self.dpdents.remove(dency_id, dent_id)
        # we delete the dent_id:dency_id relations
        self.dpdencies.__delitem__(dent_id)

    def disconnectDpdents(self, dency_id):
        '''
        Disconnect all dependents connected to this (dependency) property
        :param dency_id: property id of dependency property
        :returns: the set of dependents affected by the disconnection
        '''
        self.navigation.disconnectDpdents(dency_id)
        dents_ids = self.dpdents[dency_id]
        logDebug('Disconnecting property: %s' % dency_id)
        # for each dependency we delete the dent_id:dency_id relations
        for dent_id in dents_ids:
            if self.dpdencies.has(dent_id, dency_id):
                self.dpdencies.remove(dent_id, dency_id)
        # we delete the dency_id:dent_id relations
        self.dpdents.__delitem__(dency_id)
        return dents_ids

    def __str__(self):
        return 'TopologyConnections: Dents %s | Dencies %s' % (self.dpdencies, self.dpdents)

    def __len__(self):
        return len(self.navigation)


def shedskin_TopologyConnections():
    cbdg = TopologyConnections()
    dent_id = 1
    dency_id = 2
    cbdg.connectDency(dent_id, dency_id)
    cbdg.connectDent(dent_id, dency_id)
    cbdg.connect(dent_id, dency_id)
    cbdg.disconnect(dent_id, dency_id)
    cbdg.disconnectDpdencies(dent_id)
    cbdg.disconnectDpdencies(dent_id)
    cbdg.disconnectAll(prop_id=1)
    cbdg.__str__()
    cbdg.__len__()
