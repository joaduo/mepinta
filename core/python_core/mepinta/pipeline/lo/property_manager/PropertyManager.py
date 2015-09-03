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
from pipeline_backend.logging.logging import logDebug
from mepinta.pipeline.lo.pipeline_data.data_model import Property
from mepinta.pipeline.lo.constants import FUNCTION_PROPERTY_FLAG, INPUT_PROPERTY_FLAG, \
    NULL_UID, FUNCTUM_PROPERTY_FLAG
from pipeline_backend.void_pointer_casting.void_pointer_casting import anyPtrToVoidp

# TODO: Document! and more debug printing?


class PropertyManager(object):

    def __init__(self, context_lo):
        self.context_lo = context_lo
        self.p_value_mngr = PropertyValueManager(context_lo)

    def createProperties(self, pline, prop_names, dtype_ids, prop_flags):
        # Gather all new properties' ids
        prop_ids = []
        logDebug('Creating properties %s' % (prop_names))
        # Create a property for each name, assign data type and
        # flags
        for index, prop_name in enumerate(prop_names):
            prop = Property(prop_flags, prop_name, dtype_ids[index])
            prop_ids.append(pline.addProperty(prop))
        return prop_ids

    def createFuncProperties(self, pline, prop_names, func_ptr_ids):
        logDebug('Creating functions %s' % (prop_names))
        prop_ids = []
        for index, prop_name in enumerate(prop_names):
            prop = Property(
                FUNCTION_PROPERTY_FLAG, prop_name, dtype_id=NULL_UID)
            self.p_value_mngr.replacePropValue(
                prop, anyPtrToVoidp(FunctionPropertyValue(func_ptr_ids[index])))
            prop_ids.append(pline.addProperty(prop))
        return prop_ids

    def createFunctumProperties(self, pline, prop_names, func_ptr_ids, dtype_ids, prop_flags):
        logDebug('Creating functums %s' % (prop_names))
        prop_ids = []
        for index, prop_name in enumerate(prop_names):
            # Contains the functum prop and  pointer to the function
            prop = Property(FUNCTUM_PROPERTY_FLAG | prop_flags, prop_name, dtype_id=NULL_UID)
            functum_prop = Property(
                FUNCTION_PROPERTY_FLAG, prop_name, dtype_id=dtype_ids[index])
            self.p_value_mngr.replacePropValue(
                prop, anyPtrToVoidp(FunctumPropertyValue(func_ptr_ids[index], functum_prop)))
            prop_ids.append(pline.addProperty(prop))
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
            props.append(pline.deleteProperty(p_id))
        self.p_value_mngr.deletePropsValues(props)

    def addFilters(self, pline, prop_ids):
        logDebug('Adding propagation filter properties %r' % prop_ids)
        for p_id in prop_ids:
            pline.marked_outputs.add(p_id)

    def removeFilters(self, pline, prop_ids):
        logDebug('Removing propagation filter properties %r' % prop_ids)
        for p_id in prop_ids:
            if p_id in pline.marked_outputs:
                pline.marked_outputs.remove(p_id)
    # Caching functions

    def addNonCached(self, pline, dent_ids, dency_ids):
        logDebug('Setting non cached connections %r <-> %r' %
                 (dent_ids, dency_ids))
        for index, dent_id in enumerate(dent_ids):
            if not pline.cached_link.has(dent_id, dency_ids[index]):
                pline.cached_link.add(dent_id, dency_ids[index])

    def removeNonCached(self, pline, dent_ids):
        for dent_id in dent_ids:
            pline.cached_link.__delitem__(dent_id)


def shedskin_PropertyManager(context_lo, pline, prop_id):
    pm = PropertyManager(context_lo)
    prop_ids = [prop_id]
    pm.addFilters(pline, prop_ids)
    pm.removeFilters(pline, prop_ids)
    pm.addNonCached(pline, dent_ids=prop_ids, dency_ids=prop_ids)
    pm.removeNonCached(pline, dent_ids=prop_ids)
    prop_names = ['name']
    pm.createFuncProperties(pline, prop_names, func_ptr_ids=[0])
    pm.createFunctumProperties(
        pline, prop_names, func_ptr_ids=[0], dtype_ids=[0], prop_flags=0)
    pm.createProperties(
        pline, prop_names, dtype_ids=[0], prop_flags=INPUT_PROPERTY_FLAG)
    pm.deleteProperties(pline, prop_ids)
