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

from pipeline_backend.logging.logging import log_debug

class ManyChangesFilterPropagationManager(object):
  def __init__(self, pline_evaluator):
    self.pline_evaluator = pline_evaluator
    self.on_change_ppgtino_mngr = OneChangeFilterPropagationManager(pline_evaluator)
  def propagate_changes(self, pline):
    log_debug('Beware, this propagation manager is very inefficient for many changes at different levels of filters. Use it only for animation and changing few "root" values.')
    changed_primary = set()
    changed_primary.update(pline.changed_primary)
    pline.changed_primary.clear()
    for p_id in changed_primary:
      pline.changed_primary.add(p_id)
      self.on_change_ppgtino_mngr.propagate_changes(pline)
      log_debug('After propagating for p_id=%r primary=%r secondary=%r'%(p_id,pline.changed_primary,pline.changed_secondary))
    log_debug('After propagating for all primary=%r secondary=%r changed_track=%r'%(pline.changed_primary, pline.changed_secondary, pline.changed_track))
      
class OneChangeFilterPropagationManager(object):
  def __init__(self, pline_evaluator):
    self.pline_evaluator = pline_evaluator  
  def propagate_changes(self, pline):
    log_debug('Propagating pline.changed_primary -> pline.changed_secondary. With propagation filters')
    if len(pline.changed_primary) == 1:
      ppgation_filters = set()
      prior_ppgation_filters = set()
      changed_secondary_global = set()
      #Propagate primary changes until we reach a propagation filter
      self.propagate_recursively(pline, pline.changed_primary, pline.changed_secondary, ppgation_filters)
      pline.changed_track.update(pline.changed_secondary)
      changed_secondary_global.update(pline.changed_secondary) #We save for the final state of changed_secondary
      while len(ppgation_filters) != 0:
        log_debug('Propagation filters: %r'%ppgation_filters)
        for p_id in ppgation_filters:
          prop = pline.all_properties[p_id]
          #Each evaluation returns a set of changed properties id. We will later propagate this changes
          changed_set = self.pline_evaluator.eval_function(pline,p_id,prop)
          if changed_set != None:
            if len(changed_set) > 0:
              log_debug('Property marked_outputs id=%r is propagating in %r output properties'%(p_id,len(changed_set)))
            pline.changed_primary.update(changed_set)
        log_debug('After propagation filter evaluation. pline.changed_primary=%r'%pline.changed_primary)
        prior_ppgation_filters.update(ppgation_filters)
        ppgation_filters.clear()
        if len(pline.changed_primary) > 0:
          pline.changed_secondary.clear() #We reset the prior propagation, to avoid redundant evaluations
          self.propagate_recursively(pline, pline.changed_primary, pline.changed_secondary, ppgation_filters)
          pline.changed_track.update(pline.changed_secondary)
          changed_secondary_global.update(pline.changed_secondary) #We save for the final state of changed_secondary
          pline.changed_track.difference_update(prior_ppgation_filters) #We need to avoid cyclic propagation
        else:
          break
      #Restore the final state of changed_secondary
      pline.changed_secondary = changed_secondary_global
    elif len(pline.changed_primary) == 0:
      return
    else:
      raise RuntimeError('This propagation class only supports one or zero change at a time. Use this propagation method for animation evaluation.')
  def propagate_recursively(self,pline, changed, changed_ppgation, ppgation_filters):
    prop_id = changed.pop()
    affected_props = set()
    self.get_all_affected_props(pline, prop_id, affected_props, ppgation_filters)
    changed.difference_update(affected_props) #Take out those visited properties
    changed_ppgation.update(affected_props) #Mark those changed properties
    if len(changed) > 0:
      self.propagate_recursively(pline, changed, changed_ppgation, ppgation_filters)
  def get_all_affected_props(self,pline, prop_id, affected_props, ppgation_filters):
    if prop_id in affected_props:
      return
    if prop_id in pline.marked_outputs:
      ppgation_filters.add(prop_id)
      affected_props.add(prop_id)
      return
    affected_props.add(prop_id)
    dents = pline.dpdents[prop_id]
    for dent_id in dents:
      self.get_all_affected_props(pline, dent_id, affected_props, ppgation_filters)
