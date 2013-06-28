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
from mepinta.pipeline.lo.pipeline_data.data_model import PropertyValuePointer
from pipeline_backend.logging.logging import logError
from mepinta.pipeline.lo.value_manager.PropertyValueManager import PropertyValueManager
from mepinta.pipeline.lo.exceptions.MepintaLoError import MepintaLoError
from mepinta.pipeline.lo.FunctionCaller import FunctionCaller

class DebugPropertyValueManager(object):
  '''
  This version of PropertyValueManager makes sure the data_type's invariants are
  consistent across copying and initialization of properties values. (inside value pointers)
  Invariant checking is provided by the checkRepr function in the data type.
  '''
  def __init__(self, context_lo):
    self.context_lo = context_lo
    self.prop_value_mngr = PropertyValueManager(self.context_lo)
    self.func_caller = FunctionCaller()
  def __getCheckReprFunction(self, prop):
    data_type = self.context_lo.data_types[prop.dtype_id]
    func_ptr_check_repr = data_type.getFuncPtr('checkRepr')
    if func_ptr_check_repr == None:
      msg = 'Cannot find checkRepr function for data_type:%r' % data_type
      logError(msg)
      raise MepintaLoError(msg)
    return func_ptr_check_repr
  def __checkRepr(self, prop):
    self.__checkRepr(prop, prop.getValuePtr().getValue())
  def __checkValueRepr(self, prop, value):
    func_ptr_check_repr = self.__getCheckReprFunction(prop)
    if not self.func_caller.callIntFuncVoidp(func_ptr_check_repr, value):
      data_type = self.context_lo.data_types[prop.dtype_id]
      msg = 'checkRepr failed for prop:%r and data_type:%r' % (prop, data_type)
      raise MepintaLoError(msg)
  def replacePropValue(self, prop, value):
    self.prop_value_mngr.replacePropValue(prop, value)
    self.__checkRepr(prop)
  def initPropValue(self, prop):
    self.prop_value_mngr.initPropValue(prop)
    self.__checkRepr(prop)
  def setPropValuePointer(self, prop, value_ptr):
    #TODO:
    #    if prop.type == FUNCTION_PROPERTY_FLAG: #Functions have data_type = 0
    #      logWarning('You shouldn\'t set a function property value pointer. Doing nothing.')
    #    else:
    self.__checkValueRepr(prop, value_ptr.getValue())
    self.prop_value_mngr.setPropValuePointer(prop, value_ptr)
  def copyPropValue(self, prop, value_ptr):
    self.__checkValueRepr(prop, value_ptr.getValue())
    self.prop_value_mngr.copyPropValue(prop, value_ptr)
    self.__checkRepr(prop)
  def deletePropsValues(self, props):
    for prop in props:
      value = prop.getValuePtr().getValue()
      if value != None:
        self.__checkValueRepr(prop, value)
    self.prop_value_mngr.deletePropsValues(props)

def shedskin_DebugPropertyValueManager(context_lo, prop):
  pvm = DebugPropertyValueManager(context_lo)
  value = None
  pvm.replacePropValue(prop, value)
  pvm.initPropValue(prop)
  value_ptr = PropertyValuePointer()
  pvm.setPropValuePointer(prop, value_ptr)
  pvm.copyPropValue(prop, value_ptr)
  pvm.deletePropsValues([prop])


