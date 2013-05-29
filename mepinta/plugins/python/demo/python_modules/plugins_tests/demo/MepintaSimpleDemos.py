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
#from mepinta.testing.plugins_testing.processor.base import ProcessorPluginTestBase
from common.abstract.FrameworkBase import FrameworkBase
from mepinta.testing.plugins_testing.test_pipeline.SimpleTestPipeline import SimpleTestPipeline
from plugins_tests.python.processors.demov1.Geometry2D.modifier.DeformationExpression.DeformationExpression__0001 import DeformationExpression
from mepinta.testing.plugins_testing.test_pipeline.InotifySimpleTestPipeline import InotifySimpleTestPipeline
from mepinta.testing.plugins_testing.graphviz.PipelineGraphvizTranslator import PipelineGraphvizTranslator
from mepinta_devtools.ide_projects.FileManager import FileManager
from common.shellcmds.CommandRunner import CommandRunner
import os

class MepintaSimpleDemos(FrameworkBase):
  def visualizeGraphXdot(self):
    test_pline = self.__getTestPipeline()
    graphviz_translator = PipelineGraphvizTranslator(self.context)
    graphviz_str = graphviz_translator.translate(test_pline.getPipeline())
    path = './pipeline.dot'
    FileManager(self.context).saveTextFile(path, graphviz_str, overwrite=True)
    CommandRunner(self.context).run('xdot %s' % path)
    os.remove(path)

  def evaluatePipelineAndPrint(self):
    test_pline = self.__getTestPipeline()
    test_pline.evaluateProp()

  def nodeboxInteractivePipeline(self):
    self.log('Demo not yet implemented')

  def __getTestPipeline(self):
    #test_pline = SimpleTestPipeline(self.context)
    test_pline = InotifySimpleTestPipeline(self.context)
    deformation_expression_test = DeformationExpression(self.context)
    deformation_expression_test.definePipeline(test_pline)
    #test_pline.evaluateProp()
    return test_pline



#    from mepinta.testing.plugins_testing.gui.SimpleTestPipelineGui import SimpleTestPipelineGui
#    from mepinta.testing.plugins_testing.nodebox.NodeBoxSimplePipelineOutput import NodeBoxSimplePipelineOutput
#    gui = SimpleTestPipelineGui(self.context, test_pline=test_pline)
#    gui.run()
#    NodeBoxSimplePipelineOutput(test_pline.getPipeline(), 600, 600).run()


def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()
  MepintaSimpleDemos(context).run()

if __name__ == "__main__":
  test_module()
