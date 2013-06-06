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
#TODO
#from plugins.c_and_cpp.processors.k3dv1.mesh.modifiers.base.SimpleMeshModifierBase import SimpleMeshModifierBase

class MakeSDS(MeshModifierBase):
  def define(self, inputs, internals, functions, outputs, createMesh, updateMesh):
    inputs.interpolate_boundary = DataProperty('k3d::bool_t')

    createMesh.dpdencies += inputs.interpolate_boundary

manifest = MakeSDS

if __name__ == "__main__":
  from getDefaultContext import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  PluginManifestAutoTester(getDefaultContext()).test(manifest, gui=False)

