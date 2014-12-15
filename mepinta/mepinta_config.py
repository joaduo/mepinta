# -*- coding: utf-8 -*-
'''
Mepinta
'''
from default_deployment_config import default_deployment_config


class mepinta_config(object):
    minor_version_separator = '__'
    plugin_build_targets = [
        'Debug', 'Release', 'ReleasePointerSafe', 'ReleaseTypeSafe', 'ReleaseArgumentsSafe', ]
    nodebox_gui = False
    deployment_config = default_deployment_config()
    non_cached_evaluation = False
    _config_dict = {
#         ('non_cached', 'class::mepinta.pipelineview.graph.GraphTopologyManager.GraphTopologyManager'):
#         False,
    }


def smokeTestModule():
    from common.log.debugPrint import debugPrint
    settings = mepinta_config()
    for name in dir(settings):
        if not name.startswith('_'):
            debugPrint('%s: %r' % (name, getattr(settings, name)))

if __name__ == "__main__":
    smokeTestModule()
