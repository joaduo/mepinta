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

#TODO: rename to ContextWrapper
class ContextWrapper(object):
  '''
    Provides a wrapper for a context object.
    This wrapper is used by other classes for managing the global config.
ContextClientBase
    They will do to save some config:
      self.context.config.some_parameter = <value>
      self.context.some_parameter = <value>
    And to retrieve it:
      <variable> = self.context.config.some_parameter
    Where 'self' would be an instance of this class.
    Without this wrapper the class should have to do:
      <variable> = self.context.get_config('global','some_parameter')
    This way, accessing to the global config is straightforward.
  '''
  def __init__(self, context):
    object.__setattr__(self, 'context', context)
    object.__setattr__(self, 'name', context.name)
  def __getattr__(self, name):
    if name in ['context', 'name']:
      object.__getattribute__(self, name)
    elif name in ['has_config', 'get_config', 'set_config']:
      return getattr(self.context, name)
    elif self.context.has_config(name):
      return self.context.get_config(name)
    else:
      raise RuntimeError('There is no global config for %r ' % (name))
  def __setattr__(self, name, value):
    self.context.set_config(name, value)
