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
from common.python3 import portableGetArgspec

class InitStrategyBase(object): #TODO: only use PostInitStrategyBase
#  def __init__(self):
#    pass  # TODO: select init strategy
  def _initChildren(self, args, kwargs):
    if len(args):
      raise TypeError('You should provide all arguments as keywords')
    pres = []
    posts = []
    self.__getInitLists(self.__class__, pres, posts, set())
    # TODO: use inspect here and make sure it py3 compatible
    # Call inits in args 'LIFO' order (First child classes then parents)
    self.__callInits(pres, kwargs)
    # TODO: Beware! Something strange happens here if we pass only the reverse iterator!!
    # Call inits in args 'FIFO' order (First parent classes then children)
    self.__callInits(list(reversed(posts)), kwargs)
  def __callInits(self, funcs, kwargs):
    for class_, func in funcs:
      args = portableGetArgspec(func).args
      func_kwargs = dict(filter(lambda x: x[0] in args, kwargs.items()))
      try:
        func(self, **func_kwargs)
      except TypeError as e:
        self.log.last_exception(level='error')
        self.log.error(e)
        raise TypeError('For class %s.%s' % (class_.__module__, class_.__name__))
  def __getInitLists(self, class_, pres, posts, already_added):
    # TODO: check here when arriving to InitStrategyBase, if it doesn't, it
    # means there is multiple inheritance and it's not allowed
    # debugPrint how to inherit correctly
    if class_ == InitStrategyBase:
      return
    if issubclass(class_, InitStrategyBase):
      if hasattr(class_, '__pre_init__') and class_.__pre_init__ not in already_added:
        pres.append((class_, class_.__pre_init__))
        already_added.add(class_.__pre_init__)
      if hasattr(class_, '__post_init__') and class_.__post_init__ not in already_added:
        posts.append((class_, class_.__post_init__))
        already_added.add(class_.__post_init__)
      self.__getInitLists(class_.__base__, pres, posts, already_added)
    else:
      raise RuntimeError('InitStrategyBase should be on the main inheritance line.')


if __name__ == '__main__':
  class ExtendedBase(InitStrategyBase):
    def __pre_init__(self, something):
      pass
    def __post_init__(self, value1, test1=1, tat1=20):
      self.post_init_var1 = value1

  class ConcreteClass(ExtendedBase):
    def __pre_init__(self, other_value):
      self.pre_init_var = other_value

    def __post_init__(self, value, test=1, tat=20):
      self.post_init_var = value

  from common.context.Context import Context
  ctx = Context('python')
  cc = ConcreteClass()
  cc._initChildren([], dict(context=ctx, something=2312, value1=231, other_value=20, value=100, test=2))
  debugPrint(cc.post_init_var, cc.pre_init_var, cc.post_init_var1)

