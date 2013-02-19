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

from mepinta.plugins_manifest import PluginManifestBase, DataProperty, FunctionProperty, \
  GenericEnum

class PluginManifestDummy(PluginManifestBase):
  def define(self, inputs, internals, functions, outputs):
    '''Adds the material property to a node. '''
    inputs.material = DataProperty('k3d::imaterial')
    outputs.mesh = DataProperty('k3d::mesh')
    functions.updateMeshTopology = FunctionProperty()
    functions.updateMeshGeometry = FunctionProperty()

    functions.updateMeshTopology.dpdencies += [inputs.material, ]
    functions.updateMeshGeometry.dpdencies += [functions.updateMeshTopology, ]

    outputs.mesh.dpdencies += [functions.updateMeshTopology,
                               functions.updateMeshGeometry, ]

    inputs.u_segments = DataProperty('k3d::int32_t')
    inputs.v_segments = DataProperty('k3d::int32_t')
    inputs.radius = DataProperty('k3d::double_t')
    inputs.u_power = DataProperty('k3d::double_t')
    inputs.v_power = DataProperty('k3d::double_t')
    inputs.primitive = GenericEnum(SPHERE=0, QUAD_ONLY_SPHERE=1, SPHEREIZED_CYLINDER=2).setDefault('SPHERE')

    functions.updateMeshTopology.dpdencies += [inputs.u_segments,
                                     inputs.v_segments,
                                     inputs.primitive, ]
    functions.updateMeshGeometry.dpdencies += [inputs.u_segments,
                                     inputs.v_segments,
                                     inputs.radius,
                                     inputs.u_power,
                                     inputs.v_power,
                                     inputs.primitive, ]

manifest = PluginManifestDummy

if __name__ == "__main__":
  from default_context import getDefaultContext
  PluginManifestDummy(context=getDefaultContext())
