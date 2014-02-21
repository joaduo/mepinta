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
from common.abstract.SelfConfigBase import SelfConfigBase
from common.abstract.PostInitStrategyBase import PostInitStrategyBase


class FrameworkBase(PostInitStrategyBase, SelfConfigBase):
  '''
  Base class for all logic classes in the framework.
  Data classes should inherit from object or FrameworkObject
  '''
  def __init__(self, context, *a, **ad):
    SelfConfigBase.__init__(self, context=context)
    PostInitStrategyBase.__init__(self, *a, **ad)


def smokeTestModule():
  from common.log.debugPrint import debugPrint
  class ExtendedBase(FrameworkBase):
    def __post_init__(self, *a, **ad):
      debugPrint('Post init Extended Base')
      pass

  class Foo(object):
    pass

#  class ConcreteClass(Foo, ExtendedBase):
  class ConcreteClass(ExtendedBase, Foo):
    def __post_init__(self, value):
      debugPrint('Post init Concrete')
      self.post_init_var = value

  from common.context.Context import Context
  ctx = Context('python')
  cc = FrameworkBase(context=ctx)
  cc = ConcreteClass(context=ctx, value=1)

if __name__ == '__main__':
  smokeTestModule()
