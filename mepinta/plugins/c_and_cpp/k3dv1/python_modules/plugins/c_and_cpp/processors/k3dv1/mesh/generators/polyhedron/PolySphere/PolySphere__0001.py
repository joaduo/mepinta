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

from mepinta.plugins_manifest import DataProperty, GenericEnum
from plugins.c_and_cpp.processors.k3dv1.mesh.generators.base.MeshSourceManifestBase import MeshSourceManifestBase

class PolySphere(MeshSourceManifestBase):
  def define(self, inputs, internals, functions, outputs, updateMeshTopology, updateMeshGeometry):
    inputs.u_segments = DataProperty('k3d::int32_t')
    inputs.v_segments = DataProperty('k3d::int32_t')
    inputs.radius = DataProperty('k3d::double_t')
    inputs.u_power = DataProperty('k3d::double_t')
    inputs.v_power = DataProperty('k3d::double_t')
    inputs.primitive = GenericEnum(SPHERE=0, QUAD_ONLY_SPHERE=1, SPHEREIZED_CYLINDER=2).setDefault('SPHERE')
    
    updateMeshTopology.dpdencies += [inputs.u_segments,
                                     inputs.v_segments,
                                     inputs.primitive,]
    updateMeshGeometry.dpdencies += [inputs.u_segments,
                                     inputs.v_segments,
                                     inputs.radius,
                                     inputs.u_power,
                                     inputs.v_power,
                                     inputs.primitive,]

manifest = PolySphere

if __name__ == "__main__":
  from mepinta.context.MepintaContext import MepintaContext
  from mepinta.plugins_manifest.PluginManifestTester import PluginManifestAutoTester
  context = MepintaContext('c_and_cpp')
  plugin_instance = manifest(context=context)
  context.log(manifest)
  PluginManifestAutoTester(context=context).test(plugin_instance)
