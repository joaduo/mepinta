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
import shlex
import subprocess

class CommandRunner(FrameworkBase):
  def run(self, cmd):
    process_open = subprocess.Popen(shlex.split(cmd), stderr=subprocess.PIPE, stdout=subprocess.PIPE)
    stdout, stdin = process_open.stdout.read(), process_open.stderr.read()
    return stdout, stdin

def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()
  print CommandRunner(context).run('ls -alh')

if __name__ == "__main__":
  test_module()
