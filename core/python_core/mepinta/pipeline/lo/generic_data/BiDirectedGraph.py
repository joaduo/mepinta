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

from mepinta.pipeline.lo.generic_data.DirectedGraph import DirectedGraph
from pipeline_backend.logging.logging import logDebug


class BiDirectedGraph(object):

    def __init__(self):
        # TODO: invariants: dpdencies, dpdents should be read-only from outside
        self.dpdencies = DirectedGraph()
        self.dpdents = DirectedGraph()

    def connect(self, dent_id, dency_id):
        if not self.dpdencies.has(dent_id, dency_id):
            self.dpdencies.add(dent_id, dency_id)
            self.dpdents.add(dency_id, dent_id)

    def disconnect(self, dent_id, dency_id):
        if self.dpdencies.has(dent_id, dency_id):
            self.dpdencies.remove(dent_id, dency_id)
            self.dpdents.remove(dency_id, dent_id)

    def disconnectAll(self, prop_id):
        self.disconnectDpdencies(prop_id)
        # return changed ids
        return self.disconnectDpdents(prop_id)

    def disconnectDpdencies(self, dent_id):
        logDebug('Disconnecting property: %s' % dent_id)
        # for each dependency we delete the dency_id:dent_id relations
        for dency_id in self.dpdencies[dent_id]:
            self.dpdents.remove(dency_id, dent_id)
        # we delete the dent_id:dency_id relations
        self.dpdencies.__delitem__(dent_id)

    def disconnectDpdents(self, dency_id):
        dents_ids = self.dpdents[dency_id]
        logDebug('Disconnecting property: %s' % dency_id)
        # for each dependency we delete the dent_id:dency_id relations
        for dent_id in dents_ids:
            self.dpdencies.remove(dent_id, dency_id)
        # we delete the dency_id:dent_id relations
        self.dpdents.__delitem__(dency_id)
        return dents_ids

    def __str__(self):
        return self.dpdencies.__str__()

    def __len__(self):
        return len(self.dpdencies)


def shedskin_BiDirectedGraph():
    bdg = BiDirectedGraph()
    dent_id = 1
    dency_id = 2
    bdg.connect(dent_id, dency_id)
    bdg.disconnect(dent_id, dency_id)
    bdg.disconnectDpdencies(dent_id)
    bdg.disconnectDpdencies(dent_id)
    bdg.disconnectAll(prop_id=1)
    bdg.__str__()
    bdg.__len__()
