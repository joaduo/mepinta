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

from pipeline_backend.void_pointer_casting.void_pointer_casting import  strCharpToVoidp, \
    doubleToVoidp, intToVoidp, voidpToDouble, voidpToInt, \
    voidpCharpToStr, strStringToVoidp, voidpStringToStr
from pipeline_backend.logging.logging import logDebug
from mepinta.pipeline.lo.value_manager.PropertyValueManager import PropertyValueManager


class ValueManager(object):

    def __init__(self, context_lo):
        self.context_lo = context_lo
        self.p_value_mngr = PropertyValueManager(context_lo)

    def markChangedProps(self, pline, prop_ids):
        '''
        Add the changed properties (but do not below to a ChangeSet,
          when animating for example)
        :param pline: a pipeline (lo)
        :param prop_ids: a list of properties ids
        '''
        # Will propagate change, then mark it as a primary change
        for p_id in prop_ids:
            pline.changed_primary.add(p_id)

    def markChangeSetChangedProps(self, pline, prop_ids):
        '''
        Add the changed properties of a "ChangeSet"
        :param pline: a pipeline (lo)
        :param prop_ids: a list of properties ids
        '''
        # Will propagate change, then mark it as a primary change in the
        # topology
        for p_id in prop_ids:
            pline.getTopology().changed_primary.add(p_id)

    def __setPropValue(self, pline, prop_id, value):
        '''Directly passing a void*, no need for casting and checking (checking must be done before)'''
        logDebug('Setting value to prop_id=%r' % prop_id)
        self.p_value_mngr.replacePropValue(pline.all_properties[prop_id], value)
        # Add property to changed_primary
        pline.changed_primary.add(prop_id)

    def setUntypedPropsValues(self, pline, prop_ids, prop_values):
        for index, p_id in enumerate(prop_ids):
            self.__setPropValue(pline, p_id, prop_values[index])

    def getUntypedPropsValues(self, pline, prop_ids):
        prop_values = []
        for p_id in prop_ids:
            prop = pline.all_properties[p_id]
            prop_values.append(prop.getValuePtr().getValue())
        return prop_values

    # Setters, validation of types is handled by shedskin, since list are typed
    def setStdStrings(self, pline, prop_ids, prop_values):
        for index, p_id in enumerate(prop_ids):
            self.__setPropValue(
                pline, p_id, strStringToVoidp(prop_values[index]))

    def setCharps(self, pline, prop_ids, prop_values):
        for index, p_id in enumerate(prop_ids):
            self.__setPropValue(
                pline, p_id, strCharpToVoidp(prop_values[index]))

    def setDoubles(self, pline, prop_ids, prop_values):  # TODO: check if shedskin does any difference
        for index, p_id in enumerate(prop_ids):
            self.__setPropValue(pline, p_id, doubleToVoidp(prop_values[index]))

    def setInts(self, pline, prop_ids, prop_values):
        for index, p_id in enumerate(prop_ids):
            self.__setPropValue(pline, p_id, intToVoidp(prop_values[index]))

    # Getters
    def getStdStrings(self, pline, prop_ids):
        prop_values = []
        for p_id in prop_ids:
            prop = pline.all_properties[p_id]
            if self.context_lo.data_types[prop.dtype_id].name == 'cpp_std_string':
                prop_values.append(
                    voidpStringToStr(prop.getValuePtr().getValue()))
        return prop_values

    def getCharps(self, pline, prop_ids):
        prop_values = []
        for p_id in prop_ids:
            prop = pline.all_properties[p_id]
            # TODO: fix wiht c_namespace string
            if self.context_lo.data_types[prop.dtype_id].name == 'charp':
                prop_values.append(
                    voidpCharpToStr(prop.getValuePtr().getValue()))
        return prop_values

    def getDoubles(self, pline, prop_ids):
        prop_values = []
        for p_id in prop_ids:
            prop = pline.all_properties[p_id]
            if self.context_lo.data_types[prop.dtype_id].name == 'double':
                prop_values.append(
                    voidpToDouble(prop.getValuePtr().getValue()))
        return prop_values

    def getInts(self, pline, prop_ids):
        prop_values = []
        for p_id in prop_ids:
            prop = pline.all_properties[p_id]
            if self.context_lo.data_types[prop.dtype_id].name == 'int':
                prop_values.append(voidpToInt(prop.getValuePtr().getValue()))
        return prop_values


def shedskin_ValueManager(context_lo, pline, prop_id):
    vm = ValueManager(context_lo)
    prop_ids = [prop_id]

    vm.markChangedProps(pline, prop_ids)
    vm.markChangeSetChangedProps(pline, prop_ids)
    vm.setStdStrings(pline, prop_ids, ['value'])
    vm.setCharps(pline, prop_ids, ['value'])
    vm.setInts(pline, prop_ids, [1])
    vm.setDoubles(pline, prop_ids, [1.1])
    vm.setUntypedPropsValues(pline, prop_ids, [None])

    vm.getStdStrings(pline, prop_ids)
    vm.getCharps(pline, prop_ids)
    vm.getDoubles(pline, prop_ids)
    vm.getInts(pline, prop_ids)
    vm.getUntypedPropsValues(pline, prop_ids)

if __name__ == '__main__':
    pass
