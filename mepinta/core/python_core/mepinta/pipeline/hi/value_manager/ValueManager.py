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
from mepinta.pipeline.hi.base import HiAutoBase, unwrap_decorator
from mepinta.plugins_manifest.proxy.data_model import DataPropertyProxy,\
  GenericEnumProxy


class ValueManager(HiAutoBase):
  def getDispatchDict(self, prefix):
    dispatch_template = {'c.builtin.int':'int',
                         'c.builtin.double':'double',
                         'c.builtin.charp':'charp',
                         'cpp.std.string':'std_string',
                        }
    dispatch_dict = {}
    for data_type_name,target in dispatch_template.items():
      dispatch_dict[data_type_name] = getattr(self, '_%s__%s_%s'%(self.__class__.__name__,prefix,target))
    return dispatch_dict

  def __checkProp(self, prop):
    if not isinstance(prop, DataPropertyProxy):
      raise RuntimeError('You shold provide a DataPropertyProxy object. Unsupported object: %r of type %r'%(prop,type(prop)))
        
  def getValue(self,pline, prop):
    self.__checkProp(prop)
    if prop.data_type_name in self.getDispatchDict('get'):
      return self.getDispatchDict('get')[prop.data_type_name](pline, prop)
    else:
      self.context.log.warning('Unsupported getter for type %s'%prop.getDataTypeShortName())
  
  def __setGenericEnum(self, pline, prop, value):
    if value in prop.enum_dict:
      value = prop.enum_dict[value]
    elif value not in prop.enum_dict.values():
      value = prop.default_value
    self.__set_int(pline, prop, value)
    
  def setValue(self, pline, prop, value):
    self.__checkProp(prop)
    if isinstance(prop, GenericEnumProxy):
      self.__setGenericEnum(pline,prop,value)
    elif prop.data_type_name in self.getDispatchDict('set'):
      self.getDispatchDict('set')[prop.data_type_name](pline, prop, value)
    else:
      self.context.log.warning('Unsupported setter for type %s'%prop.getDataTypeShortName())
    
  @unwrap_decorator
  def markChanged(self, pline, prop):
    self.wrapped.markChangedProps(pline, [prop])

  #TODO: should be able to set ctypes structs. It will be implemented on C + Ctypes. But not in this module
  @unwrap_decorator
  def __set_std_string(self,pline, prop, str_):
    self.wrapped.set_std_strings(pline,[prop],[str(str_)])    
  @unwrap_decorator
  def __set_charp(self,pline, prop, str_):
    self.wrapped.set_charps(pline,[prop],[str(str_)])  
  @unwrap_decorator
  def __set_str(self,pline, prop, str_):
    self.wrapped.set_charps(pline,[prop],[str(str_)])
  @unwrap_decorator
  def __set_int(self,pline, prop, int_):
    self.wrapped.set_ints(pline,[prop],[int(int_)])
  @unwrap_decorator
  def __set_double(self, pline, prop, double_):
    self.wrapped.set_doubles(pline, [prop], [float(double_)])

  @unwrap_decorator
  def __get_std_string(self, pline, prop):
    values = self.wrapped.get_std_strings(pline,[prop])
    if len(values) > 0:
      return values[0]
    else:
      return None  
  @unwrap_decorator
  def __get_charp(self, pline, prop):
    values = self.wrapped.get_charps(pline,[prop])
    if len(values) > 0:
      return values[0]
    else:
      return None   
  @unwrap_decorator
  def __get_str(self, pline, prop):
    values = self.wrapped.get_charps(pline,[prop])
    if len(values) > 0:
      return values[0]
    else:
      return None
  @unwrap_decorator
  def __get_int(self, pline, prop):
    values = self.wrapped.get_ints(pline,[prop])
    if len(values) > 0:
      return values[0]
    else:
      return None    
  @unwrap_decorator
  def __get_double(self, pline, prop):
    values = self.wrapped.get_doubles(pline,[prop])
    if len(values) > 0:
      return values[0]
    else:
      return None    
