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

from mepinta.pipeline.lo.pipeline_data.hidden_data_types import FunctionPropertyValue, \
  FunctumPropertyValue
from mepinta.pipeline.lo.value_manager.PropertyValueManager import PropertyValueManager
from pipeline_backend.logging.logging import log_debug
from mepinta.pipeline.lo.pipeline_data.data_model import Property
from mepinta.pipeline.lo.constants import FUNCTION_PROPERTY_FLAG, INPUT_PROPERTY_FLAG, \
  NULL_UID, FUNCTUM_PROPERTY_FLAG
from pipeline_backend.void_pointer_casting.void_pointer_casting import any_ptr_to_voidp

#TODO: Document! and more debug printing?
class PropertyManager(object):
  def __init__(self, context_lo):
    self.context_lo = context_lo
    self.p_value_mngr = PropertyValueManager(context_lo)
  def create_properties(self, pline, prop_names, dtype_ids, prop_flags):
    prop_ids = []
    #TODO: remember to add property to topo = pline.get_topology() somewhere else
    log_debug('Creating properties %s' % (prop_names))
    for index, prop_name in enumerate(prop_names):
      prop = Property(prop_flags, prop_name, dtype_ids[index])
      prop_ids.append(pline.add_property(prop))
    return prop_ids
  def create_func_properties(self, pline, prop_names, func_ptr_ids):
    log_debug('Creating functions %s' % (prop_names))
    prop_ids = []
    for index, prop_name in enumerate(prop_names):
      prop = Property(FUNCTION_PROPERTY_FLAG, prop_name, dtype_id=NULL_UID)
      self.p_value_mngr.new_prop_value(prop, any_ptr_to_voidp(FunctionPropertyValue(func_ptr_ids[index])))
      prop_ids.append(pline.add_property(prop))
    return prop_ids
  def create_functum_properties(self, pline, prop_names, func_ptr_ids, dtype_ids, prop_flags):
    log_debug('Creating functums %s' % (prop_names))
    prop_ids = []
    for index, prop_name in enumerate(prop_names):
      prop = Property(FUNCTUM_PROPERTY_FLAG | prop_flags, prop_name, dtype_id=NULL_UID) #Contains the functum prop and  pointer to the function
      functum_prop = Property(FUNCTION_PROPERTY_FLAG, prop_name, dtype_id=dtype_ids[index])
      self.p_value_mngr.new_prop_value(prop, any_ptr_to_voidp(FunctumPropertyValue(func_ptr_ids[index], functum_prop)))
      prop_ids.append(pline.add_property(prop))
    return prop_ids
  def deleteProperties(self, pline, prop_ids):
    '''
    Deletes properties permanently from a pipeline. (also delete their values to
    avoid memory leaks)
    :param pline:
    :param prop_ids:
    '''
    props = []
    for p_id in prop_ids:
      props.append(pline.delete_property(p_id))
    self.p_value_mngr.deletePropertiesValues(props)
  def add_filters(self, pline, prop_ids):
    log_debug('Adding propagation filter properties %r' % prop_ids)
    for p_id in prop_ids:
      pline.marked_outputs.add(p_id)
  def remove_filters(self, pline, prop_ids):
    log_debug('Removing propagation filter properties %r' % prop_ids)
    for p_id in prop_ids:
      if p_id in pline.marked_outputs:
        pline.marked_outputs.remove(p_id)
  #Caching functions
  def add_non_cached(self, pline, dent_ids, dency_ids):
    log_debug('Setting non cached connections %r <-> %r' % (dent_ids, dency_ids))
    for index, dent_id in enumerate(dent_ids):
      if not pline.cached_link.has(dent_id, dency_ids[index]):
        pline.cached_link.add(dent_id, dency_ids[index])
  def remove_non_cached(self, pline, dent_ids):
    for dent_id in dent_ids:
      pline.cached_link.__delitem__(dent_id)

def shedskin_PropertyManager(context_lo, pline, prop_id):
  pm = PropertyManager(context_lo)
  prop_ids = [prop_id]
  pm.add_filters(pline, prop_ids)
  pm.remove_filters(pline, prop_ids)
  pm.add_non_cached(pline, dent_ids=prop_ids, dency_ids=prop_ids)
  pm.remove_non_cached(pline, dent_ids=prop_ids)
  prop_names = ['name']
  pm.create_func_properties(pline, prop_names, func_ptr_ids=[0])
  pm.create_functum_properties(pline, prop_names, func_ptr_ids=[0], dtype_ids=[0], prop_flags=0)
  pm.create_properties(pline, prop_names, dtype_ids=[0], prop_flags=INPUT_PROPERTY_FLAG)
  pm.deleteProperties(pline, prop_ids)

