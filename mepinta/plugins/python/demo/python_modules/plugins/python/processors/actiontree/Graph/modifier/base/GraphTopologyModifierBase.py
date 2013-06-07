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

from mepinta.plugins_manifest import PluginManifestBase, DataProperty, FunctionProperty, \
  directed, Functum

class GraphTopologyModifierBase(PluginManifestBase):
  def _superClassDefine(self, inputs, internals, functions, outputs):
    #inputs
    inputs.graph = 'actiontree.Graph'
    #internals
    internals.topology_id = 'int' #need to know which topo id we are working on
    internals.created_nodes = 'str'#'list'
    #outputs
    outputs.graph = 'actiontree.Graph'
    #functions
    functions.setTopologyIdOnce = FunctionProperty()
    functions.demuxSignal = FunctionProperty()
    internals.resetTopology = 'str'
    internals.changeGraphTopology = 'str'#Functum()
    internals.changeGraphValues = 'str'#Functum()

    #Set dependencies
    #Set toplogy id related dependencies
    internals.topology_id.dpdencies += functions.setTopologyIdOnce
    functions.setTopologyIdOnce.dpdencies += directed('>', inputs.graph)
    #Set signal demux dependencies
    functions.demuxSignal.dpdencies += [inputs.graph,
                                        internals.topology_id,
                                        directed('>', internals.resetTopology),
                                        directed('>', internals.changeGraphTopology),
                                        directed('>', internals.changeGraphValues), ]
    internals.resetTopology.dpdencies += [inputs.graph,
                                          internals.topology_id, ]
    #Set modifier related topology ids
    internals.changeGraphTopology.dpdencies += [inputs.graph,
                                                internals.topology_id,
                                                internals.created_nodes, ]
    internals.changeGraphValues.dpdencies += [internals.changeGraphTopology,
                                              inputs.graph,
                                              internals.topology_id]
    outputs.graph.dpdencies += functions.demuxSignal

    self.nonCached(outputs.graph)

    return internals.changeGraphValues, internals.changeGraphTopology
  def define(self, inputs, internals, functions, outputs, changeGraphValues, changeGraphTopology):
    '''
      Implement this method on children classes.
      Example:
        inputs.node_name = 'str'
        changeGraphTopology.dpdencies += [inputs.node_name]
    '''
    pass


if __name__ == "__main__":
  pass
