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

from mepinta.plugins_manifest import ProcessorManifestBase, DataProperty, FunctionProperty,\
    directed, Functum


class DeformationTemporalExpression(ProcessorManifestBase):

    '''
      When the evaluation starts (lets say frame 0)
      Should create vars x*,y*,z* (or whatever the are renamed to)
        x0:current frame
        x1:current frame -1
        x2:current frame -2 and so on...
      Also y0,y1... and z0,z1... so on...
      If the code can't find the sample for the requested frame will use
        the default_sample as sample for that frame. 
    '''

    def define(self, inputs, internals, functions, outputs):
        # Inputs
        inputs.x_function = DataProperty('charp')
        inputs.y_function = DataProperty('charp')
        inputs.z_function = DataProperty('charp')

        inputs.current_frame = DataProperty('int')
        # Forward, Backward, Bidirectional (need to review this)
        inputs.direction = DataProperty('uint')
        # If bidirectional samples are doubled
        inputs.samples_amount = DataProperty('uint')
        inputs.default_sample = DataProperty('k3dv1_Mesh')

        inputs.time = DataProperty('double')
        inputs.time_name = DataProperty('charp')
        inputs.mesh = DataProperty('k3dv1_Mesh')
        # Internals
        internals.last_frame = DataProperty('int')
        internals.samples_storage = DataProperty(
            'internal_any')  # mesh:frame_number
        # Output
        outputs.mesh = DataProperty('k3dv1_Mesh')
        # Functions
        internals.on_deform_mesh = Functum()
        # Demux Functions
        functions.demux_signal = FunctionProperty()

        # Set dependencies
        internals.on_deform_mesh.dpdencies += [inputs.x_function,
                                                inputs.y_function,
                                                inputs.z_function,
                                                inputs.time,
                                                inputs.time_name,
                                                  directed('>', inputs.mesh),
                                                ]

        functions.demux_signal.dpdencies += [internals.on_deform_mesh,
                                             inputs.mesh,
                                             ]
        outputs.mesh.dpdencies += [functions.demux_signal,
                                   directed('<', internals.on_deform_mesh),
                                   ]

manifest = DeformationTemporalExpression

if __name__ == "__main__":
    from mepinta.context.MepintaContext import MepintaContext
    from mepinta.plugins_manifest.PluginManifestTester import PluginManifestTester
    context = MepintaContext('c_and_cpp')
    plugin_instance = manifest(context=context)
    context.log(manifest)
    PluginManifestTester(context=context).test(plugin_instance)
