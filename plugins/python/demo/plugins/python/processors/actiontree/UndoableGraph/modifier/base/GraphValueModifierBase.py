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
from mepinta.plugins_manifest import ProcessorManifestBase, FunctionProperty, \
    directed


class GraphValueModifierBase(ProcessorManifestBase):

    def _superClassDefine(self, inputs, internals, functions, outputs):
        # inputs
        inputs.graph = 'actiontree.UndoableGraph'
        inputs.context_name = 'str'
        # outputs
        outputs.graph = 'actiontree.UndoableGraph'
        # functions
        functions.changeGraphValues = FunctionProperty()
        # Set dependencies
        # Set modifier related topology ids
        functions.changeGraphValues.dpdencies += (inputs.graph,
                                                  inputs.context_name,)
        outputs.graph.dpdencies += functions.changeGraphValues

        self.nonCached(outputs.graph)

        return functions.changeGraphValues

    def define(self, inputs, internals, functions, outputs, changeGraphValues):
        '''
          Implement this method on children classes.
          Example:
            inputs.node_name = 'str'
            changeGraphValues.dpdencies += [inputs.node_name]
        '''
        pass

if __name__ == "__main__":
    pass
