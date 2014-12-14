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
from plugins.c_and_cpp.processors.k3dv1.mesh.modifiers.base.MeshModifierBase import MeshModifierBase


class ExtrudeFaces(MeshModifierBase):

    def define(self, inputs, internals, functions, outputs, createMesh, updateMesh):
        #(self, inputs, internals, functions, outputs):
        inputs.segments = DataProperty('k3d::int32_t')
        inputs.group_faces = DataProperty('k3d::bool_t')
        inputs.group_normals = DataProperty('k3d::bool_t')
        inputs.select_new_faces = DataProperty('k3d::bool_t')
        inputs.distance = DataProperty('k3d::double_t')
        inputs.inset = DataProperty('k3d::double_t')
        internals.extrude_vertices = DataProperty('mepinta::internal_any')
        internals.point_map = DataProperty('mepinta::internal_any')

        createMesh.dpdencies += [inputs.segments,
                                 inputs.group_faces,
                                 inputs.group_normals,
                                 inputs.select_new_faces,
                                 internals.extrude_vertices,
                                 internals.point_map, ]
        updateMesh.dpdencies += [inputs.distance,
                                 inputs.inset,
                                 internals.extrude_vertices,
                                 internals.point_map, ]

manifest = ExtrudeFaces

if __name__ == "__main__":
    from mepinta.context.MepintaContext import MepintaContext
    from mepinta.plugins_manifest.PluginManifestTester import PluginManifestAutoTester
    context = MepintaContext('c_and_cpp')
    plugin_instance = manifest(context=context)
    context.log(manifest)
    PluginManifestAutoTester(context=context).test(plugin_instance)
