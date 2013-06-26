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
from mepinta.plugins_manifest.proxy.data_model import FunctionPropertyProxy, \
  InOutPropertyProxyBase, DataPropertyProxy, PropertyAndQualifierBase, \
  FunctumPropertyProxy, QualifierBase
from mepinta.plugins_manager.data_types.DataTypeAliasManager import DataTypeAliasManager

class PropertyProxyContainer(FrameworkBase):
  '''
    Beware: every public attribute set that is of type 'str' will become a
      DataPropertyProxy taking the type from the string passed.
    All private attributes are not converted.
  '''
  def __post_init__(self):
    self.__declaration_order = [] #keep  the manifest' properties declaration order
    self.__container_type = None
    self.__backend_name = self.context.backend_name
    self.__data_type_alias_manager = DataTypeAliasManager(self.context)

  @property
  def containerType(self):
    return self.__container_type

  def setContainerType(self, containerType):
    '''
    Since the containerType property is read-only, this method is used to set
      the container type. (done in the ProcessorProxy class)
    :param containerType:
    '''
    self.__container_type = containerType

  @property
  def declarationOrder(self):
    return self.__declaration_order

  def getProperties(self, *types):
    '''
      Get the properties in this container of a specific property type.
      Possible types: (with hierarchy)
        PropertyAndQualifierBase
          PropertyProxy
            FunctionPropertyProxy    (functions declarationOrder)
            InOutPropertyProxyBase   (declarationOrder carrying information)
              FunctumPropertyProxy   (property carrying information and other declarationOrder: functum = function + datum)
              DataPropertyProxy      (pure data property)
                InotifyPropertyProxy (The property receives signals from inotify, probably related to a File or Folder)
                GenericEnumProxy     (data property implementing a generic enum data type)
      If no types are provided, then the type is choosen based on this container
        name.
        FunctionPropertyProxy if th
    '''
    if not len(types):
      types = self.__getContainerTypes()
    properties = {}
    for prop_name, prop_proxy in self.__dict__.items():
      #Check if the property is of the type or the qualified is of the type
      if isinstance(prop_proxy, types) or isinstance(prop_proxy, QualifierBase) and isinstance(prop_proxy.__qualified__(), types):
        properties[prop_name] = prop_proxy
    return properties

  def __getContainerTypes(self):
    '''Get the container's default type, based on container name'''
    if self.containerType == 'function':
      return FunctionPropertyProxy
    else:
      return InOutPropertyProxyBase

  def __setattr__(self, name, value):
    '''
      Intercepts PropertyProxy values to set their names.
      If the attribute is public and value is of str type, then it will be
      converted to a DataPropertyProxy, taking the string as the property type.
    '''
    if not name.startswith('_') :
      if isinstance(value, str):
        if value in self.__data_type_alias_manager.getFunctumAliases():
          value = FunctumPropertyProxy()
        else:
          value = DataPropertyProxy(value)
      if isinstance(value, tuple) and len(value) == 2  and \
         isinstance(value[0], str): #Passing a tuple like 'int',1 (data type, minor version)
        value = DataPropertyProxy(value[0], value[1])
      if isinstance(value, PropertyAndQualifierBase): #TODO: validate according to the container type. #TODO: here validate when its a function or a In/Out/Internal?
        self.__addProp(name, value)
        #value.parent = self #TODO: remove?
        if isinstance(value.__qualified__(), InOutPropertyProxyBase):
          value.data_type_name = self.__data_type_alias_manager.getRealDataTypeName(value.data_type_alias)
    FrameworkBase.__setattr__(self, name, value)

  def __addProp(self, name, value):
    '''
    Add a new property to the processor's manifest
    :param name: name of the property
    :param value: the property object
    '''
    value.name = name
    value.type = self.containerType
    if name in self.declarationOrder:
      raise RuntimeError('Declaring property %r twice for this container.' % name)
    self.declarationOrder.append(name)

  def __delattr__(self, name):
    '''
      When deleting an attribute, make sure to delete it from the
        declarationOrder list.
    '''
    prop = getattr(self, name)
    if isinstance(prop, PropertyAndQualifierBase):
      self.declarationOrder.remove(prop.name)
    return FrameworkBase.__delattr__(self, name)

def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  testModule()
