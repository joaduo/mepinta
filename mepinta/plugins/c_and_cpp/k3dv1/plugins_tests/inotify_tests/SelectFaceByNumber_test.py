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
        import plugins.c_and_cpp.processors.k3dv1.mesh.selection.bynumber.SelectFaceByNumber as select
        self.testedProcessors.append(select)

    def _createInputMesh(self, test_pline):
        import plugins.c_and_cpp.processors.k3dv1.mesh.input.file.OBJMeshReader as obj_rdr
        obj_node = test_pline.append(obj_rdr)
        test_pline.setValue(obj_node.inputs.file, '/home/jduo/output.obj')
        test_pline.defaultMarked.append(obj_node.functions.loadMesh)
        return obj_node

    def definePluginPipeline(self, test_pline):
        select = self.testedProcessors[0]
        n_sel = test_pline.append(select)
        import plugins.c_and_cpp.processors.k3dv1.mesh.modifiers.polyhedron.ExtrudeFaces as ext_fac
        n_ext = test_pline.append(ext_fac)

        test_pline.setValue(n_sel.inputs.primitive_number, 0)
        test_pline.setValue(n_sel.inputs.face_index, 0)
        test_pline.setValue(n_ext.inputs.segments, 2)
        test_pline.setValue(n_ext.inputs.distance, 4.0)

    def getTimeParameters(self):
        return self.time.startEndStepSleep(end=-15., step=2, sleep=0.1)

    def stressPipeline(self, test_pline, time):
        nodes = test_pline.getNodesDict()
        node_sel = nodes['SelectFaceByNumber 1']
        test_pline.setValue(node_sel.inputs.face_index, time *2)
        node_ext = nodes['ExtrudeFaces 1']
        test_pline.setValue(node_ext.inputs.distance, 1.0 + time/4.0)
        test_pline.setValue(node_ext.inputs.segments, 1.0 + time/4.0)


test = SelectFaceByNumber

if __name__ == "__main__":
    sfbn = SelectFaceByNumber(getDefaultContext(LOG_INFO))
