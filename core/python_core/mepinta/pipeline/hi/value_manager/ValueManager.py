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
from mepinta.pipeline.hi.base import unwrap_decorator, \
    unwrapLo
from mepinta.plugins_manifest.proxy.data_model import GenericEnumProxy
from mepinta.pipeline.hi.FactoryLo import FactoryLo
from common.abstract.FrameworkBase import FrameworkBase

# TODO: should be able to set ctypes structs. It will be implemented on C
# + Ctypes. But not in this module

class ValueManager(FrameworkBase):  # TODO: rename to TypedValueManager

    def __post_init__(self):
        self._value_manager_lo = FactoryLo(
            self.context).getInstance('ValueManager', self.context)
        self._get_dispatch_dict = self.__getDispatchDict('get')
        self._set_dispatch_dict = self.__getDispatchDict('set')

    def getValue(self, pline, prop):
        if prop.data_type_name in self._get_dispatch_dict:
            return self._get_dispatch_dict[prop.data_type_name](pline, prop)
        else:
            self.log.warning('Unsupported getter for type %s' %
                             prop.getDataTypeShortName())

    def setValue(self, pline, prop, value):
        if isinstance(prop, GenericEnumProxy):
            self.__setGenericEnum(pline, prop, value)
        elif prop.data_type_name in self._set_dispatch_dict:
            self._set_dispatch_dict[prop.data_type_name](pline, prop, value)
        else:
            self.log.warning('Unsupported setter for type %s' %
                             prop.getDataTypeShortName())

    @unwrap_decorator
    def markChanged(self, pline, prop):
        self._value_manager_lo.markChangedProps(pline, [prop])

    # TODO: distinguish mutiple from mono values
    def __getDispatchDict(self, prefix):
        dispatch_template = {'c.builtin.int': ('Int', int),
                             'c.builtin.double': ('Double', float),
                             'c.builtin.charp': ('Charp', str),
                             'cpp.std.string': ('StdString', str),
                             }
        dispatch_dict = {}
        for data_type_name, (data_type_nick, type_cast) in dispatch_template.items():
            method = getattr(self._value_manager_lo, '%s%ss' %
                             (prefix, data_type_nick))
            unwrap_and_cast = self._getUnwrapAndCast(prefix, method, type_cast)
            dispatch_dict[data_type_name] = unwrap_and_cast
        return dispatch_dict

    def _getUnwrapAndCast(self, prefix, method, type_cast):
        if prefix == 'set':
            def unwrapAndCast(pline, prop, value):
                method(unwrapLo(pline), [unwrapLo(prop)], [type_cast(value)])
        elif prefix == 'get':
            def unwrapAndCast(pline, prop):
                values = method(unwrapLo(pline), [unwrapLo(prop)])
                if len(values) > 0:
                    return values[0]
                else:
                    return None
        return unwrapAndCast

    def __setGenericEnum(self, pline, prop, value):
        if value in prop.enum_dict:
            value = prop.enum_dict[value]
        elif value not in prop.enum_dict.values():
            self.log.w('Setting default value for generic enum.')
            value = prop.default_value
        self.__setInt(pline, prop, value)

    @unwrap_decorator
    def __setInt(self, pline, prop, int_):
        self._value_manager_lo.setInts(pline, [prop], [int(int_)])
