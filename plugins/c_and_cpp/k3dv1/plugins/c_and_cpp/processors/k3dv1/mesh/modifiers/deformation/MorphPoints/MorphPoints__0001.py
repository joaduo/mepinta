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
from plugins.c_and_cpp.processors.k3dv1.mesh.modifiers.deformation.base.SimpleDeformationManifestBase import SimpleDeformationManifestBase


class MorphPoints(SimpleDeformationManifestBase):

    def define(self, inputs, internals, functions, outputs, deformMesh):
        # Inputs
        inputs.target = 'k3d::mesh'
        inputs.target_amount = 'k3d::double_t'
        inputs.xtarget1 = 'k3d::mesh'
        inputs.xtarget_amount1 = 'k3d::double_t'

        # Set dependencies
        deformMesh.dpdencies += [inputs.target,
                                 inputs.target_amount,
                                 inputs.xtarget1,
                                 inputs.xtarget_amount1, ]

manifest = MorphPoints

if __name__ == "__main__":
    from mepinta.testing.plugins_testing.PluginManifestTester import PluginManifestTester
    from getDefaultContext import getDefaultContext
    context = getDefaultContext()
    plugin_instance = manifest(context=context)
    context.log(manifest)
    PluginManifestTester(context=context).test(plugin_instance)
