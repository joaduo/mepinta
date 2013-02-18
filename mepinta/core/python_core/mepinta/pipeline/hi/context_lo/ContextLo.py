# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

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
'''
Created on Mar 10, 2012

@author: jduo
'''

from common.abstract.FrameworkBase import FrameworkBase
from mepinta.pipeline.hi.FactoryLo import FactoryLo

class ContextLo(FrameworkBase): 
  def __post_init__(self):
    self.wrapped = FactoryLo(context=self.context).get('ContextLo')()
  def get_lo(self):
    return self.wrapped
  def hasattr_(self,instance,name):
    try:
      object.__getattribute__(instance,name)
      return True
    except:
      return False
  def __getattr__(self,name):
    #TODO: add filters here
    if self.hasattr_(self.wrapped, name) and not self.hasattr_(self, name):
      return object.__getattribute__(self.wrapped,name)
    else:
      return object.__getattribute__(self,name)
  def __wrapped_lo__(self):
    return self.get_lo()

if __name__ == '__main__':
  from common.context.Context import Context
  ctxp = Context('python')
  ctxlo = ContextLo(context=ctxp)
  print(ctxlo)
#  flo = FactoryLo(context=ctxp)
#  pline = flo.get('Pipeline')
#  print(pline())
#  print(flo.context)
#  print(flo.context.context_lo)
#  print(ctxp)
