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
from pipeline_backend.logging.logging import logDebug
from mepinta.pipeline.lo.context_lo.ContextLo import ContextLo
from mepinta.pipeline.lo.pipeline_evaluator.base import PipelineEvaluatorBase

def isDataTypeAlias(processor_context, data_type_name, data_type_alias):
  logDebug('Checking if data type %s is an alias of %s'%(data_type_alias,data_type_name))
  return data_type_alias in processor_context.context_lo.data_type_aliases[data_type_name]

def evaluateProp(processor_context, prop_id):
  logDebug('Evaluating prop_id %s in reentrant mode.'%prop_id)
  dency_id, dency_prop = processor_context.pline_evaluator.evaluateProp(processor_context.pline, prop_id)
  return dency_id, dency_prop.getValuePtr().getValue()

def shedskin_reentrant(processor_context):
  isDataTypeAlias(processor_context, "int", "int32_t")
  evaluateProp(processor_context, prop_id=1)
