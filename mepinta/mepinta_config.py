# -*- coding: utf-8 -*-
'''
Mepinta
'''
from default_deployment_config import default_deployment_config

class mepinta_config(object):
  minor_version_separator = '__'
  plugin_build_targets = ['Debug', 'Release', 'ReleasePointerSafe', 'ReleaseTypeSafe', 'ReleaseArgumentsSafe', ]
  nodebox_gui = False
  def __init__(self):
    self.deployment_config = default_deployment_config
  _config_dict = {
                  ('non_cached', 'class::mepinta.pipelineview.graph.GraphTopologyManager.GraphTopologyManager'):
                  False,
                  }

def smokeTestModule():
  from common.log.debugPrint import debugPrint
  settings = mepinta_config('python')
  for name in dir(settings):
    if not name.startswith('_'):
      debugPrint('%s: %r' % (name, getattr(settings, name)))

if __name__ == "__main__":
  smokeTestModule()
