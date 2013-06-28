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
from mepinta.pipeline.hi.base import  HiAutoBase, unwrap_decorator

class PipelineEvaluatorFunctum(HiAutoBase):
  def __post_init__(self):
    self.ppgation_mngr = self._getWrappedClass("SimplePropagationManager")(self.wrapped)
  @unwrap_decorator
  def propagateChanges(self, pline):
    self.ppgation_mngr.propagateChanges(pline)
  @unwrap_decorator
  def evaluateProp(self, pline, prop_id):
    if prop_id in pline.getTopology().properties:
      #pline.startTopologyChangeSet() #TODO: review
      self.ppgation_mngr.propagateChanges(pline)
      return self.wrapped.evaluateProp(pline, prop_id)
    else:
      self.log.warning('Property is not in the current topology. Not evaluating')


def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()
  pe = PipelineEvaluatorFunctum(context=context)
  context.log(pe)

if __name__ == '__main__':
  testModule()

