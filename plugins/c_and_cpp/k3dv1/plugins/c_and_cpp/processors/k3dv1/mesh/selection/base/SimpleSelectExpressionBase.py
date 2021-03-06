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
    Functum, directed


class SimpleSelectExpressionBase(ProcessorManifestBase):

    def _superClassDefine(self, inputs, internals, functions, outputs):
        '''
          Creates a common topology pipeline for selection modifiers based on  math
          expressions. 
          (demuxing the mesh Topology and Geometry updates signals)
        '''
        inputs.mesh = DataProperty('k3d::mesh')
        inputs.weight_expression = DataProperty('k3d::string_t')
        inputs.max_value = DataProperty('k3d::double_t')
        inputs.use_max_value = DataProperty('k3d::int32_t')
        inputs.previous_selection_name = DataProperty('k3d::string_t')
        inputs.time = DataProperty('k3d::double_t')
        inputs.time_name = DataProperty('k3d::string_t')

        outputs.mesh = DataProperty('k3d::mesh')

        internals.updateSelection = Functum()
        functions.demuxMeshSignal = FunctionProperty()

        internals.updateSelection.dpdencies += [directed('>', inputs.mesh),]

        internals.updateSelection.dpdencies += [inputs.weight_expression,
                                                inputs.max_value,
                                                inputs.use_max_value,
                                                inputs.previous_selection_name,
                                                inputs.time,
                                                inputs.time_name, ]

        functions.demuxMeshSignal.dpdencies += [internals.updateSelection,
                                                inputs.mesh, ]

        outputs.mesh.dpdencies += [functions.demuxMeshSignal,
                                   directed('<', internals.updateSelection), ]

        return internals.updateSelection

    def define(self, inputs, internals, functions, outputs, updateSelection):
        '''
          Implement this method on children classes.
          Example:
            inputs.rows = DataProperty('uint')
            updateSelection.dpdencies += [inputs.rows]
        '''
        pass


if __name__ == "__main__":
    pass
