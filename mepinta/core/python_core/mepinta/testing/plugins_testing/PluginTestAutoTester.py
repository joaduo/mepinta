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
from mepinta.testing.plugins_testing.base import ModuleAutoTesterBase, \
  ForkInotifyUtilsBase
from mepinta.testing.plugins_testing.ProcessorPluginTestRunner import ProcessorPluginTestRunner
from mepinta.testing.plugins_testing.test_pipeline.InotifySimpleTestPipeline import InotifySimpleTestPipeline

class PluginTestAutoTester(ModuleAutoTesterBase):
  def __post_init__(self):
    self.__fork_inotify_utils = ForkInotifyUtilsBase(self.context)

  def __getTestModule(self):
    import __main__
    return __main__

  def __setGui(self, gui):
    self.context.nodebox_gui = gui

  def deepTest(self, gui=True):
    self.test(gui)

  def test(self, gui=True): #TODO: rename to deepTest
    self.__setGui(gui)
    #Since we changed the context config, logic classes must be instanced here
    ProcessorPluginTestRunner(self.context).blockListeningEvents(self.__getTestModule())

  def __createPipeline(self):
    test_module = self.__getTestModule()
    test_instance = self.__fork_inotify_utils._getTestInstance(test_module)
    test_pline = InotifySimpleTestPipeline(self.context)
    test_instance.definePipeline(test_pline)
    return test_pline

  def simpleTest(self, gui=True):
    self.__setGui(gui)
    test_pline = self.__createPipeline()
    test_pline.blockListeningEvents(self.__getTestModule())

  def shallowTest(self, gui=True):
    self.__setGui(gui)
    test_pline = self.__createPipeline()
    if gui:
      from mepinta.testing.plugins_testing.gui.SimpleTestPipelineGui import SimpleTestPipelineGui
      SimpleTestPipelineGui(self.context, test_pline=test_pline).run()
    else:
      test_instance = self.__fork_inotify_utils._getTestInstance(self.__getTestModule())
      test_instance.stressPipeline(test_pline, time=0)
      test_pline.evaluateProp()

  def smokeTest(self, gui=True):
    self.__setGui(gui)
    test_pline = self.__createPipeline()
    if gui:
      from mepinta.testing.plugins_testing.nodebox.NodeBoxSimplePipelineOutput import NodeBoxSimplePipelineOutput
      NodeBoxSimplePipelineOutput(test_pline.getPipeline()).run()

  def visualizeXdot(self, gui=True):
    raise NotImplementedError()

if __name__ == "__main__":
  pass
