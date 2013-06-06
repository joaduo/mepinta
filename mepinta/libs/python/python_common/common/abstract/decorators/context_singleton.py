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

class context_singleton(object):
  '''
    Singleton pattern decorator.
    It provides a singleton for a determined Class in a determined Context.
    So for each Context there will be only once instance of the decorated class.
  '''
  def __init__(self, Class):
    self.Class = Class  
  def __call__(self, context=None, *a, **ad):
    if context == None:
      msg = "You should always provide a context for class: %r"%self.Class.__class__.__name__
      raise RuntimeError(msg)
    if not context.hasConfig('singleton',self.Class):
      context.setConfig('singleton',self.Class(context=context,*a,**ad),self.Class)
    return context.getConfig('singleton',self.Class)
