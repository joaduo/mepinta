'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

This file is part of Mepinta under GPL 3
'''
import unittest
from mepinta.pipelineview.actiontree.data_model import ActionTree
from mepinta.pipelineview.actiontree.ActionTreeManager import ActionTreeManager
from pprint import pprint, pformat


class Test(unittest.TestCase):

    def print_verify(self, answers, tree):
        print  '='*8
        print tree.buildTree(string=True)
        count = max(answers.keys()) if answers else 1 
        answers[count + 1] = tree.buildTree(string=True)

    def test_tree(self):
        answers = {}
        tree = ActionTree()
        mngr = ActionTreeManager()
        self.print_verify(answers, tree)
        mngr.undoAction(tree)
        self.print_verify(answers, tree)
        mngr.redoAction(tree)
        self.print_verify(answers, tree)
        mngr.addAction(tree, 'act1')
        self.print_verify(answers, tree)
        mngr.addAction(tree, 'act2')
        self.print_verify(answers, tree)
        mngr.addAction(tree, 'act3')
        self.print_verify(answers, tree)
        mngr.undoAction(tree)
        self.print_verify(answers, tree)
        mngr.redoAction(tree)
        self.print_verify(answers, tree)
        mngr.undoAction(tree)
        self.print_verify(answers, tree)
        mngr.addAction(tree, 'act4')
        self.print_verify(answers, tree)
        


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
