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

#from mepinta.pipeline.lo.pipeline_data.data_model import Topology

class SimplePropagationManager(object):
  '''
    The properties affected by operations on the topo graph are registered on the
      "topo.changed_primary" set. (changing topology and changing properties' values)
    After registering all changes for operations on the topo graph we propagate
      this changes to all the dependents affected by them.
      Then they are stored in the set "topo.changed_secondary"
    Now we can keep track of the properties affected by the set of operations on a first order topo.
    These means that when we move on the second order topo (action tree),
      we know which Node have changed_primary after applying or undoing a set
      of operations. Those changes are stored in "topo.changed_track"
    When we evaluate properties, we check if the property is in "changed_track" set.
      Evaluating it and then removing it.
    When we move on the second order pipeline, we add the changes on "topo.changed_primary" to the
      "changed_track" from the node we go by. (supposing we are crossing severals nodes until we reach
      a new working node in the action tree).
  '''
  def __init__(self, pline_evaluator):
    pass
    #self.pline_evaluator = pline_evaluator
  def propagate_changes(self, pline):
    #for prop_id in pline.changed_primary:
    if len(pline.changed_primary) > 0:
      self.__recursivePropagation(pline.getTopology(), pline.changed_primary, pline.changed_track)
  def __recursivePropagation(self, topo, changed, changed_ppgation):
    prop_id = changed.pop()
    affected_props = set()
    self.__allAffectedProps(topo, prop_id, affected_props)
    changed.difference_update(affected_props)
    changed_ppgation.update(affected_props)
    if len(changed) > 0:
      self.__recursivePropagation(topo, changed, changed_ppgation)
  def __allAffectedProps(self, topo, prop_id, affected_props):
    if prop_id in affected_props:
      return
    affected_props.add(prop_id)
    dents = topo.connections.dpdents[prop_id]
    for dent_id in dents:
      self.__allAffectedProps(topo, dent_id, affected_props)


def shedskin_SimplePropagationManager(pline, pline_evaluator):
  spm = SimplePropagationManager(pline_evaluator)
  spm.propagate_changes(pline)

#if __name__ == '__main__':
#  spm = SimplePropagationManager(None)
#  pline = Topology()
#  pline.add_property(1)
#  print(pline.changed_primary, pline.changed_secondary)
#  pline.add_property(2)
#  pline.connect(1, 2)
#  pline.changed_primary.add(2)
#  print(pline.changed_primary, pline.changed_secondary)
#  spm.propagate_changes(pline)
#  print(pline.changed_primary, pline.changed_secondary)

