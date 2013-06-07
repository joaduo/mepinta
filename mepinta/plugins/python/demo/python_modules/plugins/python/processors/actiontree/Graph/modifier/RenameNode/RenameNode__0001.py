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

#from mepinta.plugins_manifest import PluginManifestBase, FunctionProperty
#from mepinta.pipelineview.graph.GraphManager import GraphManager
from mepinta_python_sdk.props import get_prop_value, replace_out_prop_value
#from plugins.python.processors.actiontree.Graph.modifier.base.GraphValueModifierBase import GraphValueModifierBase
from plugins.python.processors.actiontree.Graph.modifier.base.GraphTopologyModifierBase import GraphTopologyModifierBase
#from mepinta.pipelineview.graph.data_model import Graph

class RenameNode(GraphTopologyModifierBase):
  #def define(self, inputs, internals, functions, outputs, changeGraphValues):
  def define(self, inputs, internals, functions, outputs, changeGraphValues, changeGraphTopology):
    inputs.node_id = 'int'
    inputs.new_name = 'str'

    changeGraphValues.dpdencies += inputs.node_id, inputs.new_name

manifest = RenameNode

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
  #resetTopology = get_prop_value(args, 'inputs', 'resetTopology')
  #output
  out_graph = get_prop_value(args, 'outputs', 'graph')
  #DemuxSignal
  if in_graph.topology_changed:
    #We have a new topology, then start from this new topology
    #resetTopology.function_ptr(resetTopology.args)
    #Modify the topology on the new given topology
    changeGraphTopology.function_ptr(changeGraphTopology.args)
  #Set the necessary values
  changeGraphValues.function_ptr(changeGraphValues.args)

def setTopologyIdOnce(args):
  '''
  The first time this processor is ran, we need to set the topology id for later use
  :param args: Opaque args to be used by the functions in mepinta_python_sdk.props
  '''
  graph = get_prop_value(args, 'inputs', 'graph')
  topology_id = get_prop_value(args, 'topology_id', 'graph')
  if topology_id == 0:
    topology_id = graph.pline.getCurrentTopologyId()
    replace_out_prop_value(args, 'topology_ud', topology_id)


if __name__ == "__main__":
  from getDefaultContext import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  #PluginManifestAutoTester(getDefaultContext()).test(manifest)#, gui=True)
  PluginManifestAutoTester(getDefaultContext()).visualizeXdot(manifest)
