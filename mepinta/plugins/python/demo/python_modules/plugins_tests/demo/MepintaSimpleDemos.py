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
from common.abstract.FrameworkBase import FrameworkBase
from plugins_tests.python.processors.demov1.Geometry2D.modifier.DeformationExpression.DeformationExpression__0001 import DeformationExpression
from mepinta.testing.plugins_testing.test_pipeline.InotifySimpleTestPipeline import InotifySimpleTestPipeline
from mepinta.testing.plugins_testing.graphviz.PipelineGraphvizTranslator import PipelineGraphvizTranslator
from mepinta_devtools.ide_projects.FileManager import FileManager
from common.shellcmds.CommandRunner import CommandRunner
import os

class MepintaSimpleDemos(FrameworkBase):
  '''
  This class gathers simple demos for the demo.py command of a Mepinta deployment.
  Each public method represents a available demo.
  '''
  def visualizeGraphXdot(self):
    ''' Mepinta GUI demo. Shows Pipeline in as a dot graph. '''
    test_pline = self.__getTestPipeline()
    graphviz_translator = PipelineGraphvizTranslator(self.context)
    graphviz_str = graphviz_translator.translate(test_pline.getPipeline())
    path = './pipeline.dot'
    FileManager(self.context).saveTextFile(path, graphviz_str, overwrite=True)
    CommandRunner(self.context).run('xdot %s' % path)
    os.remove(path)

  def evaluatePipelineAndPrint(self):
    ''' Mepinta Pipeline demo. Output only to console.'''
    test_pline = self.__getTestPipeline()
    test_pline.evaluateProp()

  def nodeboxInteractivePipeline(self):
    ''' Mepinta interactive GUI demo. Shows Pipeline and lets the user change properties values.'''
    from mepinta.testing.plugins_testing.gui.SimpleTestPipelineGui import SimpleTestPipelineGui
    gui = SimpleTestPipelineGui(self.context, test_pline=self.__getTestPipeline())
    gui.run()

  def __getTestPipeline(self):
    test_pline = InotifySimpleTestPipeline(self.context)
    deformation_expression_test = DeformationExpression(self.context)
    deformation_expression_test.definePipeline(test_pline)
    return test_pline

def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()
  MepintaSimpleDemos(context).evaluatePipelineAndPrint()

if __name__ == "__main__":
  test_module()