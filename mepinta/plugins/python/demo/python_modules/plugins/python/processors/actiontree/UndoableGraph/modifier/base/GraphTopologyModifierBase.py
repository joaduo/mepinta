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

from mepinta.plugins_manifest import PluginManifestBase, FunctionProperty, \
  directed

class GraphTopologyModifierBase(PluginManifestBase):
  def _superClassDefine(self, inputs, internals, functions, outputs):
    #inputs
    inputs.graph = 'actiontree.UndoableGraph'
    inputs.context_name = 'str'
    #outputs
    outputs.graph = 'actiontree.UndoableGraph'
    #functions
    functions.demuxSignal = FunctionProperty()
    internals.changeGraphTopology = 'functum'
    internals.changeGraphValues = 'functum'

    #Set dependencies
    #Set signal demux dependencies
    functions.demuxSignal.dpdencies += [inputs.graph,
                                        directed('>', internals.changeGraphTopology),
                                        directed('>', internals.changeGraphValues), ]
    #Set modifier related topology ids
    internals.changeGraphTopology.dpdencies += [inputs.graph,
                                                inputs.context_name, ]
    internals.changeGraphValues.dpdencies += [internals.changeGraphTopology,
                                              inputs.graph,
                                              inputs.context_name, ]
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
