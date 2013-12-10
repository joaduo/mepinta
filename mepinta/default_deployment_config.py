# -*- coding: utf-8 -*-
'''
Mepinta
'''
import os

file_dir = os.path.dirname(__file__)

class default_deployment_config(object):
  mepinta_source_path = file_dir
  deployment_path = os.path.join(file_dir, 'deployment')
  plugins_sets = dict(c_and_cpp=['basic', 'k3dv1'])
#  libk3dsdk_path = '${libk3dsdk_path}'
#  libgsigc2_path = '${libgsigc2_path}'
#  libboost_unit_test_framework_path = '${libboost_unit_test_framework_path}'


def smokeTestModule():
  from common.log.debugPrint import debugPrint
  settings = default_deployment_config()
  for name in dir(settings):
    if not name.startswith('_'):
      debugPrint(getattr(settings, name))

if __name__ == "__main__":
  smokeTestModule()
