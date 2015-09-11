'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

This file is part of Mepinta under GPL 3
'''
import unittest
from mepinta.pipelineview.actiontree.data_model import ActionTree
from mepinta.pipelineview.actiontree.ActionTreeManager import ActionTreeManager
from pprint import pprint, pformat
from mepinta.context.MepintaContext import MepintaContext
from pipeline_backend.logging.logging import LOG_DEBUG


class Test(unittest.TestCase):

    def print_verify(self, answers, tree):
        print  '='*8
        print tree
        count = max(answers.keys()) if answers else 1 
        answers[count + 1] = tree.buildTree(string=True)
        
    def test_adding_actions(self):
        import plugins.python.processors.actiontree.UndoableGraph.generator.EmptyGraph as EmptyGraph
        answers = {}
        tree = ActionTree()
        mngr = ActionTreeManager()
        mngr.addAction(tree, EmptyGraph)
        print tree.actions_graph.pline.getTopology()

    def test_tree(self):
        answers = {}
        tree = ActionTree()
        mngr = ActionTreeManager()
        self.print_verify(answers, tree)
        mngr.undoAction(tree)
        self.print_verify(answers, tree)
        mngr.redoAction(tree)
        self.print_verify(answers, tree)
        mngr.addAction(tree, 'actiontree.UndoableGraph.generator.EmptyGraph')
        self.print_verify(answers, tree)
        mngr.addAction(tree, 'actiontree.UndoableGraph.generator.EmptyGraph')
        self.print_verify(answers, tree)
        mngr.addAction(tree, 'actiontree.UndoableGraph.generator.EmptyGraph')
        act3 = tree.current_action
        self.print_verify(answers, tree)
        mngr.undoAction(tree)
        self.print_verify(answers, tree)
        mngr.redoAction(tree)
        self.print_verify(answers, tree)
        mngr.undoAction(tree)
        self.print_verify(answers, tree)
        mngr.addAction(tree, 'actiontree.UndoableGraph.generator.EmptyGraph')
        act4 = tree.current_action
        self.print_verify(answers, tree)
        print mngr.setCurrentAction(tree, act3)
        mngr.addAction(tree, 'actiontree.UndoableGraph.generator.EmptyGraph')
        self.print_verify(answers, tree)
#        print mngr.setCurrentAction(tree, act3)
        mngr.addAction(tree, 'actiontree.UndoableGraph.generator.EmptyGraph')
        self.print_verify(answers, tree)
#        print mngr.setCurrentAction(tree, act3)
        mngr.addAction(tree, 'actiontree.UndoableGraph.generator.EmptyGraph')
        self.print_verify(answers, tree)
        print mngr.setCurrentAction(tree, act4)
        mngr.eval(tree)


if __name__ == "__main__":
    MepintaContext('python', log_level=LOG_DEBUG)
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
