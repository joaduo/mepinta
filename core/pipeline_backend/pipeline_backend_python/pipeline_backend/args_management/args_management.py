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

from mepinta.pipeline.lo.constants import INPUT_PROPS, C_EXIT_SUCCESS, \
    CUSTOM_INPUT_PROPS, OUTPUT_PROPS

# Dummy object representing a voidp of a C struct (in cpp version)


class MepintaFunctum(object):

    def __init__(self, function, args):
        self.function_ptr = function
        self.args = args


def getFunctumStructVoidp(func_ptr, args):
    return MepintaFunctum(func_ptr, args)

# Dummy object representing a C struct (in cpp version)


class MepintaProps(object):

    def __init__(self):
        self.prop_ids = []
        self.names = []
        self.values = []
        self.handles = []
        self.changed = set()

# Dummy object representing a C struct (in cpp version)


class MepintaArgs(object):

    def __init__(self):
        self.thread_id = 0
        self.inputs = MepintaProps()
        self.variable_inputs = MepintaProps()
        self.outputs = MepintaProps()
        self.variable_outputs = MepintaProps()

# Get properties based on the Constant


def getProps(args, in_out_id):
    if in_out_id == INPUT_PROPS:
        return args.inputs
    elif in_out_id == CUSTOM_INPUT_PROPS:
        return args.variable_inputs
    elif in_out_id == OUTPUT_PROPS:
        return args.outputs
    else:
        return args.variable_outputs

# Mimic delete args in C (no need in Python)


def deleteArgs(args):
    return C_EXIT_SUCCESS

# Mimic create args in C


def createArgs(in_size, out_size):
    args = MepintaArgs()
    return args

# TODO: review if this is necessary? since there are args per function
# This was supposed to be args per thread, so we reuse the args structure
# But looks like we are going to discard this idea
args_per_thread = {}


def getThreadArgs(in_size, out_size, thread_id):
    global args_per_thread
    if thread_id not in args_per_thread:
        args_per_thread[thread_id] = createArgs(in_size, out_size)
    args = args_per_thread[thread_id]
    argsSetThreadId(args, thread_id)
    return args

# TODO: review discarding this


def argsSetThreadId(args, thread_id):
    args.thread_id = thread_id
    return C_EXIT_SUCCESS

# Mimic args set capacity in C


def argsSetCapacity(args, in_out_id, props_size):
    return C_EXIT_SUCCESS

# Mimic function in C


def argsAppendProp(args, in_out_id, index, prop_id, prop, prop_real, data_type):
    props = getProps(args, in_out_id)
    if len(props.prop_ids) == index:
        props.prop_ids.append(prop_id)
        props.names.append(prop.name)
        props.values.append(prop_real.getValuePtr())
        props.handles.append(data_type.lib_handle)
    else:
        props.prop_ids[index] = prop_id
        props.names[index] = prop.name
        props.values[index] = prop_real.getValuePtr()
        props.handles[index] = data_type.lib_handle
    return C_EXIT_SUCCESS

# Mimic function in C


def argsSetChanged(args, in_out_id, index):
    props = getProps(args, in_out_id)
    props.changed.add(props.prop_ids[index])
    return C_EXIT_SUCCESS

# Mimic function in C


def argsSetUnchanged(args, in_out_id, index):
    props = getProps(args, in_out_id)
    prop_id = props.prop_ids[index]
    if prop_id in props.changed:
        props.changed.remove(prop_id)
    return C_EXIT_SUCCESS

# Mimic function in C


def argsBuildChangedSet(args, in_out_id, changed):
    return changed.union(args.outputs.changed)

# TODO: Remove this?


def shedskin_args_management():
    args = createArgs(in_size=1, out_size=1)
    deleteArgs(args)
    argsSetCapacity(args, in_out_id=INPUT_PROPS, props_size=1)

    class Misc(object):

        def getValuePtr(self):
            return None
    data_type = Misc()
    data_type.lib_handle = None
    prop = Misc()
    prop.name = 'bla'
    argsAppendProp(args, in_out_id=INPUT_PROPS, index=0,
                   prop_id=0, prop=prop, prop_real=prop, data_type=data_type)
    argsSetChanged(args, in_out_id=INPUT_PROPS, index=0)
    argsSetUnchanged(args, in_out_id=INPUT_PROPS, index=0)
    argsBuildChangedSet(args, in_out_id=INPUT_PROPS, changed=set())
