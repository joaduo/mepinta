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

# Data

def intToVoidp(int_v):  # TODO: remove
    return int_v


def doubleToVoidp(float_v):
    return float_v


def strToVoidp(str_):
    return str_


def strCharpToVoidp(str_):
    return str_


def strStringToVoidp(str_):
    return str_


def anyPtrToVoidp(anything):
    return anything


def voidpToInt(voidp):
    return voidp


def voidpToDouble(voidp):
    return voidp


def voidpToStr(voidp):
    return voidp


def voidpCharpToStr(voidp):
    return voidp


def voidpStringToStr(voidp):
    return voidp


def voidpToListInt(voidp):
    return voidp


def voidp_to_FunctionPropertyValue(voidp):
    return voidp


def voidp_to_FunctumPropertyValue(voidp):
    return voidp

# Functions pointers


def voidpToFuncArgVoid(voidp):
    return voidp


def voidpToFuncArgVoidp(voidp):
    return voidp


def voidpToProcessorFunc(voidp):
    return voidp


def voidpToCopyToFunc(voidp):
    return voidp


def shedskin_void_pointer_casting():
    voidp = None
    voidpToFuncArgVoid(voidp)
    voidpToFuncArgVoidp(voidp)

    voidpToInt(voidp)
    voidpToStr(voidp)
    voidpToDouble(voidp)
    voidpToListInt(voidp)

    anyPtrToVoidp(voidp)
    intToVoidp(1)
    doubleToVoidp(10.0)
    strToVoidp('')

if __name__ == '__main__':
    shedskin_void_pointer_casting()
