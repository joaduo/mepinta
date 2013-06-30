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

def unwrapLo(wrapper): #TODO: take this out of here?
  if hasattr(wrapper, '__wrapped_lo__'):
    return wrapper.__wrapped_lo__()
  elif isinstance(wrapper, list):
    return [unwrapLo(item) for item in wrapper]
  else:
    return wrapper

@context_singleton
class FactoryLo(FrameworkBase):
  def __post_init__(self):
    self.wrapped = self.getWrapped()()

  def __loadLibBackendApiC(self):
    #Import the shedskin module to load the backend_c_api library
    #The rest of the libraries will be loaded by that library.
    try:
      from mepinta.pipeline.lo_cpp.load_library_stand_alone import loadLibraryStandAlone
    except ImportError as e:
      msg = 'There may not exist mepinta.pipeline.lo_cpp.load_library_stand_alone (shedskin cpp compiled) module. (check how to build it if not there)'
      msg += '\n ImportError:%s' % e
      self.log.e(msg)
      raise MepintaError(msg)

    #Ok, we can load the libbackend_c_api.so (that will load all the other .so)
    lib_backend_api_c_path = joinPath(self.context.deployment_config.deployment_path, 'build/libs/backend/libbackend_api_c.so')
    self.log.debug("Loading lib at %r." % lib_backend_api_c_path)
    #Check if we could load it
    if not loadLibraryStandAlone(lib_backend_api_c_path, "global"):
      raise MepintaError("Couldn't load mepinta_cpp core at %s." % lib_backend_api_c_path)

  def getWrapped(self):
    if self.context.backend_name == 'python':
      from mepinta.pipeline.lo.pipeline_lo_facade import FactoryLo as WrappedClass
    elif self.context.backend_name == 'c_and_cpp':
      self.__loadLibBackendApiC()
      try:
        from mepinta.pipeline.lo_cpp.pipeline_lo_facade import FactoryLo as WrappedClass
      except ImportError as e:
        msg = 'There may not exist mepinta.pipeline.lo_cpp.pipeline_lo_facade (shedskin cpp compiled) module. (check how to build it if not there)'
        msg += '\n ImportError:%s' % e
        self.log.e(msg)
        raise MepintaError(msg)
    else:
      raise MepintaError("There is not such backend: %r" % self.context.backend_name)
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
  from common.log.debugPrint import debugPrint
  from common.context.Context import Context
  ctxp = Context('python')
  ctxc = Context('c_and_cpp')
  flo = FactoryLo(context=ctxp)
  pline = flo.getClass('Pipeline')
  debugPrint(pline())
  debugPrint(flo.context)
  debugPrint(ctxp)
  flo = FactoryLo(context=ctxc)
