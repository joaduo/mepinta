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

class PluginTestAutoTester(ModuleAutoTesterBase):
  def test(self, gui=True):
    self.context.nodebox_gui = gui
    import __main__
    test_module = __main__
    self.log.debug('Autotested module module %s' % test_module)
    #Since we create a new context config, logic classes must be instanced here
    ProcessorPluginTestRunner(self.context).blockListeningEvents(test_module)

if __name__ == "__main__":
  pass
