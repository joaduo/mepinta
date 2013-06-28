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
from common.context.Context import arg_singleton_and_wrap
from mepinta.pipeline.hi.context_lo.ContextLo import ContextLo
from mepinta.pipeline.hi.LogOutput import LogOutput
from common.context.base import ContextBase

@arg_singleton_and_wrap
class MepintaContext(ContextBase):
  def __init__(self, backend_name):
    ContextBase.__init__(self, backend_name)
    self.__initConfig()
  def __initConfig(self):
    context = self
    context_lo = ContextLo(context=context)
    context.setConfig('context_lo', context_lo)
    logger = context.getConfig('log')
    logger.setOutput(LogOutput(context=context))

def testModule():
  pass

if __name__ == "__main__":
  testModule()
