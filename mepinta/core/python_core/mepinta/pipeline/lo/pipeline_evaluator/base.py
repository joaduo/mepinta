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

from mepinta.pipeline.lo.FunctionCaller import FunctionCaller
from mepinta.pipeline.lo.value_manager.PropertyValueManager import PropertyValueManager

# TODO: remove


class PipelineEvaluatorBase(object):

    def __init__(self, context_lo):
        self.context_lo = context_lo
        self.p_value_mngr = PropertyValueManager(context_lo)
        self.func_caller = FunctionCaller()

    def evaluateProp(self, pline, prop_id):
        prop = pline.all_properties[prop_id]
        return prop_id, prop


def shedskin_PipelineEvaluatorBase(context_lo, pline, prop):
    pe = PipelineEvaluatorBase(context_lo)
#  prop_id = 100
#  pline.all_properties[prop_id] = prop
#  pe.eval_function(pline, prop_id, prop)
#  pe.eval(pline, prop_id, True)
#  pe.animate(pline, prop_id)
#  pe.eval_property(pline, prop_id, prop)
    return pe

if __name__ == "__main__":
    pass
