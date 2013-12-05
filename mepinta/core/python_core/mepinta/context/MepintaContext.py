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
  def __init__(self, name):
    ContextBase.__init__(self, name)
    self.__initConfig()

  def __initConfig(self):
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

def testModule():
  #context = MepintaContext('python')
  context = MepintaContext('c_and_cpp')
  from common.log.debugPrint import debugPrint
  pprint = debugPrint
  pprint(context.getConfig('backend_name'))
  pprint(context.getConfig('plugin_build_targets'))
  pprint(context.getConfigDict())

if __name__ == "__main__":
  testModule()
