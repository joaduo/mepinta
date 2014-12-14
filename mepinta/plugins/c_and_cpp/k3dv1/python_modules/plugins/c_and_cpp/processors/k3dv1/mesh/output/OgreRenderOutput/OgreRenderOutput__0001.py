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

from mepinta.plugins_manifest import ProcessorManifestBase, DataProperty, FunctionProperty, \
    directed, Functum


class OgreRenderOutput(ProcessorManifestBase):
    build = False

    def define(self, inputs, internals, functions, outputs):
        # Inputs
        inputs.opengl_context = DataProperty('mepinta::internal_any*')
        inputs.ogre_context = DataProperty('mepinta::internal_any*')
        inputs.width = DataProperty('int')
        inputs.height = DataProperty('int')
        inputs.position_x = DataProperty('double')
        inputs.position_y = DataProperty('double')
        inputs.position_z = DataProperty('double')
        inputs.mesh = DataProperty('k3d::mesh*')
        # functions
        functions.renderMesh = FunctionProperty()
        # dependencies
        functions.renderMesh.dpdencies += [
            inputs.opengl_context,
            inputs.ogre_context,
            inputs.width,
            inputs.height,
            inputs.position_x,
            inputs.position_y,
            inputs.position_z,
            inputs.mesh,
        ]

manifest = OgreRenderOutput

if __name__ == "__main__":
    from mepinta.context.MepintaContext import MepintaContext
    from mepinta.plugins_manifest.PluginManifestTester import PluginManifestTester
    context = MepintaContext('c_and_cpp')
    plugin_instance = manifest(context=context)
    context.log(manifest)
    PluginManifestTester(context=context).test(plugin_instance)
