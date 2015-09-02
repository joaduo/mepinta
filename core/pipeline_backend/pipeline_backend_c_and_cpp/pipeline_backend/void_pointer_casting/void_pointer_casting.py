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

# Functions prototypes


def func_arg_void():
    return None


def func_arg_voidp(voidp):
    return None


def processor_func(args_voidp):
    return 0


def copyToFunc(to_voidp, from_voidp):
    return None

# Data

def intToVoidp(int_v):  # TODO: remove
    return None


def doubleToVoidp(float_v):
    return None


def strToVoidp(str_):
    return None


def strCharpToVoidp(str_):
    return None


def strStringToVoidp(str_):
    return None


def anyPtrToVoidp(anything):
    return None


def voidpToInt(voidp):
    return 1


def voidpToDouble(voidp):
    return 1.1


def voidpToStr(voidp):
    return ''


def voidpCharpToStr(voidp):
    return ''


def voidpStringToStr(voidp):
    return ''


def voidpToListInt(voidp):
    return [1]


def voidp_to_FunctionPropertyValue(voidp):
    return FunctionPropertyValue()


def voidp_to_FunctumPropertyValue(voidp):
    return FunctumPropertyValue()

# Functions pointers


def voidpToFuncArgVoid(voidp):
    func_arg_void()
    return func_arg_void


def voidpToFuncArgVoidp(voidp):
    func_arg_voidp(None)
    return func_arg_voidp


def voidpToProcessorFunc(voidp):
    processor_func(None)
    return processor_func


def voidpToCopyToFunc(voidp):
    copyToFunc(None, None)
    return copyToFunc


def shedskin_void_pointer_casting():
    voidp = None
    voidpToFuncArgVoid(voidp)
    voidpToFuncArgVoidp(voidp)
    voidpToProcessorFunc(voidp)
    voidpToCopyToFunc(voidp)

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
