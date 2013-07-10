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
    ''' Mepinta GUI demo. Shows Pipeline in as a dot graph. (you need the xdot command in the path "apt-get install xdot" in ubuntu/debian)'''
    test_pline = self.__getTestPipeline()
    graphviz_translator = PipelineGraphvizTranslator(self.context)
    graphviz_str = graphviz_translator.translate(test_pline.getPipeline())
    path = './pipeline.dot'
    FileManager(self.context).saveTextFile(path, graphviz_str, overwrite=True)
    try:
      CommandRunner(self.context).run('xdot %s' % path)
    except OSError as e:
      msg = 'The xdot command may not be in the command path. OSError: %s' % e
      self.log.e(msg)
    os.remove(path)

  def evaluatePipelineAndPrint(self):
    ''' Simplest Mepinta Pipeline demo. Outputs to console.'''
    test_pline = self.__getTestPipeline()
    test_pline.evaluateProp()

  def nodeboxInteractivePipeline(self):
    ''' Mepinta interactive GUI demo. Shows Pipeline and lets the user change properties values. (you need nodebox-gl installed in your python path to run this http://www.cityinabottle.org/nodebox/).'''
    try:
      import nodebox
    except:
      self.log.error('\n You have not nodebox gl installed or is not in the PYTHONPATH. Check the mepinta INSTALL file for further instructions. \n')
      return
    from mepinta.testing.plugins_testing.gui.SimpleTestPipelineGui import SimpleTestPipelineGui
    self.context.nodebox_gui = True
    gui = SimpleTestPipelineGui(self.context, test_pline=self.__getTestPipeline())
    try:
      gui.run()
    except Exception as e:
      self.log.error('Exception %r ocurred.' % e)
      self.log.error('\n This may mean that you have the wrong nodebox gl library installed. Check the mepinta INSTALL file for further instructions. \n')

  def __getTestPipeline(self):
    test_pline = InotifySimpleTestPipeline(self.context)
    deformation_expression_test = DeformationExpression(self.context)
    deformation_expression_test.definePipeline(test_pline)
    return test_pline

def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()
  MepintaSimpleDemos(context).evaluatePipelineAndPrint()

if __name__ == "__main__":
  testModule()
