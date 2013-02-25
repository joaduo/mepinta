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

from mepinta.plugins_manifest import DataProperty
from plugins.c_and_cpp.processors.k3dv1.mesh.generators.base.MeshSourceManifestBase import MeshSourceManifestBase

class PolyCylinder(MeshSourceManifestBase):
  def define(self, inputs, internals, functions, outputs, updateMeshTopology, updateMeshGeometry):
    inputs.u_segments = DataProperty('k3d::int32_t')
    inputs.v_segments = DataProperty('k3d::int32_t')
    inputs.top_cap = DataProperty('k3d::bool_t')
    inputs.bottom_cap = DataProperty('k3d::bool_t')
    inputs.radius = DataProperty('k3d::double_t')
    inputs.z_max = DataProperty('k3d::double_t')
    inputs.z_min = DataProperty('k3d::double_t')
    inputs.u_power = DataProperty('k3d::double_t')
    inputs.top_segments = DataProperty('k3d::int32_t')
    inputs.bottom_segments = DataProperty('k3d::int32_t')
    
    #updateMeshTopology.dpdencies += [inputs.u_segments,
    #                                 inputs.v_segments,
    #                                 inputs.top_cap,
    #                                 inputs.bottom_cap,
    #                                 inputs.top_segments,
    #                                 inputs.bottom_segments,]
    #updateMeshGeometry.dpdencies += [inputs.u_segments,
    #Remove the function, since it won't be used
    outputs.mesh.dpdencies.remove(updateMeshGeometry)
    #TODO: This is wrong. All the process is done in updateMeshTopology
    updateMeshTopology.dpdencies += [inputs.u_segments,
                                     inputs.v_segments,
                                     inputs.top_cap,
                                     inputs.bottom_cap,
                                     inputs.top_segments,
                                     inputs.bottom_segments,
                                     inputs.z_min,
                                     inputs.z_max,
                                     inputs.radius,
                                     inputs.u_power,
                                     inputs.material,]


manifest = PolyCylinder

if __name__ == "__main__":
  from mepinta.context.MepintaContext import MepintaContext
  from mepinta.plugins_manifest.PluginManifestTester import PluginManifestTester
  context = MepintaContext('c_and_cpp')
  plugin_instance = manifest(context=context)
  context.log(manifest)
  PluginManifestTester(context=context).test(plugin_instance)
