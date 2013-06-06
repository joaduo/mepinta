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
from common.abstract.decorators.context_singleton import context_singleton
from common.abstract.FrameworkBase import FrameworkBase
from mepinta.pipeline.lo_cpp.load_library_stand_alone import load_library_stand_alone
import os
from mepinta.abstract.MepintaError import MepintaError

def unwrap_lo(wrapper): #TODO: take this out of here?
  if hasattr(wrapper, '__wrapped_lo__'):
    return wrapper.__wrapped_lo__()
  elif isinstance(wrapper, list):
    return [unwrap_lo(item) for item in wrapper]
  else:
    return wrapper

@context_singleton
class FactoryLo(FrameworkBase):
  def __post_init__(self):
    self.wrapped = self.get_wrapped()()
  def __load_libmepintacore(self):
      sep = os.sep
      path = sep.join(__file__.split(sep)[:-3]) + "%slib%slibMepintaArgsApi.so" % (sep, sep)
      self.log.debug("Loading lib at %r." % path)
      if not load_library_stand_alone(path, "global"):
        raise MepintaError("Couldn't load mepinta_cpp core at %s." % path)
  def get_wrapped(self):
    if self.context.backend_name == 'python':
      from mepinta.pipeline.lo.pipeline_lo_facade import FactoryLo as WrappedClass
    elif self.context.backend_name == 'c_and_cpp':
      self.__load_libmepintacore()
      from mepinta.pipeline.lo_cpp.pipeline_lo_facade import FactoryLo as WrappedClass
    else:
      raise MepintaError("There is not such backend: %r" % self.context.backend_name)
    return WrappedClass
  def get(self, class_name):
    if hasattr(self.wrapped, 'get_' + class_name):
      factory_method = getattr(self.wrapped, 'get_' + class_name)
    else:
      raise RuntimeError("There is no factory for the: %r" % class_name)
    return factory_method
  def getInstance(self, class_name, context):
    return self.get(class_name)(context_lo=unwrap_lo(context.context_lo))

if __name__ == '__main__':
  from common.context.Context import Context
  ctxp = Context('python')
  ctxc = Context('c_and_cpp')
  flo = FactoryLo(context=ctxp)
  pline = flo.get('Pipeline')
  print(pline())
  print(flo.context)
  print(ctxp)
  flo = FactoryLo(context=ctxc)
