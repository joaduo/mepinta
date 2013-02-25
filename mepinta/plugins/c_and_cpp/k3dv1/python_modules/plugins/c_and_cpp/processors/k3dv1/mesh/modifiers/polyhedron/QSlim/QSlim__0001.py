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
from plugins.c_and_cpp.processors.k3dv1.mesh.modifiers.base.SimpleMeshModifierBase import SimpleMeshModifierBase

class QSlim(SimpleMeshModifierBase):
  def define(self, inputs, internals, functions, outputs, createMesh):
    #Inputs
    inputs.material = DataProperty('k3d::imaterial')   
    inputs.face_count = DataProperty('k3d::int32_t')
    inputs.contraction_type = GenericEnum(EDGE=0, FACE=1)
    inputs.placement_policy = GenericEnum(OPTIMAL=0, LINE=1, ENDORMID=2, ENDPOINTS=3)
    inputs.quadric_weighting = GenericEnum(UNIFORM=0, AREA=1, ANGLE=2)
    inputs.boundary_weight = DataProperty('k3d::double_t')
    inputs.compactness_ratio = DataProperty('k3d::double_t')
    inputs.meshing_penalty = DataProperty('k3d::double_t')

    #Set dependencies   
    createMesh.dpdencies +=  [inputs.material,
                              inputs.face_count,
                              inputs.contraction_type,
                              inputs.placement_policy,
                              inputs.quadric_weighting,
                              inputs.boundary_weight,
                              inputs.compactness_ratio,
                              inputs.meshing_penalty,]

manifest = QSlim

if __name__ == "__main__":
  from default_context import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  PluginManifestAutoTester(getDefaultContext()).test(manifest)#, gui=True)


