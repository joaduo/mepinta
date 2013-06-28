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

from mepinta.plugins_manifest.proxy.data_model import FunctionPropertyProxy,\
  DataPropertyProxy, FunctumPropertyProxy
from common.abstract.FrameworkBase import FrameworkBase
from mepinta.pipeline.hi.property_manager.PropertyManager import PropertyManager
from mepinta.plugins_manager.PluginsManager import PluginsManager
from mepinta.pipeline.lo.constants import CUSTOM_PROPERTY_FLAG

class GraphNodePropertyCreator(FrameworkBase):
  def __post_init__(self):
    self.prop_mngr = PropertyManager(context=self.context)
  def createProperties(self, pline, node_proxy):
    prop_ids  = self.__createInoutProps(pline, node_proxy.inputs)
    prop_ids += self.__createInoutProps(pline, node_proxy.internals)
    prop_ids += self.__createInoutProps(pline, node_proxy.outputs)
    prop_ids += self.__createFunctionsProps(pline, node_proxy.functions)
    self.__setNonCached(pline, node_proxy)
    self.__setPropagationFilter(pline, node_proxy)
    return prop_ids
  #TODO: def __create_containers_props(self, pline, containers)
  def __setPropsIds(self, prop_dict, prop_names, prop_ids):
    for index, name in enumerate(prop_names):
      prop_dict[name].property_id = prop_ids[index]
  def __createFunctionsProps(self, pline, container):
    prop_dict = container.getProperties(FunctionPropertyProxy)
    prop_names = list(prop_dict.keys())
    prop_names.sort()
    func_ids = []
    for name in prop_names:
      func_ids.append(prop_dict[name].func_ptr_id)
    prop_ids = self.prop_mngr.createFuncProperties(pline, prop_names, func_ids)
    self.__setPropsIds(prop_dict, prop_names, prop_ids)
    return prop_ids
  def __createInoutProps(self, pline, container):#TODO: take this out
    prop_ids = self.__createDataProps(pline, container)
    prop_ids += self.__createFunctumProps(pline, container)
    return prop_ids
  def __getContainerProps(self, container, class_):
    prop_dict = container.getProperties(class_)
    prop_names = list(prop_dict.keys())
    new_prop_names = []
    for name in prop_names:
      if not prop_dict[name].property_id:
        new_prop_names.append(name)
    if len(new_prop_names) == len(prop_dict):
      prop_flags = 0
    else:
      prop_flags = CUSTOM_PROPERTY_FLAG
    new_prop_names.sort()
    return new_prop_names, prop_dict, prop_flags
  def __createDataProps(self, pline, container):#TODO: take this out    
    prop_names, prop_dict, prop_flags = self.__getContainerProps(container, DataPropertyProxy)
    dtype_ids = []
    for name in prop_names:
      dtype_ids.append(prop_dict[name].dtype_id)
    prop_ids = self.prop_mngr.createProperties(pline, container.containerType, prop_names, dtype_ids, prop_flags)
    self.__setPropsIds(prop_dict, prop_names, prop_ids)
    return prop_ids
  def __createFunctumProps(self, pline, container):#TODO: take this out    
    prop_names, prop_dict, prop_flags = self.__getContainerProps(container, FunctumPropertyProxy)
    func_ids = []
    dtype_ids = []
    for name in prop_names:
      func_ids.append(prop_dict[name].func_ptr_id)
      dtype_ids.append(prop_dict[name].dtype_id)
    prop_ids = self.prop_mngr.createFunctumProperties(pline, prop_names, func_ids, dtype_ids, prop_flags)
    self.__setPropsIds(prop_dict, prop_names, prop_ids)
    return prop_ids    
  def __setPropagationFilter(self, pline, node_proxy):
    if len(node_proxy.processor.proxy.marked_outputs) == 0:
      return    
    prop_ids = [getattr(node_proxy.functions, prop_prxy.name).property_id for prop_prxy in node_proxy.processor.proxy.marked_outputs ]
    self.prop_mngr.addFilters(pline,prop_ids)
  def __setNonCached(self, pline, node_proxy):
    prop_names = node_proxy.non_cached_capable
    if len(prop_names) == 0:
      return    
    prop_dst_ids = []
    prop_src_ids = []
    for dst_prop,src_prop in prop_names:
      prop_dst_ids.append(dst_prop)
      prop_src_ids.append(src_prop)
    self.prop_mngr.addNonCached(pline, prop_dst_ids, prop_src_ids)

class GraphPropertyManager(FrameworkBase):
  def __post_init__(self):
    self.plugins_mngr = PluginsManager(self.context)
    self.prop_mngr = PropertyManager(self.context)
    self.node_prop_creator = GraphNodePropertyCreator(context=self.context)
  def createProperties(self, pline, node_proxy): #TODO: add support for debugging version
    return self.node_prop_creator.createProperties(pline, node_proxy)
  