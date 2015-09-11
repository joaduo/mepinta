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
from mepinta.pipelineview.graph.data_model import Graph
from mepinta.pipeline.hi.pipeline_data.data_model import Pipeline
from common.abstract.FrameworkObject import FrameworkObject
from mepinta.pipeline.lo.constants import NULL_UID
from functools import wraps
import json


class Action(object):

    def __init__(self, parent, node_id):
        # The parent action
        self.parent = parent
        # Store node_id associated to this action
        self.node_id = node_id
        # All the children of these nodes
        self.children = set()

    def newChild(self, node_id):
        '''
        This method adds a Child actions to this action.
        This could mean:
          -growing a branch
          -forking into a new branch (if this action already has a child)
        :param node_id:
        '''
        node_id = Action(self, node_id)
        self.children.add(node_id)
        return node_id

    def buildTree(self, string=False):
        # Build tree (dictionaries) with the ActionTree hierarchy
        if self.children:
            branch = {}
            for c in self.children:
                k = str(c) if string else c
                branch[k] = c.buildTree(string)
            return branch

    def __str__(self):
        return '%s(%s)'  % (self.__class__.__name__, self.node_id)

    def __repr__(self):
        return str(self)


def log_method(method):
    '''
    Decorates methods
    :param method:
    '''
    @wraps(method)
    def wraper(self, *args, **kwargs):
        self.steps_log.append(method.__name__)
        return method(self, *args, **kwargs)
    return wraper


class ActionTree(FrameworkObject):

    def __init__(self):
        self.actions = {}
        # Root Action has no parent -> None
        self.root_action = Action(parent=None, node_id=NULL_UID)
        # The current action the user is positioned in
        self.current_action = self.root_action
        # Mepinta's Graph wrapped by this tree (used to evaluate values
        # in this tree
        self.actions_graph = Graph(Pipeline())
        # The latest path of actions done (for undo/redo purposes) 
        self.actions_path = [self.current_action]
        # actions logging
        self.steps_log = []

    def getGraphNode(self, node_id=None):
        node_id = node_id if node_id else self.current_action.node_id 
        # We could return None if we are in the root Action
        return self.actions_graph.nodes.get(node_id)

    @log_method
    def addAction(self, node_id):
        # nice alias
        path = self.actions_path
        # Remove any non-redoable action
        del path[path.index(self.current_action) + 1:]
        # Create Action with actions_graph's node id
        self.current_action = self.current_action.newChild(node_id)
        # Save id:action table
        self.actions[node_id] = self.current_action
        # Keep track for undo/redo
        path.append(self.current_action)
        return self.current_action

    @log_method
    def undoAction(self):
        # Make sure we have something to undo to
        if self.current_action != self.root_action:
            self.current_action = self.current_action.parent
            return self.current_action
        return None

    @log_method
    def redoAction(self):
        path = self.actions_path
        old_cur = self.current_action
        # Make sure we have something to redo to
        if path[-1] != old_cur:
            self.current_action = path[path.index(old_cur) + 1]
            assert self.current_action in old_cur.children
            return self.current_action
        # TODO: raise exception (Redo exception?)??
        return None

    def buildTree(self, string=False):
        return self.root_action.buildTree(string)
    
    def __str__(self):
        tree = self.buildTree(string=True)
        tree = json.dumps(tree, indent=True)
        latest = self.steps_log[-1] if self.steps_log else None
        tree = (('current: %s\nlatest step: %s\n' % 
                 (self.current_action, latest)) + tree)
        return tree



def testModule():
    from mepinta.context.MepintaContext import MepintaContext
    ctx = MepintaContext()
    ctx.log(ActionTree())


if __name__ == "__main__":
    testModule()
