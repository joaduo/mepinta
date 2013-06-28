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
from pipeline_backend.logging.logging import log_debug

def get_prop_value(args, in_out, name):
  return getattr(args, in_out).values[getattr(args, in_out).names.index(name)].get_value()

def has_changed_by_name(args, name): #rename to isChangedByName?
  if name in args.inputs.names:
    index = args.inputs.names.index(name)
    prop_id = args.inputs.prop_ids[index]
    return prop_id in args.inputs.changed
  else:
    log_debug("Name not in args")

def add_changed_by_index(args, index):
  log_debug('index=%r' % index)
  if index < len(args.outputs.values):
    args.outputs.changed[index] = True

def add_changed_by_name(args, name):
  if name in args.outputs.names:
    index = args.outputs.names.index(name)
    prop_id = args.outputs.prop_ids[index]
    args.outputs.changed.add(prop_id)
  else:
    log_debug("Name not in args")

def replace_out_prop_value(args, name, value, del_func_ptr):
  args.outputs.values[args.outputs.names.index(name)].replace_value(value, del_func_ptr)


