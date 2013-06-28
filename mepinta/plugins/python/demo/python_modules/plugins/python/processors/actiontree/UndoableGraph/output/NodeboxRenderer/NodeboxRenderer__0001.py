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
from plugins.python.processors.actiontree.UndoableGraph.output.base.UndoableGraphRendererBase import UndoableGraphRendererBase

class manifest(UndoableGraphRendererBase):
  def define(self, inputs, internals, functions, outputs, render):
    internals.temp_data = 'dict'
    render.dpdencies += internals.temp_data

def render(args):
  from mepinta_python_sdk.props import get_prop_value
  from mepinta.testing.plugins_testing.nodebox.NodeBoxSimplePipelineOutput import NodeBoxSimplePipelineOutput
  graph = get_prop_value(args, 'inputs', 'graph')
  temp_data = get_prop_value(args, 'inputs', 'temp_data')
  pline = graph.pline
  data_name = 'NodeBoxSimplePipelineOutput'
  if data_name not in temp_data:
    temp_data[data_name] = NodeBoxSimplePipelineOutput(pline)
  temp_data[data_name].update()

if __name__ == "__main__":
  from getDefaultContext import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  PluginManifestAutoTester(getDefaultContext()).test(manifest)#, gui=True)
