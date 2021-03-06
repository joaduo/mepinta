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
from mepinta.pipeline.lo.reentrant.reentrant import isDataTypeAlias as isDataTypeAlias_implementation


def isDataTypeAlias(processor_context, data_type_name, data_type_alias):
    return isDataTypeAlias_implementation(processor_context, data_type_name, data_type_alias)


def shedskin_backend_reentrant_isDataTypeAlias(processor_context):
    isDataTypeAlias(processor_context, "int", "int32_t")
