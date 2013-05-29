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

class Geometry2DPluginTest(ProcessorPluginTestBase):
  def definePluginPipeline(self):
    raise NotImplementedError("Implement on children classes!")

  def _createInputGeometry(self, test_pline):
    import plugins.python.processors.demov1.Geometry2D.generator.Circle as circle
    circle_node = test_pline.append(circle)
    test_pline.setValue(circle_node.inputs.segments, 1)
    test_pline.setValue(circle_node.inputs.radius, 5.0)
    return circle_node

  def _createOutputGeometry(self, test_pline):
    import plugins.python.processors.demov1.Geometry2D.output.StdoutPrint as stdout_print
    write_node = test_pline.append(stdout_print)
    return write_node

  def definePipeline(self, test_pline):
    self._createInputGeometry(test_pline)
    self.definePluginPipeline(test_pline)
    output_node = self._createOutputGeometry(test_pline)
    test_pline.default_evaluated.append(output_node.functions.printToStdout)

  def stressPipeline(self, test_pline, time):
    import math
    sphere_node = test_pline.getNodesDict()['PolySphere 1']
    test_pline.setValue(sphere_node.inputs.radius, math.cos(time) * 0.5 + 1)
    test_pline.setValue(sphere_node.inputs.segments, time * 2)

if __name__ == "__main__":
  pass
