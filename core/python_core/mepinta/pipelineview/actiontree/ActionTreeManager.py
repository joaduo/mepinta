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


class ActionTreeManager(FrameworkBase):

    def __post_init__(self):
        self.graph_mngr = GraphManager()
        self.prop_mngr = PropertyManager()
        self.pline_eval = PipelineEvaluatorFunctum()

    def getTransitionPath(self, from_action, to_action):
        frm_path, to_path = self._getPathsToCommonNode(to_action, from_action)
        return frm_path + list(reversed(to_path))

    def _getPathsToCommonNode(self, from_action, to_action):
        frm = from_action
        to = to_action
        frm_visited = set()
        to_visited = set()
        frm_path = []
        to_path = []

        # go up to the parents until we reach a common node or the root of the
        # tree
        while frm.parent != None and \
            to.parent != None and \
            frm not in to_visited and \
            to not in frm_visited:
            frm_visited.add(frm)
            to_visited.add(to)
            frm_path.append(frm)
            to_path.append(to)
            frm = frm.parent
            to = to.parent

        if frm.parent == None:  # frm_path reached the root
            to = self._keepGoing(to, to_path, frm_visited)
            # Remove path to the root and keep the to node
            del frm_path[frm_path.index(to) + 1:]
        elif to.parent == None:  # to_path reached the root
            frm = self._keepGoing(frm, frm_path, to_visited)
            # Remove path to the root and keep the frm node
            del to_path[to_path.index(frm) + 1:]
        elif to in frm_visited and to in to_visited:
            # equivalent to "if frm in to_visited and frm in frm_visited:"
            # Both reached the same node at the same time.
            # delete the last node in common with frm_path (means to=frm)
            to_path.pop()
        elif to in frm_visited:  # but frm is not in frm_visited
            # to is on fmr_path, but fmr is not in to_path
            # remove tail to the root and keep the to node
            del frm_path[frm_path.index(to) + 1:]
        elif frm in to_visited:  # but to is not in to_visited
            # frm is on to_path, but to is not in frm_path
            # remove tail to the root and keep the frm node
            del to_path[to_path.index(frm) + 1:]
        return frm_path, to_path

    def _keepGoing(self, node, node_path, visited_set):
        while node.parent != None and node not in visited_set:
            node_path.append(node)
            node = node.parent
        if node.parent == None:
            raise RuntimeError(
                'To and From node shouldn\'t have None as common node')
        return node

#    def initTree(self, tree):
#        pass

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
        pass

    def setActionPropValue(self, tree, action):
        pass

    def evalTree(self, tree):
        graph = tree.actions_graph.graph
        node = graph.nodes[tree.current_action.node_id]
        self.pline_eval.evaluateProp(graph.pline, node.outputs.graph)
        #self.prop_mngr.
        #self.graph_mngr.
