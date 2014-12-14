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

from mepinta.plugins_manifest import ProcessorManifestBase, DataProperty, FunctionProperty


class TransformPoints(ProcessorManifestBase):

    def define(self, inputs, internals, functions, outputs):
        inputs.mesh = DataProperty('k3dv1_Mesh')
        inputs.matrix = DataProperty('k3dv1_Matrix4')

        outputs.mesh = DataProperty('k3dv1_Mesh')
        functions.on_deform_mesh = FunctionProperty()

        functions.on_deform_mesh.dpdencies += [inputs.mesh                                               , inputs.matrix]
        outputs.mesh.dpdencies += [functions.on_deform_mesh, ]

manifest = TransformPoints

if __name__ == "__main__":
    from mepinta.context.MepintaContext import MepintaContext
    from mepinta.plugins_manifest.PluginManifestTester import PluginManifestTester
    context = MepintaContext('c_and_cpp')
    plugin_instance = manifest(context=context)
    context.log(manifest)
    PluginManifestTester(context=context).test(plugin_instance)
