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
from mepinta.pipeline.lo.reentrant.reentrant import evaluateProp


def MP_evaluateProp(processor_context, prop_id, dency_id):
    dency_id_return, value = evaluateProp(processor_context, prop_id)
    return value


def shedskin_backend_reentrant_evaluateProp(processor_context):
    MP_evaluateProp(processor_context, prop_id=1, dency_id=None)
