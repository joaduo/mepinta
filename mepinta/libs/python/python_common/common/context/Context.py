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

class args_singleton(object):
  '''
    Decorator that provides a single instance for the arguments provided
      I.e.: same arguments, same instance
      If the arguments differ, then a new instance is created
      In this case arguments are: name
  '''
  __instances = {}
  def __init__(self, Class):
    self.Class = Class
  def __call__(self, name):
    if name not in self.__instances:
      self.__instances[name] = self.Class(name)
    return self.__instances[name]
  def get_current_contexts(self):
    return self.__instances

#TODO: move it to base.py
class ContextBase(object):
  def __init__(self, name):
    self.name = name
    #TODO: Create a persisted __config with self.__config.value = PersistConfig(10)
    #or self.__config.value = PersistPolicy(value=10, future_changes=true)
    #or PersistPolicy(self, 'value')
    self.__config = ConfigLoader().load(name)
    self.set_config('log', Logger())

  @property
  def log(self):
    return self.get_config('log')
  def get_config_store(self):
    return self.__config
  def has_config(self, name, owner="global"):
    return self.__get_config_key(name, owner) in self.__config
  def get_config(self, name, owner="global"):
    if self.has_config(name, owner):
      return self.__config[self.__get_config_key(name, owner)]
    else:
      raise RuntimeWarning("No config '%s'." % self.__config_key_str(name, owner))
  def set_config(self, name, value, owner="global"):
    self.__config[self.__get_config_key(name, owner)] = value
  def __get_config_key(self, name, owner="global"):
    return (owner, name)
  def __config_key_str(self, name, owner="global"):
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


@args_singleton
class Context(ContextBase):
  pass

if __name__ == '__main__':
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
  from common.config.ConfigWrapper import ConfigWrapper
  cwrapper = ConfigWrapper(OwnerClass=a.__class__, context=ctxp)
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
