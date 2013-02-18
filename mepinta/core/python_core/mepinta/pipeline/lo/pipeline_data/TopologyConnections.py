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
from mepinta.pipeline.lo.generic_data.BiDirectedGraph import BiDirectedGraph

class TopologyConnections:
  '''Stores the Topology's Graph connections. (navigatable in both directions)
  
  Since these connections can be arbitrary directed, this Object stores a second
  copy of the Graph (self.navigation) with bidirectional information for each 
  connection, for navigation through the graph.
  '''
  def __init__(self):
    #For navigation purposes (in some cases you may lack the information to navigate in both ways
    self.navigation = BiDirectedGraph()
    #dent_id : dency_id Graph
    self.dpdencies = DirectedGraph()
    #dency_id : dent_id Graph
    self.dpdents = DirectedGraph()
  def connect_dency(self,dent_id, dency_id):
    self.navigation.connect(dent_id, dency_id)
    if not self.dpdencies.has(dent_id, dency_id):
      self.dpdencies.add(dent_id, dency_id)
  def connect_dent(self,dent_id, dency_id):
    self.navigation.connect(dent_id, dency_id)
    if not self.dpdents.has(dency_id, dent_id):
      self.dpdents.add(dency_id, dent_id)
  def connect(self, dent_id, dency_id):
    self.navigation.connect(dent_id, dency_id)
    if not self.dpdencies.has(dent_id, dency_id):
      self.dpdencies.add(dent_id, dency_id)
    if not self.dpdents.has(dency_id, dent_id):
      self.dpdents.add(dency_id, dent_id)
  def disconnect(self, dent_id, dency_id):
    self.navigation.disconnect(dent_id, dency_id)
    if self.dpdencies.has(dent_id, dency_id):
      self.dpdencies.remove(dent_id, dency_id)
    if self.dpdents.has(dency_id, dent_id):
      self.dpdents.remove(dency_id, dent_id)
  def disconnect_all(self, prop_id):
    self.disconnect_dpdencies(prop_id)
    #return changed ids
    return self.disconnect_dpdents(prop_id)
  def disconnect_dpdencies(self, dent_id):
    self.navigation.disconnect_dpdencies(dent_id)
    log_debug('Disconnecting property: %s'%dent_id)
    for dency_id in self.dpdencies[dent_id]: #for each dependency we delete the dency_id:dent_id relations
      if self.dpdents.has(dency_id, dent_id):
        self.dpdents.remove(dency_id,dent_id)
    self.dpdencies.__delitem__(dent_id) #we delete the dent_id:dency_id relations
  def disconnect_dpdents(self, dency_id):
    self.navigation.disconnect_dpdents(dency_id)
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

        
def shedskin_TopologyConnections():
  cbdg = TopologyConnections()
  dent_id=1
  dency_id=2
  cbdg.connect_dency(dent_id, dency_id)
  cbdg.connect_dent(dent_id, dency_id)
  cbdg.connect(dent_id, dency_id)
  cbdg.disconnect(dent_id, dency_id)
  cbdg.disconnect_dpdencies(dent_id)
  cbdg.disconnect_dpdencies(dent_id)
  cbdg.disconnect_all(prop_id=1)
  cbdg.__str__()
  cbdg.__len__()

