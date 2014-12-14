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

from getDefaultContext import getDefaultContext
from pipeline_backend.logging.logging import LOG_INFO
from plugins_tests.base.K3dMeshPluginTest import K3dMeshPluginTest


class SelectFaceByNumber(K3dMeshPluginTest):

    def __post_init__(self):
        import plugins.c_and_cpp.processors.k3dv1.mesh.modifiers.deformation.MorphPoints as morph
        self.testedProcessors.append(morph)

    def _createInputMesh(self, test_pline):
        import plugins.c_and_cpp.processors.k3dv1.mesh.input.file.OBJMeshReader as obj_rdr
        import plugins.c_and_cpp.processors.k3dv1.mesh.generators.polyhedron.PolyCone as cone
        import plugins.c_and_cpp.processors.k3dv1.mesh.selection.SelectPointsExpression as sel_exp

        cone_node = test_pline.append(cone)
        test_pline.setValue(cone_node.inputs.radius, 2)
        test_pline.setValue(cone_node.inputs.height, 2)
        test_pline.setValue(cone_node.inputs.u_segments, 6)
        test_pline.setValue(cone_node.inputs.v_segments, 6)

        obj_node = test_pline.append(obj_rdr)
        test_pline.setValue(obj_node.inputs.file, '/home/jduo/output.obj')
        test_pline.defaultMarked.append(obj_node.functions.loadMesh)

        sel_node = test_pline.append(sel_exp)
        test_pline.setValue(sel_node.inputs.weight_expression,  "1")

    def definePluginPipeline(self, test_pline):
        morph = self.testedProcessors[0]
        morph_node = test_pline.append(morph)

        test_pline.setValue(morph_node.inputs.target_amount, 0.5)
        cone_node = test_pline.getNodesDict()['PolyCone 1']
        test_pline.connect(morph_node.inputs.target, cone_node.outputs.mesh)

    def getTimeParameters(self):
        return self.time.startEndStepSleep(start=0., end=1., step=0.5, sleep=0.05)

    def stressPipeline(self, test_pline, time):
        import math
        nodes = test_pline.getNodesDict()
        morph_node = nodes['MorphPoints 1']
        test_pline.setValue(morph_node.inputs.target_amount, math.cos(time) / 3.)


test = SelectFaceByNumber

if __name__ == "__main__":
    sfbn = SelectFaceByNumber(getDefaultContext(LOG_INFO))
