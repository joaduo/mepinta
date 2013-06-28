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
  def propagateChanges(self, pline):
    if len(pline.changed_primary):
      self.__propagate(pline.getTopology(), pline.changed_primary, pline.changed_track)
  def __propagate(self, topo, changed, changed_ppgation):
    while len(changed):
      prop_id = changed.pop()
      affected_props = set()
      self.__propagateOneChange(topo, prop_id, affected_props)
      changed.difference_update(affected_props)
      changed_ppgation.update(affected_props)
  def __propagateOneChange(self, topo, prop_id, affected_props):
    not_visited = set([prop_id])
    while len(not_visited):
      prop_id = not_visited.pop()
      if prop_id not in affected_props:
        affected_props.add(prop_id)
        not_visited.update(topo.connections.dpdents[prop_id])

def shedskin_SimplePropagationManager(pline, pline_evaluator):
  spm = SimplePropagationManager(pline_evaluator)
  spm.propagateChanges(pline)

