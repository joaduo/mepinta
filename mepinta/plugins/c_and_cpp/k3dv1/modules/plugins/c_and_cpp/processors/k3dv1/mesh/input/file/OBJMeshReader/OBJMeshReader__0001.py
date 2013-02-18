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
from plugins.c_and_cpp.processors.k3dv1.mesh.input.file.base.MeshReaderManifestBase import MeshReaderManifestBase

class OBJMeshReader(MeshReaderManifestBase):
  def define(self, inputs, internals, functions, outputs, loadMesh):
    pass

manifest = OBJMeshReader

if __name__ == "__main__":
  from mepinta.context.MepintaContext import MepintaContext
  from mepinta.plugins_manifest.PluginManifestTester import PluginManifestTester
  context = MepintaContext('c_and_cpp')
  plugin_instance = manifest(context=context)
  context.log(manifest)
  PluginManifestTester(context=context).test(plugin_instance)
