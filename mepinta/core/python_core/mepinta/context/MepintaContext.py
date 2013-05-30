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
from common.context.Context import ContextBase, args_singleton
from mepinta.pipeline.hi.context_lo.ContextLo import ContextLo
from mepinta.pipeline.hi.LogOutput import LogOutput

class chicken_egg_solver(object):
  '''
    Context needs to have prior any instancing:
      context_lo: For having a context to create classes on the lo layer.
      the logger output: For proper output of the logging.
    This decorator ensures that when instanced, the Context already has this two
    attributes.
    Also, ContextLo and LogOutput (in the hi package) need a MepintaContext to
      be instanced.
   (ContextLo and LogOutput need the MepintaContext, but don't use log or
     context_lo attributes)
  '''
  def __init__(self, Class):
    self.Class = Class
  def __call__(self, *a, **ad):
    instance = self.Class(*a, **ad)
    return self.__solve(instance)
  def __solve(self, context):
    context_lo = ContextLo(context=context)
    context.set_config('context_lo', context_lo)
    logger = context.get_config('log')
    logger.set_output(LogOutput(context=context))
    return context

@args_singleton
@chicken_egg_solver
class MepintaContext(ContextBase):
  pass

if __name__ == '__main__':
  pass
  ctx = MepintaContext('python')
  print(ctx)
  log = ctx.get_config('log')
  log.set_level(60)
  log.info('Hello')
  log.trace('Hello')
