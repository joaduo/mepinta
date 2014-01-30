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
from common.context.base import ContextBase
from mepinta.pipeline.hi.context_lo.ContextLo import ContextLo
from mepinta.pipeline.hi.LogOutput import LogOutput
from mepinta.abstract.MepintaError import MepintaError
from inspect import currentframe
import os
import re


class singleton_autocontext(arg_singleton_and_wrap):
  '''
  We would like to select context based on the package that is calling the
    context.
  '''
  def __call__(self, name=None, *args):
    if not name:
      path = self._getCallerFilePath()
      name = self.solveContextName(path)
    return super(singleton_autocontext, self).__call__(name, *args)

  def _getCallerFilePath(self):
    frame = self._getFrame(back=3)
    return frame.f_code.co_filename

  def _getFrame(self, back):
    frame = currentframe()
    for _ in range(back):
        frame = frame.f_back
    return frame

  def solveContextName(self, path):
    #TODO: solve based on the main script also (if this method fails)
    regex = r'plugins.(?P<backend>(?:python)|(?:c_and_cpp)).(?:[a-z_0-9]+).python_modules'
    regex = regex.replace('.', os.path.sep)
    m = re.search(regex, path)
    if m:
      name = m.group('backend')
      return name
    else:
      raise MepintaError('Could not resolve backend automatically by path %r '
                         '(specify backend name explicitly)' % path)

@singleton_autocontext
class MepintaContext(ContextBase):
  '''
  Specializes the "encapsulated context pattern" for a Mepinta environment.
  This means:
    -having a 'backend_name' property
    -initializing lower level 'ContextLo' based on backend
    -setting logging output to the based on backend and specific for mepinta
  '''
  def __init__(self, name):
    ContextBase.__init__(self, name)
    self._initConfig()

  def _initConfig(self):
    context = self
    deployment_path = self.getConfig('deployment_config').deployment_path
    context_lo = ContextLo(context=context, deployment_path=deployment_path)
    context.setConfig('context_lo', context_lo)
    logger = context.getConfig('log')
    logger.setOutput(LogOutput(context=context))

  def _getDefaultConfig(self, name):
    from mepinta_config import mepinta_config
    config = mepinta_config()
    if not hasattr(config, 'backend_name'):
      if 'python' in name:
        config.backend_name = 'python'
      elif 'cpp' in name:
        config.backend_name = 'c_and_cpp'
      else:
        raise LookupError('Cannot find backend name for context name')
    return config

def smokeTestModule():
  #context = MepintaContext('python')
  context = MepintaContext('c_and_cpp')
  from common.log.debugPrint import debugPrint
  pprint = debugPrint
  pprint(context.getConfig('backend_name'))
  pprint(context.getConfig('plugin_build_targets'))
  pprint(context.getConfigDict())

if __name__ == "__main__":
  smokeTestModule()
