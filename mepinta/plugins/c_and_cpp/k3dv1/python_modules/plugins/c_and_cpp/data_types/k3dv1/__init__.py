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


def getK3dList():
  #  k3d_libs = """libk3dsdk-expression.so
  #libk3dsdk-ftgl.so
  #libk3dsdk-glew.so
  #libk3dsdk-half.so
  #libk3dsdk-ngui.so
  #libk3dsdk-opengl.so
  #libk3dsdk-parallel.so
  #libk3dsdk-python-arrays.so
  #libk3dsdk-python-atk.so
  #libk3dsdk-python-b.so
  #libk3dsdk-python-const-arrays.so
  #libk3dsdk-python-interfaces.so
  #libk3dsdk-python-mesh.so
  #libk3dsdk-python-primitives.so
  #libk3dsdk-python.so
  #libk3dsdk-python-values.so
  #libk3dsdk-qtui-script.so
  #libk3dsdk-qtui.so
  #libk3dsdk-resource.so
  #libk3dsdk-sgi-tesselator.so
  #libk3dsdk.so
  #libk3dsdk-subdivision-surface.so
  #libk3d-solar-solpos.so"""

  libs = [
  "/usr/lib/libsigc-2.0.so",
  "/home/jduo/002-k3d/build/dependencies/boost_1_45_0/bin.v2/libs/test/build/gcc-4.4.3/release/threading-multi/libboost_unit_test_framework.so.1.45.0",
  ]
  k3d_libs_path = "/home/jduo/Projects/Informatica/k3d/build/renamed/lib/"
  k3d_libs = """libk3dsdk.so
libk3dsdk-expression.so"""
  libs += [k3d_libs_path + lib for lib in k3d_libs.splitlines()]
  return libs

def loadK3dLibs():
  from mepinta.pipeline.lo_cpp.load_library_stand_alone import load_library_stand_alone
  libs = getK3dList()
  libs += ["/home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/k3dv1/k3dv1MPExtension/Debug/libk3dv1MPExtension.so"]
  libs += ["/home/jduo/001-Mepinta/EclipseProjects_Basic_Data_Types/Mepinta/MepintaLocal/src/mepinta/lib/libMepintaArgsApi.so"]
  libs += ["/home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/Mepinta/MepintaArgsApiCpp/Debug/libMepintaArgsApiCpp.so"]

  for path in libs:
    load_library_stand_alone(path, symbol="global")

done = False
def preLoadPlugin(context):
  global done
  if not done:
    loadK3dLibs()
    done = True

