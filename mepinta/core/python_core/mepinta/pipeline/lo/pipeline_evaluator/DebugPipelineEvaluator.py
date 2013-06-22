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
from mepinta.pipeline.lo.pipeline_evaluator.base import PipelineEvaluatorBase
class DebugPipelineEvaluator(PipelineEvaluatorBase):
  '''
  '''
  def evaluateProp(self, pline, prop_id):
    #check values after processor evaluation (and before?)
    pass
#    prop = pline.all_properties[prop_id]
#    return self.__evalProperty(pline, prop_id, prop)


def shedskin_PipelineEvaluatorFunctum(context_lo, pline, prop, args_mngr):
  pe = DebugPipelineEvaluator(context_lo)
  prop_id = 100
  pline.all_properties[prop_id] = prop
  #pe.__evalFunction(pline, prop_id, prop)
  pe.evaluateProp(pline, prop_id)
  #pe.animate(pline, prop_id)
  #pe.__evalProperty(pline, prop_id, prop)



