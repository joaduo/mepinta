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
from plugins_tests.base.K3dMeshPluginTest import K3dMeshPluginTest

class QSlim(K3dMeshPluginTest):
  def __post_init__(self):
    import plugins.c_and_cpp.processors.k3dv1.mesh.modifiers.polyhedron.QSlim as qslim
    self.testedProcessors.append(qslim)

  def definePluginPipeline(self, test_pline):
    qslim = self.testedProcessors[0]
    qslim_node = test_pline.append(qslim)
    test_pline.setValue(qslim_node.inputs.face_count, 10)
    test_pline.setValue(qslim_node.inputs.contraction_type, 0)
    test_pline.setValue(qslim_node.inputs.placement_policy, 0)
    test_pline.setValue(qslim_node.inputs.quadric_weighting, 0)
    test_pline.setValue(qslim_node.inputs.boundary_weight, 10.0)
    test_pline.setValue(qslim_node.inputs.compactness_ratio, 10.0)
    test_pline.setValue(qslim_node.inputs.meshing_penalty, 10.0)

  def getTimeParameters(self):
    return self.time.startEndStepSleep(start=0., end=3., step=0.5, sleep=0.05)

  def stressPipeline(self, test_pline, time):
    K3dMeshPluginTest.stressPipeline(self, test_pline, time)
    qslim_node = test_pline.getNodesDict()['QSlim 1']
    test_pline.setValue(qslim_node.inputs.face_count, 10 * time)

test = QSlim

if __name__ == "__main__":
  from mepinta.testing.plugins_testing.PluginTestAutoTester import PluginTestAutoTester
  from getDefaultContext import getDefaultContext
  from pipeline_backend.logging.logging import LOG_INFO
  PluginTestAutoTester(getDefaultContext(LOG_INFO)).test(test, gui=False)
