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

class ProcessorContext(object):
  def __init__(self, context_lo, pline, pline_evaluator):
    self.context_lo = context_lo
    self.pline = pline
    self.pline_evaluator = pline_evaluator

        
def shedskin_reentrant_data_model(context_lo, pline, pline_evaluator):
  processor_context = ProcessorContext(context_lo, pline, pline_evaluator)
  return processor_context
