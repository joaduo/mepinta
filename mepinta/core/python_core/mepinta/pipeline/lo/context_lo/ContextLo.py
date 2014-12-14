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
from mepinta.pipeline.lo.pipeline_data.data_model import DataType, ProcessorFunction


class ContextLo(object):

    def __init__(self):
        self.data_types = {}  # id:(data_type object)
        # path:(void*)handle #TODO: this should go to the PluginLoader? uhm... no
        self.data_types_paths = {}
        self.functions = {}  # id:(void*)func_pointer
        self.processors_paths = {}  # path:(void*)handle
        # We create this dummy data type for all those props without it
        self.data_types[0] = DataType('Zero_Data_Type', None)
        self.functions[0] = ProcessorFunction('Zero_Function', None)
        self.data_type_aliases = {}  # str:str

    def appendDataTypeAlias(self, data_type_name, data_type_alias):
        # TODO: review usage, should be on plugins data type validation?
        if data_type_name not in self.data_type_aliases:
            self.data_type_aliases[data_type_name] = []
        self.data_type_aliases[data_type_name].append(data_type_alias)


def shedskin_ContextLo():
    context_lo = ContextLo()
    context_lo.appendDataTypeAlias('int', 'int32_t')
    return context_lo
