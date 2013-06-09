# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

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
from plugins.python.processors.actiontree.UndoableGraph.output.base.UndoableGraphRendererBase import UndoableGraphRendererBase

class manifest(UndoableGraphRendererBase):
  pass

from mepinta_python_sdk.props import get_prop_value
def render(args):
  from pipeline_backend.logging.logging import log_info
  #Inputs
  graph = get_prop_value(args, 'inputs', 'graph')
  log_info(str(graph))

if __name__ == "__main__":
  from getDefaultContext import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  context = getDefaultContext()
  PluginManifestAutoTester(context=context).test(manifest)