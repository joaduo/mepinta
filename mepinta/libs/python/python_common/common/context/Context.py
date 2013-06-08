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
from common.context.base import ContextBase
from common.config.ContextWrapper import ContextWrapper

class arg_singleton_and_wrap(object):
  '''
    Decorator that provides a single instance for the arguments provided
      I.e.: same arguments, same instance
      If the arguments differ, then a new instance is created
      In this case arguments are: name
  '''
  __instances = {}
  def __init__(self, class_):
    self.class_ = class_
  def __call__(self, name):
    if name not in self.__instances:
      self.__instances[name] = ContextWrapper(self.class_(name))
    return self.__instances[name]
  def getCurrentContexts(self):
    return self.__instances

@arg_singleton_and_wrap
class Context(ContextBase):
  pass

