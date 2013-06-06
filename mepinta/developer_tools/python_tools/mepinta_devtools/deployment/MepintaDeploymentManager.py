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
from common.abstract.FrameworkBase import FrameworkBase

class MepintaDeploymentManager(FrameworkBase):
  '''
  Comandos básicos
    deploy.py <path> [-f]
    <deployment>/set_python_paths.sh
    <deployment>/mepinta_tests.py
    <deployment>/mepinta_demo.py
    <deployment>/mepinta_compile.py
    <deployment>/mepinta_tools.py
      eclipse
        core
        c_and_cpp_plugins
        python_plugins
      qt
        c_and_cpp_plugins
    <deployment>/deployment_config.py
  hacer un módulo
    deployment_config.py
      mepinta_src_path
      libk3dsdk_path
      libgsigc2_path
      libboost_unit_test_framework_path
  Responsibilities:
    Create a new Mepinta Deployment given a deployment path.
    Create the plugins deployment
    Create the core deployment so libs
      backend_c and backend_cpp
      Shedskin: build_shedskin_module.py <pipeline_lo_facade|load_library_stand_alone>
        pipeline_lo_facade and load_library_stand_alone
    Create a run script that loads (should be taken in count automatically later, since the plugin should specify this?)
      "/usr/lib/libsigc-2.0.so",
      "/home/jduo/002-k3d/build/dependencies/boost_1_45_0/bin.v2/libs/test/build/gcc-4.4.3/release/threading-multi/libboost_unit_test_framework.so.1.45.0",
      "libk3dsdk.so libk3dsdk-expression.so"
      backend_c and backend_cpp
    Create the Eclipse core deployment for dev purposes
      <deployment>/deployment_config.py
      core/python_core
      developer_tools/python_tools
      libs/python/python_common
    Create Eclipse shedskin deployment for dev purposes ??
      pipeline_lo_facade and load_library_stand_alone
    Create the Plugins' QT or Eclipse deployment for dev purposes.

    Leave everything in its place to compile and run (mepinta and its tests)

  Goal:
  This deployment is used by Mepinta to find available plugins to load.
  Also lets the developer have in one place all the required files for
  development. (headers and libraries (.so))
  '''

def test_module():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  test_module()
