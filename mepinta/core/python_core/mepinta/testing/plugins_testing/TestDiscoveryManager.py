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
from unittest import TestLoader
from unittest.runner import TextTestRunner
from common.abstract.FrameworkObject import FrameworkObject

class TestDiscoveryManager(FrameworkObject): #Cannot be FrameworkBase because contexts are init in tests
  def __getPluginsTestDir(self):
    import plugins_tests.python as package
    return package.__path__[0]
  def runAllTests(self):
    test_suite = TestLoader().discover(start_dir=self.__getPluginsTestDir(), pattern='*.py', top_level_dir=self.__getPluginsTestDir())
    TextTestRunner().run(test_suite)


def testModule():
  TestDiscoveryManager().runAllTests()

if __name__ == "__main__":
  testModule()
