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
from mepinta.testing.plugins_testing.gui.SimpleTestPipelineGui import SimpleTestPipelineGui
from mepinta.testing.plugins_testing.test_pipeline.InotifySimpleTestPipeline import InotifySimpleTestPipeline

class GUIInotifyTestPipeline(InotifySimpleTestPipeline):
  '''Wraps and mimics a SimpleTestPipeline.
    Extends InotifySimpleTestPipeline adding capabilities of:
    -Receiving inputs events from the GUI and setting properties' values.
    
    It can watch: (inherited from InotifySimpleTestPipeline)
    -Input Files properties.
    -Processor library files (.so.implementation).
    -Test modules.
    
  This is the default test pipeline used by the 'ProcessorPluginTestRunner' class
  with gui enabled.
  '''  
  def blockListeningEvents(self, test_modules=[], timeout=None):
    self.registerTestModules(test_modules)
    if not (len(self._watched_test_modules) or len(self._watched_processors)):
      self.log.warning('Should should at least watch one test module or processor.')
    SimpleTestPipelineGui(self.context, test_pline=self).runWithInotify(self._inotify_mngr)

if __name__ == "__main__":
  pass
