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

def fastIntegrationTest(context=None):
  from getDefaultContext import getDefaultContext
  if not context:
    context = getDefaultContext()
  if context.backend_name == 'python':
    from plugins_tests.integration.fastIntegrationTest import fastIntegrationTestPython
    fastIntegrationTestPython(context)
  else:
    raise NotImplementedError()

def test_module():
  fastIntegrationTest()

if __name__ == "__main__":
  test_module()
