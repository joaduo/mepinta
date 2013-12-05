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
from pipeline_backend.logging.logging import LOG_INFO, LOG_DEBUG
from mepinta.context.getMepintaContext import getMepintaContext
from mepinta.context.MepintaContext import MepintaContext

#TODO: clean
#def setConfigs(context, deployment_path):
#  from mepinta.pipelineview.graph.GraphTopologyManager import GraphTopologyManager
#  non_cached = False
#  context.setConfig('non_cached', non_cached, GraphTopologyManager)
#  context.log.w('Using artificial deployment config!')
#  class deployment_config(object):
#    def __init__(self):
#      self.mepinta_source_path = '/home/jduo/001-Mepinta/git/mepinta/mepinta'
#      self.deployment_path = deployment_path
#  context.deployment_config = deployment_config()

called_once = False
def getDefaultContext(log_level=LOG_INFO, name='python'):
  '''Creates a default context to reduce code verbosity for starting.'''

  global called_once
  if called_once:
    raise RuntimeError('You should call the default context only once. (in the main script)')
  else:
    called_once = True
#  deployment_path = '/home/jduo/001-Mepinta/EclipseProjects_GitRepo/mepinta_test_folders/deployment7'
  #context = getMepintaContext(name)
  context = MepintaContext(name)
  context.log.setLevel(log_level)
#  setConfigs(context, deployment_path)
  return context

def smokeTestModule():
  from common.log.debugPrint import debugPrint
#  from mepinta.pipeline.hi.FactoryLo import FactoryLo
#  ctxc = getDefaultContext(name='c_and_cpp')
  ctxc = getDefaultContext(name='python')
  debugPrint(ctxc.getConfigDict())
  #ctxc.getConfig(name, owner)
  #debugPrint(ctxc.deployment_config.deployment_path)
#  flo = FactoryLo(context)

if __name__ == "__main__":
  smokeTestModule()
