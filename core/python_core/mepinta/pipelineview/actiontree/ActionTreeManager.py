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
from common.abstract.FrameworkBase import FrameworkBase
from mepinta.pipelineview.graph.GraphManager import GraphManager
from mepinta.pipeline.hi.property_manager.PropertyManager import PropertyManager
from mepinta.pipeline.hi.pipeline_evaluator.PipelineEvaluatorFunctum import PipelineEvaluatorFunctum
from mepinta.pipeline.hi.value_manager.ValueManager import ValueManager


class ActionTreeManager(FrameworkBase):

    def __post_init__(self):
        self.graph_mngr = GraphManager()
        self.prop_mngr = PropertyManager()
        self.pline_eval = PipelineEvaluatorFunctum()
        self.val_mngr = ValueManager()

    def getTransitionPath(self, from_action, to_action):
        frm_path, to_path = self._getPathsToCommonNode(from_action, to_action)
        return frm_path + list(reversed(to_path))

    def _getPathsToCommonNode(self, from_action, to_action):
        frm = from_action
        to = to_action
        frm_visited = set()
        to_visited = set()
        frm_path = []
        to_path = []

        # go down to the parents until we reach a common node 
        # or the root of the tree
        while (frm and to and 
               frm not in to_visited and to not in frm_visited):
            # Go up one step
            frm_visited.add(frm)
            frm_path.append(frm)
            frm = frm.parent
            if to not in frm_visited:
                # Go up one step
                to_visited.add(to)
                to_path.append(to)
                to = to.parent
        
        if to in frm_visited:
            # Delete unneeded remaining path (going down)
            del frm_path[frm_path.index(to) + 1:]
        if frm in to_visited:
            # Delete unneeded remaining path (going down)
            del to_path[to_path.index(frm) + 1:]
        return frm_path, to_path

    id_ = 0
    def addAction(self, tree, processor):
        # TODO: create Graph's node
        self.id_ += 1
        return tree.addAction(self.id_)

    def undoAction(self, tree):
        return tree.undoAction()

    def redoAction(self, tree):
        return tree.redoAction()

    def setCurrentAction(self, tree, action):
        path = self.getTransitionPath(tree.current_action, action)
        return path
        # Code below not yet working, we need to add a processor
        # (thus creates a node)
        # Also I need to review how we are copying values in the pipeline
        # since the copying functions are not very well implemented
#        changed = set()
#        for action in path:
#            node = tree.actions_graph.nodes[action.node_id]
#            u_graph = self.val_mngr.getValue(tree.actions_graph.pline, node.outputs.graph)
#            changed.update(u_graph.getTopology().changed_primary)
#        # Update the changed state of the pipeline
#        u_graph.graph.pline.changed_primary.update(changed)

    def setActionPropValue(self, tree, action):
        pass

    def evalTree(self, tree):
        graph = tree.actions_graph.graph
        node = graph.nodes[tree.current_action.node_id]
        self.pline_eval.evaluateProp(graph.pline, node.outputs.graph)
        #self.prop_mngr.
        #self.graph_mngr.
