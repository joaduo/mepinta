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

def fastIntegrationTestPython(context=None):
  from getDefaultContext import getDefaultContext
  if not context:
    context = getDefaultContext()
  from mepinta.testing.plugins_testing.PluginTestAutoTester import PluginTestAutoTester
  import plugins_tests.python.processors.actiontree.UndoableGraph.generator.EmptyGraph.EmptyGraph__0001 as test_module
  #PluginTestAutoTester(context).shallowTest(gui=False, test_module=test_module)
  PluginTestAutoTester(context).shallowTest(gui=True, test_module=test_module)

def test_module():
  fastIntegrationTestPython()

if __name__ == "__main__":
  test_module()
