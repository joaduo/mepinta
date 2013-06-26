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
import unittest

class EmptyGraphTest(ProcessorPluginTestBase, unittest.TestCase):
  def __post_init__(self):
    import plugins.python.processors.actiontree.UndoableGraph.generator.EmptyGraph as empty_graph
    self.testedProcessors.append(empty_graph)
    self.context_name = 'python'

  def definePluginPipeline(self, test_pline):
    empty_graph = self.testedProcessors[0]
    empty_graph_node = test_pline.append(empty_graph)
    test_pline.setValue(empty_graph_node.inputs.context_name, self.context_name)

    import plugins.python.processors.actiontree.UndoableGraph.modifier.CreateNode as create_node
    crt_nd_node = test_pline.append(create_node)
    #import plugins.python.processors.demov1.Geometry2D.generator.Circle
    processor_name = 'demov1.Geometry2D.generator.Circle'
    test_pline.setValue(crt_nd_node.inputs.processor_name, processor_name)
    test_pline.setValue(crt_nd_node.inputs.context_name, self.context_name)

    return empty_graph_node

  def _createOutputGraph(self, test_pline):
    gui = self.context.nodebox_gui
    if gui:
      import plugins.python.processors.actiontree.UndoableGraph.output.NodeboxRenderer as renderer
    else:
      import plugins.python.processors.actiontree.UndoableGraph.output.StdoutPrint as renderer
    output_node = test_pline.append(renderer)
    if gui:
      test_pline.uiDefaultEvaluated.append(output_node.functions.render)
    test_pline.setValue(output_node.inputs.context_name, self.context_name)
    test_pline.defaultEvaluated.append(output_node.functions.render)
    return output_node

  def definePipeline(self, test_pline):
    #self._createInputGraph(test_pline)
    self.definePluginPipeline(test_pline)
    self._createOutputGraph(test_pline)

  def getTimeParameters(self):
    self.time.frames(1)

  def stressPipeline(self, test_pline, time):
    pass

def testModule():
  from mepinta.testing.plugins_testing.PluginTestAutoTester import PluginTestAutoTester
  from getDefaultContext import getDefaultContext
  tester = PluginTestAutoTester(context=getDefaultContext())
  tester.shallowTest(gui=True)#.smokeTest()#.test(gui=False)
  #tester.simpleTest(gui=False)

if __name__ == "__main__":
  testModule()
  #unittest.main()

