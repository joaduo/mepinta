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
from mepinta.pipeline.hi.value_manager.UntypedValueManager import UntypedValueManager
from mepinta.pipeline.hi.value_manager.ValueManager import ValueManager
from mepinta.plugins_manifest.proxy.data_model import DataPropertyProxy

class AbstractValueManager(FrameworkBase):
  def __post_init__(self):
    self.__value_managers = { 'python':UntypedValueManager(self.context),
                              'c_and_cpp': ValueManager(self.context),
                            }

  def __checkProp(self, prop):
    if not isinstance(prop, DataPropertyProxy):
      raise RuntimeError('You shold provide a DataPropertyProxy object. Unsupported object: %r of type %r' % (prop, type(prop)))

  def __checkProps(self, props):
    for prop in props:
      self.__checkProp(prop)

  def getValue(self, pline, prop):
    self.__checkProp(prop)
    return self.__value_managers[self.context.backend_name].getValue(pline, prop)

  def setValue(self, pline, prop, value):
    self.__checkProp(prop)
    return self.__value_managers[self.context.backend_name].setValue(pline, prop, value)

  def getValues(self, pline, props):
    self.__checkProps(props)
    return self.__value_managers[self.context.backend_name].getValues(pline, props)

  def setValues(self, pline, props, values):
    self.__checkProps(props)
    return self.__value_managers[self.context.backend_name].setValues(pline, props, values)

def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  testModule()
