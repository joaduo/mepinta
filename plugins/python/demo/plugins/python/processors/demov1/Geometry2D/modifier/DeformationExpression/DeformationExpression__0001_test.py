# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

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
from plugins.python.processors.demov1.Geometry2D.modifier.base.Geometry2DPluginTest import Geometry2DPluginTest
from unittest import TestCase


class DeformationExpression(Geometry2DPluginTest, TestCase):

    def __post_init__(self):
        import plugins.python.processors.demov1.Geometry2D.modifier.DeformationExpression as deformation_expression
        self.testedProcessors.append(deformation_expression)

    def definePluginPipeline(self, test_pline):
        deformation_expression = self.testedProcessors[0]
        deformation_node = test_pline.append(deformation_expression)
        test_pline.setValue(deformation_node.inputs.x_expression, 'x*t')
        test_pline.setValue(deformation_node.inputs.y_expression, 'y*t')
        test_pline.setValue(deformation_node.inputs.time, 1.0)

    def getTimeParameters(self):
        return self.time.startEndStepSleep(start=0., end=3., step=0.5, sleep=0.05)

    def stressPipeline(self, test_pline, time):
        Geometry2DPluginTest.stressPipeline(self, test_pline, time)
        deformation_node = test_pline.getNodesDict()['DeformationExpression 1']
        test_pline.setValue(deformation_node.inputs.time, 10 * time)

if __name__ == "__main__":
    #  import unittest
    #  unittest.main()
    from mepinta.testing.plugins_testing.PluginTestAutoTester import PluginTestAutoTester
    from mepinta.context.MepintaContext import MepintaContext
    PluginTestAutoTester(context=MepintaContext()).test()
