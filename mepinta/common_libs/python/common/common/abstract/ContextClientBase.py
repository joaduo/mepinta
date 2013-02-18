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

from common.config.ContextWrapper import ContextWrapper
from common.context.Context import ContextBase

#TODO: rename it to GlobalConfigUserBase
class ContextClientBase(object):
  '''
    Classes inheriting from 'ContextClientBase' will have easier access to the
    global config embedded in the context object. 
    They will do to save some config:
      self.context.some_parameter = <value>
    And to retrieve it:
      <variable> = self.context.some_parameter
    Where 'self' would be an instance of the owner class (OwnerClass).
    Without this wrapper the class should have to do:
      <variable> = self.context.get_config(self.__class__,'some_parameter')
    or
      <variable> = context.get_config(self.__class__,'some_parameter')
    This way, accessing to the config is straightforward. 
  '''
  def __init__(self,context=None):
    self.context = self.__setContext(context)
  def __healthContext(self, context):
    return isinstance(context, ContextWrapper) or isinstance(context, ContextBase)
  def __setContext(self, context):
    if context == None:
      raise RuntimeError("You should provide a Context for this object since it " \
                         "inherits from %r"%self.__class__)
    elif not self.__healthContext(context):
      raise RuntimeError('Provided context %r is of incorrect type'%context)
    else:
      #The context need to be wrapped in order to have easier access to the global config
      if not isinstance(context, ContextWrapper):
        context = ContextWrapper(context)
    return context

