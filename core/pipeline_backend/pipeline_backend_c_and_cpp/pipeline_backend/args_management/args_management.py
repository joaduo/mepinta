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


def getFunctumStructVoidp(func_ptr, args):
    return None

args_per_thread = {}


def getThreadArgs(in_size, out_size, thread_id):
    global args_per_thread
    if thread_id not in args_per_thread:
        args = createArgs(in_size, out_size)
        args_per_thread[thread_id] = args
    else:
        args = args_per_thread[thread_id]
        argsSetCapacity(args, 1, in_size)
        argsSetCapacity(args, 2, out_size)
    argsSetThreadId(args, thread_id)
    return args


def deleteArgs(args):
    return 0


def createArgs(in_size, out_size):
    return None


def argsSetThreadId(args, thread_id):
    return 0


def argsSetCapacity(args, in_out_id, props_size):
    return 0

def argsAppendProp(args, in_out_id, index,prop_id,prop,prop_real,data_type):
    return 0


def argsSetChanged(args, in_out_id, index):
    return 0


def argsSetUnchanged(args, in_out_id, index):
    return 0


def argsBuildChangedSet(args, in_out_id, changed):
    changed.add(10)
    return changed


def shedskin_args_management():
    #  args = None
    #  size = 0
    #  thread_id = 0
    #  in_out_id = 1
    #  index = 0
    #  deleteArgs(args)
    #  createArgs(size, size)
    #  argsSetCapacity(args, in_out_id, size)
    #  argsSetThreadId(args, thread_id)
    # argsAppendProp(None, 0, 0, 0, prop, data_type)
    #  argsSetChanged(args, in_out_id, index)
    #  argsSetUnchanged(args, in_out_id, index)
    #  argsBuildChangedSet(args)
    args = createArgs(in_size=1, out_size=1)
    deleteArgs(args)
    argsSetCapacity(args, in_out_id=1, props_size=1)
#  class Misc(object):
#    def getValuePtr(self): return None
#  data_type = Misc(); data_type.lib_handle = None
#  prop = Misc(); prop.name = 'bla'
#  argsAppendProp(args, in_out_id=INPUT_PROPS, index=0, prop_id=0, prop=prop, data_type=data_type)
    argsSetChanged(args, in_out_id=1, index=0)
    argsSetUnchanged(args, in_out_id=1, index=0)
    changed = set()
    changed.add(0)
    argsBuildChangedSet(args, in_out_id=1, changed=changed)

    getThreadArgs(in_size=1, out_size=1, thread_id=1)
