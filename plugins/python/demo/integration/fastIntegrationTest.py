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


def getTestModules():
    test_modules = []
#  import plugins_tests.python.processors.actiontree.UndoableGraph.generator.EmptyGraph.EmptyGraph__0001 as testModule
#  test_modules.append(testModule)
    import plugins.python.processors.demov1.Geometry2D.modifier.DeformationExpression.DeformationExpression__0001_test as test_module
    test_modules.append(test_module)
    return test_modules


def fastIntegrationTestPython(context=None, gui=False):
    from mepinta.context.MepintaContext import MepintaContext
    if not context:
        context = MepintaContext()
    from mepinta.testing.plugins_testing.PluginTestAutoTester import PluginTestAutoTester
    test_modules = getTestModules()
    if gui:
        PluginTestAutoTester(context).shallowTest(gui, test_modules[0])
    else:
        for test_module in test_modules:
            PluginTestAutoTester(context).shallowTest(gui, test_module)


def smokeTestModule():
    fastIntegrationTestPython(gui=True)

if __name__ == "__main__":
    smokeTestModule()
