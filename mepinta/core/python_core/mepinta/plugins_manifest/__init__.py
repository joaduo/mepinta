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
from mepinta.plugins_manifest.proxy.data_model import PropertyProxy, DataPropertyProxy, \
  FunctionPropertyProxy, directedReadable, FunctumPropertyProxy, GenericEnumProxy, \
  PropertyProxyQualifier, InotifyPropertyProxy
from mepinta.abstract.MepintaError import MepintaError
from common.type_checking.isiterable import isiterable
from mepinta.plugins_manifest.proxy.ProcessorProxy import ProcessorProxy

__all__ = [
           'DataProperty',
           'FunctionProperty',
           'Functum',
           'GenericEnum',
           'directed',
           'PropertyQualifierBase',
           'InotifyPropertyBase',
           'PluginManifestBase',
           ]

#Better aliases
DataProperty = DataPropertyProxy
FunctionProperty = FunctionPropertyProxy
Functum = FunctumPropertyProxy
GenericEnum = GenericEnumProxy
directed = directedReadable

#aliases for Base classes
PropertyQualifierBase = PropertyProxyQualifier
InotifyPropertyBase = InotifyPropertyProxy

class PluginManifestBase(FrameworkBase):
  '''
    This is the root parent of all the Plugin Manifest classes.
    It inherits from FrameworkBase in order to provide support for the
    self.context object.
    Some Plugins Manifest may react different according to the context.
  '''
  def __post_init__(self):
    '''
      Create the processor proxy and call the define function
      where the plugin developer should define the plugin's input and output
      data types and its topology.
    '''
    #self.processor_proxy = ProcessorProxy(name=self.getName(), backend_name=self.context.backend_name)
    self.processor_proxy = ProcessorProxy(self.context, name=self.getName())
    args, kwargs = self.__createDefineArguments()
    self.define(*args, **kwargs)
  def getName(self):
    return self.__class__.__name__
  def __getBasicArguments(self):
    pp = self.processor_proxy
    return (pp.inputs, pp.internals, pp.functions, pp.outputs)
  def _superClassDefine(self, inputs, internals, functions, outputs):
    '''Reimplement this function in base classes to create a common pipeline topology. '''
    pass
  def __createDefineArguments(self):
    '''
      Calls all collected '_superClassDefine' methods.
      Appends its results to the kwargs dict.
      (that will finally be used to call the Concrete class 'define' method
    '''
    args = self.__getBasicArguments()
    kwargs = {}
    methods = self.__collectDefineMethods(self.__class__.__bases__)
    called_methods = set()
    #Iterate the methods from the Higher super class to the lower one
    for meth in reversed(methods):
      if meth not in called_methods:
        #self.__updateKwArgs(kwargs, meth(self, *args,**kwargs))
        self.__updateKwArgs(kwargs, meth(self, *args))
        called_methods.add(meth)
      else:
        self.context.log.warning('Same _superDefine method %r for manifest: %r' % (meth, self))
    return args, kwargs

  def __updateKwArgs(self, kwargs, props):
    '''
      Updates the kwargs dictionary with the result of a '_superClassDefine' call.
      If props in the dict already exist with that name, then raise an exception.
    '''
    if props == None:
      return
    #One property, then make it iterable
    if not isiterable(props):
      props = [props]
    #If is not a property and not iterable, do nothing (
    if isiterable(props):
      for prop in props:
        if prop.name not in kwargs:
          kwargs[prop.name] = prop
        else:
          raise RuntimeError('Duplicate name %r in define keywords: %r' % (prop.name, kwargs))

  def __collectDefineMethods(self, base_classes):
    '''
      Collect all the '_superClassDefine' methods of the inheritance hierarchy.
      In sub-class to a super-class direction.
    '''
    methods = []
    for class_ in base_classes:
      if class_ != PluginManifestBase and issubclass(class_, PluginManifestBase):
        if hasattr(class_, '_superClassDefine'):
          methods.append(class_._superClassDefine)
        else:
          self.context.log.warning("Class %r has no '_superClassDefine' method" % class_)
        methods += self.__collectDefineMethods(class_.__bases__)
    return methods

  def __getattr__(self, name):
    '''
      If the instance doesn't have the attribute, try to see if it stored
      in the processor proxy instance.
      (this class impersonates a processor proxy)
    '''
    try:
      return object.__getattribute__(self, name)
    except AttributeError as aerr:
      if hasattr(self.processor_proxy, name):
        return getattr(self.processor_proxy, name)
      else:
        raise aerr

  def markedOutputs(self, *props):
    ''' Do we need to mark the outputs for filtered propagation? '''
    #TODO: should check that it's an output prop?
    self.processor_proxy.marked_outputs += props

  def nonCached(self, *props):
    '''
      Add non cached capable input and output properties
      Non cached capable properties means the data can go through the processor
      In other words: processor works directly on the output.
      When caching is enabled, then the input is copied into the output and the
      processor works on the output.
      When non caching is enabled, then the input is moved into the output
      (passing through the processor) and the processor works on the output.
    '''
    #TODO: review this should be self.nonCached(inputs.prop_name,[inputs.prop_name,outputs.prop_name])
    #and no str allowed
    for prop in props:
      if isinstance(prop, list):
        dst_src = prop
      if isinstance(prop.__qualified__(), PropertyProxy):
        prop = prop.name
      if isinstance(prop, str) and \
      hasattr(self.processor_proxy.inputs, prop) and \
      hasattr(self.processor_proxy.outputs, prop):
        dst_src = [getattr(self.processor_proxy.outputs, prop),
                   getattr(self.processor_proxy.inputs, prop), ]
      #Will raise exception if dst_src not declared
      self.processor_proxy.non_cached_capable.append(dst_src)
  def addLibraries(self, external=[], *libs):
    '''
      This functions should let the user declare the libraries dependencies.
      This is intended for the C/C++ plugins.
    '''
    raise MepintaError('Implement!') #TODO
  def addFlags(self, *flags):
    '''
      Passing flags to the C/C++ compiler.
    '''
    raise MepintaError('Implement!') #TODO
  def define(self, inputs, internals, functions, outputs):
    '''
      This function should be overrided by the Plugin Manifest.
      To create a base clase of a plugin group override the
      _defineMethodArguments method.
      This method should be always overrided by (leaf) concrete classes
    '''
    raise MepintaError('You should define your Plugin Manifest!') #TODO
  def build(self):
    '''
      What was this method for? Imagine something here...
      (I think in the future is intended to build the C/C++ plugin
      but maybe here is not the right place)
    '''
    pass

if __name__ == "__main__":
  pass
