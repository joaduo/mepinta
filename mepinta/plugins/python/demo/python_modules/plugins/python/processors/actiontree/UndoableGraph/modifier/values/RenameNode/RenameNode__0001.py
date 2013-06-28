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

from plugins.python.processors.actiontree.UndoableGraph.modifier.base.GraphValueModifierBase import GraphValueModifierBase

class manifest(GraphValueModifierBase):
  def define(self, inputs, internals, functions, outputs, changeGraphValues):
    inputs.node_id = 'int'
    inputs.node_name = 'str'

    changeGraphValues.dpdencies += (inputs.node_id, inputs.newName)

def changeGraphValues(args):
  from mepinta.pipelineview.actiontree.undoable_graph.UndoableGraphManager import UndoableGraphManager
  from mepinta.context.MepintaContext import MepintaContext
  from mepinta_python_sdk.props import getPropValue
  context_name = getPropValue(args, 'inputs', 'context_name')
  node_id = getPropValue(args, 'inputs', 'node_id')
  node_name = getPropValue(args, 'inputs', 'node_name')
  graph = getPropValue(args, 'outputs', 'graph')
  graph_manager = UndoableGraphManager(MepintaContext(context_name))
  node = graph_manager.getNodeById(graph, node_id)
  node.name = node_name

if __name__ == "__main__":
  from getDefaultContext import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  #PluginManifestAutoTester(getDefaultContext()).test(manifest)#, gui=True)
  PluginManifestAutoTester(getDefaultContext()).visualizeXdot(manifest)
