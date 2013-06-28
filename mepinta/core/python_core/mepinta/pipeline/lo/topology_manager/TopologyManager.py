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

from pipeline_backend.logging.logging import logDebug

class TopologyManager(object):
  def __init__(self, context_lo):
    pass
  def addProperties(self, topo, prop_ids):
    for prop_id in prop_ids:
      topo.addPropId(prop_id)
  def removeProperties(self, topo, prop_ids):
    for prop_id in prop_ids:
      topo.removePropId(prop_id)
  def connectProperties(self, topo, prop_dent_ids, prop_dency_ids):
    logDebug('Connecting properties dpdents=%s dpdencies=%s' % (prop_dent_ids, prop_dency_ids))
    for index, dent_id in enumerate(prop_dent_ids):
      dency_id = prop_dency_ids[index]
      topo.connect(dent_id, dency_id)
    #TODO: avoid connecting on normal property to more than one normal property
    #but do this on the higher level
  def connectPropsDencies(self, topo, prop_dent_ids, prop_dency_ids):
    for index, dent_id in enumerate(prop_dent_ids):
      dency_id = prop_dency_ids[index]
      topo.connectDency(dent_id, dency_id)
  def connectPropsDents(self, topo, prop_dent_ids, prop_dency_ids):
    for index, dent_id in enumerate(prop_dent_ids):
      dency_id = prop_dency_ids[index]
      topo.connectDent(dent_id, dency_id)
  def disconnectProperties(self, topo, prop_dent_ids, prop_dency_ids=[]):
    if len(prop_dency_ids) == 0: #disconnect from all its dpdencies
      for dent_id in prop_dent_ids:
        topo.disconnectDpdencies(dent_id)
    else: #disconnect specific sources
      for index, dent_id in enumerate(prop_dent_ids):
        dency_id = prop_dency_ids[index]
        topo.disconnect(dent_id, dency_id)
  def addChanged(self, topo, prop_changed_ids):
    for prop_changed_id in prop_changed_ids:
      topo.changed_primary.add(prop_changed_id)
  def removeChanged(self, topo, prop_changed_ids):
    for prop_changed_id in prop_changed_ids:
      topo.changed_primary.remove(prop_changed_id)
  def enableCached(self, topo, cached_ids):
    #TODO: enabling and disabling caching needs to notify linked dency
    #and linked dency of changing to avoid problems
    #If we steal a value of an unchanged property, we will run into problems
    #fix that situation
    logDebug('Enable caching on %r' % cached_ids)
    for prop_id in cached_ids:
      topo.cached.add(prop_id)
  def disableCached(self, topo, cached_ids):
    #TODO: see previous method notes
    for prop_id in cached_ids:
      if prop_id in topo.cached:
        topo.cached.remove(prop_id)



def shedskin_TopologyManager(context_lo, topo):
  pm = TopologyManager(context_lo)
  prop_ids = [0]
  pm.addChanged(topo, prop_changed_ids=prop_ids)
  pm.addProperties(topo, prop_ids)
  pm.connectProperties(topo, prop_dent_ids=prop_ids, prop_dency_ids=prop_ids)
  pm.connectPropsDencies(topo, prop_dent_ids=prop_ids, prop_dency_ids=prop_ids)
  pm.connectPropsDents(topo, prop_dent_ids=prop_ids, prop_dency_ids=prop_ids)
  pm.disableCached(topo, cached_ids=prop_ids)
  pm.disconnectProperties(topo, prop_dent_ids=prop_ids, prop_dency_ids=prop_ids)
  pm.enableCached(topo, cached_ids=prop_ids)
  pm.removeChanged(topo, prop_changed_ids=prop_ids)
  pm.removeProperties(topo, prop_ids)


if __name__ == '__main__':
  pass
