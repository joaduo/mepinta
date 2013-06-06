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
from common.config.ConfigFactory import ConfigLoader
from common.log.Logger import Logger
import inspect

class ContextBase(object):
  def __init__(self, name):
    self.name = name
    #TODO: Create a persisted __config with self.__config.value = PersistConfig(10)
    #or self.__config.value = PersistPolicy(value=10, future_changes=true)
    #or PersistPolicy(self, 'value')
    self.__config = ConfigLoader().load(name)
    self.setConfig('log', Logger())

#  @property #TODO: remove
#  def log(self):
#    return self.getConfig('log')

  def hasConfig(self, name, owner="global"):
    return self.__getConfigKey(name, owner) in self.__config

  def getConfig(self, name, owner="global"):
    if self.hasConfig(name, owner):
      return self.__config[self.__getConfigKey(name, owner)]
    else:
      raise RuntimeWarning("No config '%s'." % self.__configKeyStr(name, owner))

  def setConfig(self, name, value, owner="global"):
    self.__config[self.__getConfigKey(name, owner)] = value

  def __getConfigKey(self, name, owner="global"):
    return (owner, name)

  def __configKeyStr(self, name, owner="global"): #TODO: use
    #TODO: Use this for persistence purposes
    if inspect.isclass(owner):
      string = "%s.%s" % (owner.__module__.__str__(),
                    owner.__name__)
    elif isinstance(owner, str):
      string = "%s" % owner
    else:#TODO: print warning!!
      string = "%s" % owner
    string += '.%s' % name
    return string

  def __repr__(self):
    return 'Context:%r with Config: %r' % (self.name, str(self.__config))

def test_module():
  #TODO: clean?
  from common.decorator.args_singleton import args_singleton
  @args_singleton
  class Context(ContextBase):
    pass
  from common.config.ContextWrapper import ContextWrapper
  ctxp = Context('python')
  ctxp2 = Context('python')
  ctxp3 = Context('python')
  ctxc = Context('c_and_cpp')
  print (ctxp)
  print (ctxp2)
  print (ctxp3)
  class Pototo:
    pass
  a = Pototo()
  from common.config.SelfConfigWrapper import SelfConfigWrapper
  cwrapper = SelfConfigWrapper(OwnerClass=a.__class__, context=ctxp)
  cwrapper.hola = 1
  print(cwrapper.hola)
  try:
    print(cwrapper.hola1)
  except Exception as e:
    print(e)
  print (ctxp)
  cwrapper = ContextWrapper(context=ctxp)
  cwrapper.hola = 1
  print (ctxp)
  print (cwrapper.backend_name)

if __name__ == "__main__":
  test_module()
