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
  def definePluginPipeline(self, test_pline):
    raise NotImplementedError("Implement on children classes!")

  def _createInputGeometry(self, test_pline):
    import plugins.python.processors.demov1.Geometry2D.generator.Circle as circle
    circle_node = test_pline.append(circle)
    test_pline.setValue(circle_node.inputs.segments, 1)
    test_pline.setValue(circle_node.inputs.radius, 5.0)
    return circle_node

  def _createOutputGeometry(self, test_pline):
    gui = self.context.nodebox_gui
    if gui:
      import plugins.python.processors.demov1.Geometry2D.output.NodeboxRenderer as renderer
    else:
      import plugins.python.processors.demov1.Geometry2D.output.StdoutPrint as renderer
    output_node = test_pline.append(renderer)
    if gui:
      test_pline.uiDefaultEvaluated.append(output_node.functions.render)
    test_pline.defaultEvaluated.append(output_node.functions.render)
    return output_node

  def definePipeline(self, test_pline):
    self._createInputGeometry(test_pline)
    self.definePluginPipeline(test_pline)
    self._createOutputGeometry(test_pline)

  def stressPipeline(self, test_pline, time):
    import math
    sphere_node = test_pline.getNodesDict()['Circle 1']
    test_pline.setValue(sphere_node.inputs.radius, math.cos(time) * 0.5 + 1)
    test_pline.setValue(sphere_node.inputs.segments, time * 2)

if __name__ == "__main__":
  pass
