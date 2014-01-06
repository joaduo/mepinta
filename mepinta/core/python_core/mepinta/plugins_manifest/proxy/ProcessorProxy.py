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
from bisect import insort_left
from mepinta.plugins_manifest.proxy.data_model import FunctionPropertyProxy, \
  FunctumPropertyProxy, DataPropertyProxy
from mepinta.plugins_manifest.proxy.PropertyProxyContainer import PropertyProxyContainer

class ProcessorProxy(FrameworkBase):
  #TODO: see what to move from
  #TODO: create functions to get all containers together
  #affects TopologyManager, Node and ProcessorPluginsManager (any other?)
  def __post_init__(self, name):
    #TODO: rename to processor_name
    self.name = name
    #self.__backend_name = backend_name
    self.containers = {}
    self.inputs = self.__getContainer('input')
    self.internals = self.__getContainer('internal')
    self.outputs = self.__getContainer('output')
    self.functions = self.__getContainer('function')
    #TODO: make filters for these list, so that they get the correct values
    self.non_cached_capable = [] # a string
    self.marked_outputs = [] #a function property
    #self.marked_inputs = [] #a function property #TODO: is this ever used?

  def __getContainer(self, containerType):
    container = PropertyProxyContainer(self.context)
    container.setContainerType(containerType)
    self.containers[containerType] = container
    return container

  def getRequiredDataTypes(self, types_classes=(DataPropertyProxy,)):
    #TODO: rename types_classes -> types and use tuples instead of lists
    #TODO def getRequiredDataTypes(self, *types_classes): if len(types_classes) == 0: types_classes=[DataPropertyProxy]?
    '''Get a dict of the required data types for this processor. Avoid repeating data types.'''
    #return a dict like: {dt_name:{versions:[]}}
    data_types = {}
    for container in self.containers.values():
      props = container.getProperties(*types_classes)
      for node_property in props.values():
        dt_name = node_property.data_type_name
        if dt_name not in data_types:
          data_types[dt_name] = []# {'versions':[]}
        if node_property.data_type_version not in data_types[dt_name]:
          insort_left(data_types[dt_name], node_property.data_type_version) #create a sorted list, so latest version is at end
    return data_types

  def getFunctionsDict(self):
    '''Get the Functions and Functums defined on this proxy'''
    #returns a dict like: {name:PropertyProxy instance}
    func_dict = {}
    for container in self.containers.values():
      #filter declarationOrder from containers
      container_funcs = container.getProperties(FunctionPropertyProxy, FunctumPropertyProxy)
      if set(container_funcs.keys()) & set(func_dict.keys()):
        #functions name should never repeat
        msg = 'You should\'t make functions or functums with the same name on the same plugin.'
        msg += 'Plugin: %r Functions: %r ' % (self.name, set(container_funcs.key()) & set(func_dict.keys()))
        self.log.e(msg)
      func_dict.update(container_funcs)
    return func_dict

  def setFunctionsId(self, func_dict_ids):
    '''When a processor library was loaded, then set the id of the functions stored in ContextLo.'''
    for func_name, func_id in func_dict_ids.items():
      getattr(self.getContainer(func_name), func_name).func_ptr_id = func_id

  def getContainer(self, func_name): #TODO: rename to getFunctionContainer
    '''Get the container for a specific function name. Names of functions cannot be repeated across containers.'''
    containers = []
    for container in self.containers.values():
      if func_name in container.getProperties():
        containers.append(container)
    if len(containers) > 1:
        msg = 'You should\'t make functions or functums with the same name on the same plugin.'
        msg += 'Plugin: %r  ' % (self.name)
        self.log.e(msg)
    elif len(containers) == 1:
      return containers[0]
    else:
      msg = 'No container for func_name:%r' % func_name
      self.log.e(msg)

def testModule():
  assert None

if __name__ == "__main__":
  testModule()
