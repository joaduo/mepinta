# -*- coding: utf-8 -*-
import os
class deployment_config(object):
  mepinta_source_path = '/home/jduo/001-Mepinta/git/mepinta/mepinta'
  eclipse_projects_path = '${eclipse_projects_path}'
  qt_projects_path = '${qt_projects_path}'
  libk3dsdk_path = '${libk3dsdk_path}'
  libgsigc2_path = '${libgsigc2_path}'
  libboost_unit_test_framework_path = '${libboost_unit_test_framework_path}'
  deployment_path = os.path.dirname(__file__)

def configurePythonPaths(create_context=True):
  import sys
  config = deployment_config()
  sys.path.append(config.mepinta_source_path + '/developer_tools/python_tools')
  from mepinta_devtools.deployment.PythonPathManager import PythonPathManager
  PythonPathManager().appendAll(config.mepinta_source_path)
  from getDefaultContext import getDefaultContext
  if create_context:
    context = getDefaultContext()
    context.deployment_config = config
    return context
