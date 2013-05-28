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
from common.abstract.FrameworkBase import FrameworkBase
from mepinta.pipeline.hi.base import unwrap_decorator
from mepinta.pipeline.hi.FactoryLo import FactoryLo

class UntypedValueManager(FrameworkBase):
  def __post_init__(self):
    self._value_manager_lo = FactoryLo(self.context).getInstance('ValueManager', self.context)

  @unwrap_decorator
  def getValue(self, pline, prop):
    return self._value_manager_lo.getUntypedPropsValues(pline, [prop])

  @unwrap_decorator
  def setValue(self, pline, prop, value):
    self._value_manager_lo.setUntypedPropsValues(pline, [prop], [value])

  @unwrap_decorator
  def markChanged(self, pline, prop):
    self._value_manager_lo.markChangedProps(pline, [prop])

  @unwrap_decorator
  def getValues(self, pline, props):
    return self._value_manager_lo.getUntypedPropsValues(pline, props)

  @unwrap_decorator
  def setValues(self, pline, props, values):
    self._value_manager_lo.setUntypedPropsValues(pline, props, values)

def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  test_module()
