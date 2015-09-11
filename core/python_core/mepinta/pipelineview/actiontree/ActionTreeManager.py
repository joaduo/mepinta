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
from mepinta.plugins_manager.PluginsManager import PluginsManager
from mepinta.pipelineview.actiontree.undoable_graph.UndoableGraphManager import UndoableGraphManager
from mepinta.pipeline.hi.value_manager.UntypedValueManager import UntypedValueManager


class ActionTreeManager(FrameworkBase):

    def __post_init__(self):
        self.graph_mngr = GraphManager()
        self.prop_mngr = PropertyManager()
        self.pline_eval = PipelineEvaluatorFunctum()
        self.val_mngr = UntypedValueManager()
        self.plugins_manager = PluginsManager()
        self.graph_mngr = GraphManager()
        self._processors_metadata = dict() # processor: processor_metadata

    def getTransitionPath(self, from_action, to_action):
        # smaller alias
        frm = from_action
        to = to_action
        # Paths to common node (actions in order)
        frm_path = []
        to_path = []
        # Sets containing actions in the path to common node
        frm_visited = set()
        to_visited = set()
        # go down to the parents until we reach a common node 
        # or the root of the tree
        while (frm and to and
               frm not in to_visited and
               to not in frm_visited):
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
            joint = to
            # Delete unneeded remaining path (going down)
            del frm_path[frm_path.index(to):]
        if frm in to_visited:
            joint = frm
            # Delete unneeded remaining path (going down)
            del to_path[to_path.index(frm):]
        # We want to path from -> to, so we need to reverse to_path and
        # add it (both were pointing to a common node in upper levels)
        return frm_path, joint, list(reversed(to_path))

    def addAction(self, tree, processor, eval_=True):
        if processor not in self._processors_metadata:
            self._processors_metadata[processor] = self.plugins_manager.loadProcessor(
                processor, reload_=True)
        # get processor metadata
        processor = self._processors_metadata[processor]
        # create a Graph's node in the wrapped actions_graph
        node = self.graph_mngr.createNode(tree.actions_graph, processor)
        # We want to connect with parent node
        self._connectWithParent(tree, node)
        # Sync values
        if eval_:
            self._eval(tree, node)
        # Add action and return current action object
        return tree.addAction(node.node_id)

    def eval(self, tree):
        self._eval(tree, tree.getGraphNode())

    def _eval(self, tree, node):
        self.pline_eval.evaluateProp(tree.actions_graph.pline, node.outputs.graph)

    def _connectWithParent(self, tree, action_node):
        # Get current actions_graph's node
        parent = tree.getGraphNode()
        # If there is a parent node, then try to autoconnect
        if parent != None:
            self.graph_mngr.autoConnect(tree.actions_graph, action_node, parent)

    def undoAction(self, tree):
        return tree.undoAction()

    def redoAction(self, tree):
        return tree.redoAction()

    def setCurrentAction(self, tree, action):
        if tree.current_action == action:
            return None, None, None
        frm, joint, to = self.getTransitionPath(tree.current_action, action)
        # Gather all changed props in the underlying undoable actions_graph
        changed_props = set()
        mngr = UndoableGraphManager()
        def common(action):
            node = tree.actions_graph.nodes[action.node_id]
            u_graph = self.val_mngr.getValue(tree.actions_graph.pline, node.outputs.graph)
            changed_props.update(u_graph.getTopology().changed_primary)
            return u_graph
        for action in frm:
            mngr.undoValuesChanges(common(action))
        # No need to undo/redo
        action = joint
        u_graph = common(action)
        for action in to:
            # We need to catch the last u_graph
            u_graph = common(action)
            mngr.redoValuesChanges(u_graph)
        # Update the changed_props state of the pipeline
        u_graph.setCurrentTopologyId()
        u_graph.graph.pline.changed_primary.update(changed_props)
        tree.current_action = action
        path = tree.actions_path
        self.context.log.d('Undoing %s', path[path.index(joint)+1:])
        del path[path.index(joint)+1:]
        self.context.log.d('Redoing %s', to)
        path += to
        return frm, joint, to

    def setActionPropValue(self, tree, action):
        pass

