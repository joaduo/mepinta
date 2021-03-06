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
from pipeline_backend.logging.logging import LOG_INFO
from plugins_tests.base.K3dMeshPluginTest import K3dMeshPluginTest


class SelectPointsExpression(K3dMeshPluginTest):

    def __post_init__(self):
        import plugins.c_and_cpp.processors.k3dv1.mesh.selection.points.SelectPointsExpression as select
        self.testedProcessors.append(select)

    def definePluginPipeline(self, test_pline):
        select = self.testedProcessors[0]
        select_node = test_pline.append(select)
        test_pline.setValue(select_node.inputs.weight_expression, 't')
        test_pline.setValue(select_node.inputs.time_name, 't')
        test_pline.setValue(select_node.inputs.time, 1)

    def getTimeParameters(self):
        return self.time.startEndStepSleep(start=0., end=5., step=0.5, sleep=0.05)

    def stressPipeline(self, test_pline, time):
        K3dMeshPluginTest.stressPipeline(self, test_pline, time)
        select_node = test_pline.getNodesDict()['SelectPointsExpression 1']
        test_pline.setValue(select_node.inputs.weight_expression, 't')
        test_pline.setValue(select_node.inputs.time_name, 't')
#    qslim_node = test_pline.getNodesDict()['QSlim 1']
#    test_pline.setValue(qslim_node.inputs.face_count, 10*time)

test = SelectPointsExpression

if __name__ == "__main__":
    from getDefaultContext import getDefaultContext
    from mepinta.testing.plugins_testing.PluginTestAutoTester import PluginTestAutoTester
    PluginTestAutoTester(getDefaultContext(LOG_INFO)).test(test)  # ,gui=False)
