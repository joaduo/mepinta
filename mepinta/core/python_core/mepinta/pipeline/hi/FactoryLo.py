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
from mepinta.abstract.MepintaError import MepintaError
from common.path import joinPath
from mepinta.pipeline.hi.load_unload_library import loadLibrary

def unwrapLo(wrapper): #TODO: take this out of here?
  if hasattr(wrapper, '__wrapped_lo__'):
    return wrapper.__wrapped_lo__()
  elif isinstance(wrapper, list):
    return [unwrapLo(item) for item in wrapper]
  else:
    return wrapper

@context_singleton
class FactoryLo(FrameworkBase):
  def __post_init__(self, deployment_path):
    self.__deployment_path = deployment_path
    self.wrapped = self.getWrapped()()

  def __loadLibsBackend(self):
    #Ok, we can load the libbackend_c_api.so (that will load all the other .so)
    for api in ('c', 'cpp'):
      lib_name = 'libbackend_api_%s.so' % api
      lib_path = joinPath(self.__deployment_path, 'build', 'libs', 'c_and_cpp',
                          lib_name)
      self.log.debug("Loading lib at %r." % lib_path)
      #Check if we could load it
      if not loadLibrary(lib_path, "global", primitive_lib=True):
        raise MepintaError("Couldn't load mepinta backend core at %r." % lib_path)

  def getWrapped(self):
    if self.context.backend_name == 'python':
      from mepinta.pipeline.lo.pipeline_lo_facade import FactoryLo as WrappedClass
    elif self.context.backend_name == 'c_and_cpp':
      self.__loadLibsBackend()
      try:
        from mepinta.pipeline.lo_cpp.pipeline_lo_facade import FactoryLo as WrappedClass
      except ImportError as e:
        msg = ('There may not exist mepinta.pipeline.lo_cpp.pipeline_lo_facade'
               ' (shedskin cpp compiled) module. (check how to build it if not'
               ' there)\n ImportError:%s' % e)
        self.log.e(msg)
        raise MepintaError(msg)
    else:
      raise MepintaError("There is not such backend: %r" %
                         self.context.backend_name)
    return WrappedClass

  def getClass(self, class_name):
    if hasattr(self.wrapped, 'get_' + class_name):
      factory_method = getattr(self.wrapped, 'get_' + class_name)
    else:
      raise RuntimeError("There is no factory for the: %r" % class_name)
    return factory_method

  def getInstance(self, class_name, context):
    return self.getClass(class_name)(context_lo=unwrapLo(context.context_lo))

if __name__ == '__main__':
  from getDefaultContext import getDefaultContext
  from common.log.debugPrint import debugPrint
  context = getDefaultContext(name='python')
  flo = FactoryLo(context, deployment_path=None)
  pline = flo.getClass('Pipeline')
  debugPrint(pline())
  debugPrint(flo.context)
  debugPrint(context)

