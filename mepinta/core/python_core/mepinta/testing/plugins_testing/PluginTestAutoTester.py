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
from mepinta.testing.plugins_testing.base import ModuleAutoTesterBase
from mepinta.testing.plugins_testing.ProcessorPluginTestRunner import ProcessorPluginTestRunner
from mepinta.testing.plugins_testing.ModuleAutoTesterUtil import ModuleAutoTesterUtil

class PluginTestAutoTester(ModuleAutoTesterBase):
  def __post_init__(self):
    self.processor_plugin_testrunner = ProcessorPluginTestRunner(self.context)
    self.module_autotester_util = ModuleAutoTesterUtil(self.context)

  def test(self, gui=True):
    import __main__
    test_module = __main__
    self.log.debug('Autotested module module %s' % test_module)
    self.processor_plugin_testrunner.blockListeningEvents(test_module, gui=gui)

if __name__ == "__main__":
  pass
