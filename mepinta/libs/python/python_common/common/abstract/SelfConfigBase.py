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

from common.abstract.ContextClientBase import ContextClientBase
from common.config.SelfConfigWrapper import SelfConfigWrapper

class SelfConfigBase(ContextClientBase):
  '''
    Makes easier to access class context configuration through self.config proxy

    They will do to save some config:
      self.config.some_parameter = <value>
    And to retrieve it:
      <variable> = self.config.some_parameter

    Without this wrapper the class should have to do:
      <variable> = self.context.get_config(self.__class__,'some_parameter')
    This way, accessing to the config is straightforward.
  '''
  def __init__(self, context):
    ContextClientBase.__init__(self, context)

    self.config = SelfConfigWrapper(OwnerClass=self.__class__, context=self.context)
    self.log = self.context.log

def smokeTestModule():
  from common.context.Context import Context
  from common.log.debugPrint import debugPrint
  class FooTestPluginsManager(SelfConfigBase):
    def __post_init__(self):
      self.processors = {}
  ctx = Context('python')
  pm = FooTestPluginsManager(context=ctx)
  debugPrint(pm.config)
  pm.config.hola = 'valor'
  debugPrint(pm.config.hola)
  try:
    pm.config.context = 'bla'
  except Exception as e:
    debugPrint(e)

if __name__ == '__main__':
  smokeTestModule()
