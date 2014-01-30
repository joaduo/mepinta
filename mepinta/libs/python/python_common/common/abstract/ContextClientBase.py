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


class ContextClientBase(object):
  '''
    Makes sure that every context object is wrapped by
    :class:`common.config.ContextWrapper.ContextWrapper`
  '''
  def __init__(self, context=None):
    '''
    Wrap context if not wrapped yet.
    :param context: context, instance of :class:`from common.context.Context.ContextBase`
    '''
    self.context = self.__setContext(context)

  def __setContext(self, context):
    '''
    Wrap context if not wrapped yet.
    :param context: context, instance of :class:`from common.context.Context.ContextBase`
    '''
    if context == None:
      raise RuntimeError("You should provide a Context for this object since it"
                         " is an instance of %r" % self.__class__)
    elif not (isinstance(context, ContextWrapper) \
    or isinstance(context, ContextBase)): #healthy
      raise RuntimeError('Provided context %r is of incorrect type' % context)
    else:
      #The context need to be wrapped in order to have easier access to the global config
      if not isinstance(context, ContextWrapper):
        context = ContextWrapper(context)
    return context


def smokeTestModule():
  from common.context.Context import Context
  from common.log.debugPrint import debugPrint
  class Client(ContextClientBase):
    def example(self):
      self.processors = {}
  ctx = Context('python')
  client = Client(context=ctx)
  debugPrint(client.context)
  client.context.hola = 'valor'
  debugPrint(client.context.hola)
  try:
    client.context.context = 'bla'
  except Exception as e:
    debugPrint(e)

if __name__ == '__main__':
  smokeTestModule()
