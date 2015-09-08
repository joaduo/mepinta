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
from mepinta.pipeline.hi.pipeline_evaluator.PipelineEvaluatorFunctum import PipelineEvaluatorFunctum
from mepinta.pipelineview.actiontree.undoable_graph.data_model import UndoableGraph


from mepinta.plugins_manifest import DataTypeManifestBase


class manifest(DataTypeManifestBase):
    pass


def new():
    return UndoableGraph()


def copy(u_graph):
    raise NotImplementedError(
        'You cannot copy an UndoableGraph. Is a non_cached forced.')


def delete(u_graph):
    pass


#TODO review copyTo, something is wrong here?
def copyTo(to_graph, from_graph):
#    # Make sure to propagate changes (avoid inconsistencies) (no need?)
#    PipelineEvaluatorFunctum().propagateChanges(from_graph.pline)
    # pass the common data between undoable graphs
    to_graph.setGraph(from_graph.graph)
#    # We start a topology change set, so we haven't done anything yet
#    # TODO: review this statement
#    to_graph.topology_changed = False
    # return the copy
    return to_graph

# def checkRepr(u_graph):
#  return u_graph.checkRepr()
