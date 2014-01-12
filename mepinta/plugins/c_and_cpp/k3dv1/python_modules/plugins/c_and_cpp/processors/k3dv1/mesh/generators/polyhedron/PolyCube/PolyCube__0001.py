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

class PolyCube(MeshSourceManifestBase):
  def define(self, inputs, internals, functions, outputs, updateMeshTopology, updateMeshGeometry):
    #Inputs
    inputs.rows = DataProperty('k3d::int32_t')
    inputs.columns = DataProperty('k3d::int32_t')
    inputs.slices = DataProperty('k3d::int32_t')
    inputs.width = DataProperty('k3d::double_t')
    inputs.height = DataProperty('k3d::double_t')
    inputs.depth = DataProperty('k3d::double_t')

    #Set dependencies
    updateMeshTopology.dpdencies += [ inputs.rows
                                      , inputs.columns
                                      , inputs.slices]
    updateMeshGeometry.dpdencies += [ inputs.rows
                                      , inputs.columns
                                      , inputs.slices
                                      , inputs.width
                                      , inputs.height
                                      , inputs.depth]

manifest = PolyCube

if __name__ == "__main__":
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  from mepinta.context.MepintaContext import MepintaContext
  PluginManifestAutoTester(MepintaContext('c_and_cpp')).test(manifest)
