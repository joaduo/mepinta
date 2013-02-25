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

from mepinta.plugins_manifest import DataProperty, FunctionProperty
from plugins.c_and_cpp.processors.k3dv1.mesh.base.MaterialSinkBase import MaterialSinkBase

#TODO: rename to createMesh and updateMesh
class MeshSourceManifestBase(MaterialSinkBase):
  def _superClassDefine(self, inputs, internals, functions, outputs):
    '''Creates the common topology for MeshSources plugins .'''
    outputs.mesh = DataProperty('k3d::mesh')
    functions.updateMeshTopology = FunctionProperty()
    functions.updateMeshGeometry = FunctionProperty()
    
    functions.updateMeshTopology.dpdencies +=[inputs.material,]
    functions.updateMeshGeometry.dpdencies +=[functions.updateMeshTopology,]
    
    outputs.mesh.dpdencies += [functions.updateMeshTopology,
                               functions.updateMeshGeometry,]
    return functions.updateMeshTopology,functions.updateMeshGeometry

  def define(self, inputs, internals, functions, outputs, updateMeshTopology, updateMeshGeometry):
    '''
      Implement this method on children classes.
      Example:
        inputs.rows = DataProperty('uint')
        updateMeshTopology.dpdencies += [inputs.rows]
    '''
    pass

manifest = MeshSourceManifestBase

if __name__ == "__main__":
  from mepinta.context.MepintaContext import MepintaContext
  from mepinta.plugins_manifest.PluginManifestTester import PluginManifestAutoTester
  context = MepintaContext('c_and_cpp')
  plugin_instance = manifest(context=context)
  context.log(manifest)
  PluginManifestAutoTester(context=context).test(plugin_instance)
