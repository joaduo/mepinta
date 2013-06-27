# -*- coding: utf-8 -*-
class deployment_config(object):
  mepinta_source_path = '${mepinta_source_path}'
  eclipse_projects_path = '${eclipse_projects_path}'
  qt_projects_path = '${qt_projects_path}'
  libk3dsdk_path = '${libk3dsdk_path}'
  libgsigc2_path = '${libgsigc2_path}'
  libboost_unit_test_framework_path = '${libboost_unit_test_framework_path}'

def configurePythonPaths(create_context=True):
  import sys
  config = deployment_config()
  sys.path.append(config.mepinta_source_path + '/developer_tools/python_tools')
  from mepinta_devtools.deployment.PythonPathManager import PythonPathManager
  PythonPathManager().appendAll(config.mepinta_source_path)
  from getDefaultContext import getDefaultContext
  if create_context:
    return getDefaultContext()
