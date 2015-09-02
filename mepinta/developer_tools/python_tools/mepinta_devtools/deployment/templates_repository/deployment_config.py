# -*- coding: utf-8 -*-
import os


class deployment_config(object):
    mepinta_source_path = '${mepinta_source_path}'
    libk3dsdk_path = '${libk3dsdk_path}'
    libgsigc2_path = '${libgsigc2_path}'
    libboost_unit_test_framework_path = '${libboost_unit_test_framework_path}'
    deployment_path = os.path.dirname(__file__)


def configurePythonPaths(create_context=True):
    import sys
    config = deployment_config()
    path = os.path.join(config.mepinta_source_path, 'developer_tools')
    sys.path.append(path)
    sys.path.append(config.mepinta_source_path)
    from mepinta_devtools.deployment.PythonPathManager import PythonPathManager
    PythonPathManager().appendInitial(config.mepinta_source_path)
    if create_context:
        from mepinta.context.MepintaContext import MepintaContext
        context = MepintaContext('python')
        context.deployment_config = config
        return context
