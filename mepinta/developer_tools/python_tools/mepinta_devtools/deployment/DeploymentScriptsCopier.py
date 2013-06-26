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
import shutil
import os
from common.path import joinPath

class DeploymentScriptsCopier(FrameworkBase):
  def _getSrcPath(self):
    return joinPath(os.path.dirname(os.path.realpath(__file__)), 'scripts_repository')

  def copyScriptsTo(self, deployment_path):
    scripts = ['demo', 'tests']
    src_path = self._getSrcPath()
    for s in scripts:
      file_name = 'mepinta_%s.py' % s
      self.log.d('Copying %r to %r' % (joinPath(src_path, file_name), joinPath(deployment_path, file_name)))
      shutil.copy(joinPath(src_path, file_name), joinPath(deployment_path, file_name))

def test_module():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  test_module()
