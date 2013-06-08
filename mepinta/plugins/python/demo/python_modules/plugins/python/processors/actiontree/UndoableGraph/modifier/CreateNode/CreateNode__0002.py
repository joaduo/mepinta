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
from mepinta.pipelineview.graph.GraphManager import GraphManager
from mepinta_python_sdk.props import get_prop_value
from plugins.python.processors.actiontree.Graph.modifier.base.GraphTopologyModifierBase import GraphTopologyModifierBase

class manifest(GraphTopologyModifierBase):
  def define(self, inputs, internals, functions, outputs, changeGraphValues, changeGraphTopology):
    pass
#    inputs.context = 'actiontree.Context'
#    inputs.processor = 'actiontree.Processor'
#    inputs.node_name = 'str'
#    outputs.graph = 'actiontree.Graph'
#    functions.onTopologyChange = FunctionProperty()
#
#    functions.onTopologyChange.dpdencies += [inputs.context,
#                                             inputs.processor,]
#    outputs.graph.dpdencies += [functions.onTopologyChange]

def demuxSignal(args):
  '''
  A graph could have topology changed or values changed. Demux this signals and
  call the appropriate functums.
  :param args: Opaque args to be used by the functions in mepinta_python_sdk.props
  '''
  #Get the inputs
  #The graph to demux the signal from
  in_graph = get_prop_value(args, 'inputs', 'graph')
  #Get the functums to be initialized
  changeGraphTopology = get_prop_value(args, 'inputs', 'changeGraphTopology')
  changeGraphValues = get_prop_value(args, 'inputs', 'changeGraphValues')
  #output
  out_graph = get_prop_value(args, 'outputs', 'graph')
  #DemuxSignal
  if in_graph.topology_changed:
    #We have a new topology, then start from this new topology
    out_graph.resetTopology(in_graph)
    #Modify the topology on the new given topology
    changeGraphTopology.function_ptr(changeGraphTopology.args)
  #Set the necessary values
  changeGraphValues.function_ptr(changeGraphValues.args)

def onTopologyChange(args):
  context = get_prop_value(args, 'inputs', 'context')
  processor_name = get_prop_value(args, 'inputs', 'processor')

  graph = get_prop_value(args, 'outputs', 'graph')
  graph_manager = GraphManager(context)

  graph_manager.createNode(graph.pipeline, processor_name)


if __name__ == "__main__":
  from getDefaultContext import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  #PluginManifestAutoTester(getDefaultContext()).test(manifest)#, gui=True)
  PluginManifestAutoTester(getDefaultContext()).test(manifest, gui=False)
