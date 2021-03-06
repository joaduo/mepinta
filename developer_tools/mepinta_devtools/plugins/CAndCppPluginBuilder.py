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


class CAndCppPluginBuilder(FrameworkBase):

    '''
    Responsibilities:
      - Configure, build (and deploy) a c_and_cpp plugin.
      - Will make use of the waf framework to do the task. (or Cmake or any other system in the future)
    '''

    def createBuildScript(self, plugin_manifest):
        pass

    def buildPlugin(self, plugin_manifest, target=None):
        pass

    def cleanPlugin(self, plugin_manifest):
        pass
#  def


def testModule():
    from getDefaultContext import getDefaultContext
    context = getDefaultContext()

if __name__ == "__main__":
    testModule()
