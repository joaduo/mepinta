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

from mepinta.plugins_manifest import PluginManifestBase, FunctionProperty
from mepinta.pipelineview.actiontree.undoable_graph.UndoableGraphManager import UndoableGraphManager

class manifest(PluginManifestBase):
  def define(self, inputs, internals, functions, outputs):
    inputs.context_name = 'str'
    outputs.graph = 'actiontree.UndoableGraph'
    functions.changeGraphTopology = FunctionProperty()

    functions.changeGraphTopology.dpdencies += inputs.context_name
    outputs.graph.dpdencies += functions.changeGraphTopology

def changeGraphTopology(args):
  from mepinta_python_sdk.props import get_prop_value
  from mepinta.context.getMepintaContext import getMepintaContext

  context_name = get_prop_value(args, 'inputs', 'context_name')
  out_graph = get_prop_value(args, 'outputs', 'graph')
  context = getMepintaContext(context_name)
  UndoableGraphManager(context).initGraph(out_graph)

if __name__ == "__main__":
  from getDefaultContext import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  PluginManifestAutoTester(getDefaultContext()).test(manifest)#, gui=True)
