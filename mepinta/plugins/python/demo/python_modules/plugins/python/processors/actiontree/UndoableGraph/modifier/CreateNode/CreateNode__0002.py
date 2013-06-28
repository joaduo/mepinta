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
from plugins.python.processors.actiontree.UndoableGraph.modifier.base.GraphTopologyModifierBase import GraphTopologyModifierBase

class manifest(GraphTopologyModifierBase):
  def define(self, inputs, internals, functions, outputs, changeGraphValues, changeGraphTopology):
    inputs.processor_name = 'actiontree.Processor'
    inputs.node_name = 'str'
    #Topology changes dependencies
    changeGraphTopology.dpdencies += inputs.processor_name
    #Values changes dependencies
    changeGraphValues.dpdencies += inputs.node_name

def demuxSignal(args):
  '''
  A graph could have topology changed or values changed. Demux this signals and
  call the appropriate functums.
  :param args: Opaque args to be used by the functions in mepinta_python_sdk.props
  '''
  from mepinta_python_sdk.props import getPropValue
  #Get the inputs
  #The graph to demux the signal from
  in_graph = getPropValue(args, 'inputs', 'graph')
  #Get the functums to be initialized
  changeGraphTopology = getPropValue(args, 'inputs', 'changeGraphTopology')
  changeGraphValues = getPropValue(args, 'inputs', 'changeGraphValues')
  #output
  out_graph = getPropValue(args, 'outputs', 'graph')
  #DemuxSignal
  if in_graph.topologyChanged:
    #We have a new topology, then start from this new topology
    out_graph.resetTopology(in_graph)
    #Modify the topology on the new given topology
    changeGraphTopology.function_ptr(changeGraphTopology.args)
  #Set the necessary values
  changeGraphValues.function_ptr(changeGraphValues.args)

def changeGraphValues(args):
  from mepinta.pipelineview.actiontree.undoable_graph.UndoableGraphManager import UndoableGraphManager
  from mepinta.context.MepintaContext import MepintaContext
  from mepinta_python_sdk.props import getPropValue
  context_name = getPropValue(args, 'inputs', 'context_name')
  node_name = getPropValue(args, 'inputs', 'node_name')
  graph = getPropValue(args, 'outputs', 'graph')
  context = MepintaContext(context_name)

  if len(graph.createdNodes) == 1:
    node = graph.createdNodes[0]
    node.name = node_name
  else:
    context.log.e('There shouldn\'t be more than one node created by this plugin. Nodes: %r.' % graph.createdNodes)

def changeGraphTopology(args):
  from mepinta.pipelineview.actiontree.undoable_graph.UndoableGraphManager import UndoableGraphManager
  from mepinta.context.MepintaContext import MepintaContext
  from mepinta_python_sdk.props import getPropValue
  context_name = getPropValue(args, 'inputs', 'context_name')
  processor_name = getPropValue(args, 'inputs', 'processor_name')
  graph = getPropValue(args, 'outputs', 'graph')
  graph_manager = UndoableGraphManager(MepintaContext(context_name))

  graph_manager.createNode(graph, processor_name)

def testModule():
  from getDefaultContext import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  #PluginManifestAutoTester(getDefaultContext()).test(manifest)#, gui=True)
  PluginManifestAutoTester(getDefaultContext()).visualizeXdot(manifest)#, gui=True)
  #PluginManifestAutoTester(getDefaultContext()).test(manifest, gui=False)

if __name__ == "__main__":
  testModule()
  #import ftest
