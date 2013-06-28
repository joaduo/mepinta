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
from pipeline_backend.logging.logging import logDebug

def getPropValue(args, in_out, name):
  return getattr(args, in_out).values[getattr(args, in_out).names.index(name)].getValue()

def hasChangedByName(args, name): #rename to isChangedByName?
  if name in args.inputs.names:
    index = args.inputs.names.index(name)
    prop_id = args.inputs.prop_ids[index]
    return prop_id in args.inputs.changed
  else:
    logDebug("Name not in args")

def addChangedByIndex(args, index):
  logDebug('index=%r' % index)
  if index < len(args.outputs.values):
    args.outputs.changed[index] = True

def addChangedByName(args, name):
  if name in args.outputs.names:
    index = args.outputs.names.index(name)
    prop_id = args.outputs.prop_ids[index]
    args.outputs.changed.add(prop_id)
  else:
    logDebug("Name not in args")

def replaceOutPropValue(args, name, value, del_func_ptr):
  args.outputs.values[args.outputs.names.index(name)].replaceValue(value, del_func_ptr)


