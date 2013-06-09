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
from pipeline_backend.logging.logging import log_debug

class ConditionalBDGraph:
  def __init__(self):
    self.dpdencies = DirectedGraph()
    self.dpdents = DirectedGraph()
  def connectDency(self,dent_id, dency_id):
    if not self.dpdencies.has(dent_id, dency_id):
      self.dpdencies.add(dent_id, dency_id)
  def connectDent(self,dent_id, dency_id):
    if not self.dpdents.has(dency_id, dent_id):
      self.dpdents.add(dency_id, dent_id)
  def connect(self, dent_id, dency_id):
    if not self.dpdencies.has(dent_id, dency_id):
      self.dpdencies.add(dent_id, dency_id)
    if not self.dpdents.has(dency_id, dent_id):
      self.dpdents.add(dency_id, dent_id)
  def disconnect(self, dent_id, dency_id):
    if self.dpdencies.has(dent_id, dency_id):
      self.dpdencies.remove(dent_id, dency_id)
    if self.dpdents.has(dency_id, dent_id):
      self.dpdents.remove(dency_id, dent_id)
  def disconnectAll(self, prop_id):
    self.disconnectDpdencies(prop_id)
    #return changed ids
    return self.disconnectDpdents(prop_id)
  def disconnectDpdencies(self, dent_id):
    log_debug('Disconnecting property: %s'%dent_id)
    for dency_id in self.dpdencies[dent_id]: #for each dependency we delete the dency_id:dent_id relations
      if self.dpdents.has(dency_id, dent_id):
        self.dpdents.remove(dency_id,dent_id)
    self.dpdencies.__delitem__(dent_id) #we delete the dent_id:dency_id relations
  def disconnectDpdents(self, dency_id):
    dents_ids = self.dpdents[dency_id]
    log_debug('Disconnecting property: %s'%dency_id)
    for dent_id in dents_ids: #for each dependency we delete the dent_id:dency_id relations
      if self.dpdencies.has(dent_id, dency_id):
        self.dpdencies.remove(dent_id,dency_id)
    self.dpdents.__delitem__(dency_id) #we delete the dency_id:dent_id relations
    return dents_ids
  def __str__(self):
    return '%s: Dents %s | Dencies %s'%(self.__class__.__name__,self.dpdencies,self.dpdents)
  def __len__(self):
    return len(self.dpdencies)

        
def shedskin_ConditionalBDGraph():
  cbdg = ConditionalBDGraph()
  dent_id=1
  dency_id=2
  cbdg.connectDency(dent_id, dency_id)
  cbdg.connectDent(dent_id, dency_id)
  cbdg.connect(dent_id, dency_id)
  cbdg.disconnect(dent_id, dency_id)
  cbdg.disconnectDpdencies(dent_id)
  cbdg.disconnectDpdencies(dent_id)
  cbdg.disconnectAll(prop_id=1)
  cbdg.__str__()
  cbdg.__len__()

