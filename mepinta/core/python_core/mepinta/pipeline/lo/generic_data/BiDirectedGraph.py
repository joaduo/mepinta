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
from pipeline_backend.logging.logging import log_debug

class BiDirectedGraph(object):
  def __init__(self):
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
  def disconnect_all(self, prop_id):
    self.disconnect_dpdencies(prop_id)
    #return changed ids
    return self.disconnect_dpdents(prop_id)
  def disconnect_dpdencies(self, dent_id):
    log_debug('Disconnecting property: %s'%dent_id)
    for dency_id in self.dpdencies[dent_id]: #for each dependency we delete the dency_id:dent_id relations
      self.dpdents.remove(dency_id,dent_id)
    self.dpdencies.__delitem__(dent_id) #we delete the dent_id:dency_id relations
  def disconnect_dpdents(self, dency_id):
    dents_ids = self.dpdents[dency_id]
    log_debug('Disconnecting property: %s'%dency_id)
    for dent_id in dents_ids: #for each dependency we delete the dent_id:dency_id relations
      self.dpdencies.remove(dent_id,dency_id)
    self.dpdents.__delitem__(dency_id) #we delete the dency_id:dent_id relations
    return dents_ids
  def __str__(self):
    return self.dpdencies.__str__()
  def __len__(self):
    return len(self.dpdencies)

def shedskin_BiDirectedGraph():
  bdg = BiDirectedGraph()
  dent_id=1
  dency_id=2
  bdg.connect(dent_id, dency_id)
  bdg.disconnect(dent_id, dency_id)
  bdg.disconnect_dpdencies(dent_id)
  bdg.disconnect_dpdencies(dent_id)
  bdg.disconnect_all(prop_id=1)
  bdg.__str__()
  bdg.__len__()


