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

NULL_UID = 0x0  # NULL_UNIVERSAL ID

# TODO: synch automatically with sdkdef.h
INPUT_PROPS = 1
OUTPUT_PROPS = 2
INPUT_OUTPUT_PROPS = 3
CUSTOM_INPUT_PROPS = 101
CUSTOM_OUTPUT_PROPS = 102
CUSTOM_INPUT_OUTPUT_PROPS = 103

C_EXIT_SUCCESS = 0
C_EXIT_FAILURE = 1

PROCESSOR_EXIT_NORMAL = 0
PROCESSOR_EXIT_FAILURE = 1
PROCESSOR_FUNC_NULL = 100

# TODO: Rename to FLAG
# TODO: INPUT OUTPUT INTERNAL should be DATA_PROPERTY_TYPE
INPUT_PROPERTY_FLAG = 0b1
INTERNAL_PROPERTY_FLAG = 0b10
OUTPUT_PROPERTY_FLAG = 0b100
FUNCTION_PROPERTY_FLAG = 0b1000
FUNCTUM_PROPERTY_FLAG = 0b10000
CUSTOM_PROPERTY_FLAG = 0b100000000


def hasFlags(prop_type, flags):
    return prop_type & flags != 0

MEPINTA_C_NAMESPACE_PREFIX = "MP_"
