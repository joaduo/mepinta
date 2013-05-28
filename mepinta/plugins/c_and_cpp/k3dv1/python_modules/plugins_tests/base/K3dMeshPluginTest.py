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
from mepinta.testing.plugins_testing.processor.base import ProcessorPluginTestBase

class K3dMeshPluginTest(ProcessorPluginTestBase):
  def __post_init__(self):
    self.output_file = '/home/jduo/output.k3d'

  def _createInputMesh(self, test_pline):
    import plugins.c_and_cpp.processors.k3dv1.mesh.generators.polyhedron.PolySphere as sphere
    sphere_node = test_pline.append(sphere)
    test_pline.setValue(sphere_node.inputs.u_segments, 8)
    test_pline.setValue(sphere_node.inputs.v_segments, 8)
    test_pline.setValue(sphere_node.inputs.primitive, 'QUAD_ONLY_SPHERE')
    test_pline.setValue(sphere_node.inputs.radius, 5.0)
    return sphere_node

  def _selectAllInputVertexs(self, test_pline):
    import plugins.c_and_cpp.processors.k3dv1.mesh.selection.points.SelectPointsExpression as select
    select_node = test_pline.append(select)
    test_pline.setValue(select_node.inputs.weight_expression, '1')
    return select_node

  def _createOutputMesh(self, test_pline):
    import plugins.c_and_cpp.processors.k3dv1.mesh.output.file.K3DMeshWriter as k3d_wtr
    write_node = test_pline.append(k3d_wtr)
    test_pline.setValue(write_node.inputs.file, self.output_file)
    return write_node

  def validateOutputMesh(self):
    raise NotImplementedError("Implement!")

  def definePluginPipeline(self):
    raise NotImplementedError("Implement on children classes!")

  def definePipeline(self, test_pline):
    self._createInputMesh(test_pline)
    self.definePluginPipeline(test_pline)
    write_node = self._createOutputMesh(test_pline)
    test_pline.default_evaluated.append(write_node.functions.writeMesh)

  def stressPipeline(self, test_pline, time):
    import math
    sphere_node = test_pline.getNodesDict()['PolySphere 1']
    test_pline.setValue(sphere_node.inputs.radius, math.cos(time) * 0.5 + 1)
    test_pline.setValue(sphere_node.inputs.u_segments, time * 2)
    test_pline.setValue(sphere_node.inputs.v_segments, time)


if __name__ == "__main__":
  pass
