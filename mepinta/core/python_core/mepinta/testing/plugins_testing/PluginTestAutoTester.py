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

#TODO: launch another python with the test
class PluginTestAutoTester(ModuleAutoTesterBase):
  def test(self, test_class, gui=True):
    #self.log.debug(test_class.__module__)
    test_module = self._getClassModule(test_class)
    self.log.debug('Autotested module module %s'%test_module)
    ProcessorPluginTestRunner(self.context).blockListeningEvents(test_module, gui=gui)
        
if __name__ == "__main__":
  pass
