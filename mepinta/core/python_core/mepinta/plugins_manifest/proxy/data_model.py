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
'''
This data model represents the configuration of a plugin manifest (a processors
manifest by now)

The biggest container is the ProcessorProxy class.
The containment hierarchy (but not class hierarchy) is as follow:
ProcessorProxy (has 4)
  PropertyProxyContainer (has 0 or more)
    PropertyProxy
    PropertyProxyQualifier (has one)
        ... (many Qualifiers can wrap other qualifiers until you get to the property)
        PropertyProxy

PropertyProxyContainer objects intercept PropertyProxy attributes in the __setattr__
  This way a container sets the name of a PropertyProxy, for example:
  container.expression = DataPropertyProxy('charp')
  Then container.expression.name will be 'expression' since the container object
  intercepted PropertyProxy' instance in __setattr__  and set its name.

As illustrated above, PropertyProxyQualifier children classes can wrap a
property and other qualifiers. The qualifiers mask a property (an thus quality)
of a PropertyProxy.

Examples of qualifiers usage:
  """
    In a real world manifest you should use aliases found in plugin_manifest.__init__ package
      Usin DataProperty instead of DataPropertyProxy, and so on..
  """
  inputs.expression = DataPropertyProxy('charp',1) #no qualification
  #add validation qualifier (always)
  inputs.expression = DataPropertyProxy('charp',1).validateReturn('strlen(%s) > 1')
  #is the same as
  inputs.expression = PPValidationQualifier( DataPropertyProxy('charp',1), '#prop > 1',2)

  #When connecting to functions the 'directedReadable' function makes it more readable
  functions.eval_expression.dpdencies +=  [ directedReadable('<',inputs.expression) ]
  #or better alias 'directed' in plugin_manifest package
  functions.eval_expression.dpdencies +=  [ directed('<',inputs.expression) ]
  #is the same as
  functions.eval_expression.dpdencies +=  [ inputs.expression.directed('<') ]
  #or as
  functions.eval_expression.dpdencies +=  [ PPDirectionQualifier(inputs.expression, '<') ]
  #With the alias you can clearly understand the direction of the connection

  #Validation only for the connection
  functions.eval_expression.dpdencies +=  [ inputs.scalar_number.validateDefault('%s > 1',2) ]

Note that when you qualify in the connection, the qualification won't last in the property.
But when you qualify in initialization (in fact after it), you qualify the property
for any future connection. (you may get the inner property with the __qualified__()
method.

This is the class Hierarchy for Qualifiers:
  PropertyProxyQualifier
    PPDirectionQualifier
    PPValidationQualifier

The hierarchy of Properties Proxies:
  PropertyProxy
    FunctionPropertyProxy    (functions _declaration_order)
    BaseInOutPropertyProxy   (_declaration_order carrying information)
      FunctumPropertyProxy   (property carrying information and other _declaration_order: functum = function + datum)
      DataPropertyProxy      (pure data property)
        InotifyPropertyProxy (The property receives signals from inotify, probably related to a File or Folder)
        GenericEnumProxy     (data property implementing a generic enum data type)


Note: In BaseInOutPropertyProxy.getRealDataTypeName method maps data types to
its real python package path. This is work in progress, since this shold be
done automatically gathering information from the data types manifests.
'''
from bisect import insort_left
from common.abstract.FrameworkObject import FrameworkObject
from pipeline_backend.logging.logging import log_warning

class PropertyProxyQualifier(FrameworkObject):
  def __init__(self, wrapped_prop):
    self.wrapped_prop = wrapped_prop
  def __qualified__(self):
    return self.wrapped_prop.__qualified__()
  def hasQualifier(self, name):
    return hasattr(self, name.lower())
  def _interceptedAttr(self):
    '''
      Reimplement this method on children classes to intercept more attributes.
        And remember adding the _interceptedAttr() result from the parent class.
      Example on children: (suppose we add the direction attribute).
        def _interceptedAttr(self):
          return ['direction'] + PropertyProxyQualifier._interceptedAttr(self)
    '''
    return ['wrapped_prop']
  def __getattr__(self, name):
    '''
      Intercept _declaration_order from this class and inherited classes.
        (by reimplementing _interceptAttr).
    '''
    if name == '_interceptedAttr' or name in self._interceptedAttr():
      return object.__getattribute__(self, name)
    else:
      return PropertyProxy.__getattribute__(self.wrapped_prop, name)
  def __eq__(self, other):
    '''
      When comparing _declaration_order, use the real property without qualifications.
    '''
    return self.__qualified__() == other.__qualified__()
  def __str__(self):
    return str(self.__qualified__())
  def __repr__(self):
    return '<%s wrapping %r>' % (self.__class__.__name__, self.wrapped_prop)

class PPDirectionQualifier(PropertyProxyQualifier):
  def __init__(self, wrapped_prop, direction):
    PropertyProxyQualifier.__init__(self, wrapped_prop)
    if direction not in ['<', '>']:
      raise RuntimeError("Direction parameter should be '<' or '>'. %r is not supported." % direction)
    self.direction = direction
  def _interceptedAttr(self):
    return ['direction'] + PropertyProxyQualifier._interceptedAttr(self)

class PPValidationQualifier(PropertyProxyQualifier):
  class Validation(FrameworkObject):
    def __init__(self, expression, default_value=None):
      self.expression = expression
      self.default_value = default_value
    def isValidateDefault(self):
      return self.defaul_value != None
    def isValidateReturn(self):
      return self.defaul_value == None
  def __init__(self, wrapped_prop, expression, default_value):
    PropertyProxyQualifier.__init__(self, wrapped_prop)
    self.validation = self.Validation(expression, default_value)
  def _interceptedAttr(self):
    return ['validation'] + PropertyProxyQualifier._interceptedAttr(self)

def directedReadable(direction, wrapped_prop):
  '''
    Better direction qualifier alias (easier to read)
    This alias is used to wrap a property in order to set its connection
    direction.
    It's used when assigning the dependencies, for example:
      functions.on_evaluation.dpdencies = +[ directed('<',inputs.number),
                                             directed('>',inputs.text),
                                             inputs.mesh,
                                           ]
    In this example:
      - 'number': will only propagate changes to 'on_evaluation',
        it won't be evaluated from 'on_evaluation' function and
        won't be included on the function's args
      - 'text': will be included in the args of 'on_evaluation',
        but won't propagate changes to 'on_evaluation'
      - 'mesh': will propagate changes and be included in the function's args.
    Use the 'directed' function of the plugins_manifest package to set the
    direction.
  '''
  return PPDirectionQualifier(wrapped_prop, direction)

class PropertyDepedencies(object):
  '''
    Implements the list of Properties that a certain Property depends on.
    Makes sure there are no duplicates.
  '''
  def __init__(self):
    self.__props = []
  def __getattr__(self, name):
    return object.__getattribute__(self.__props, name)
  def __add__(self, added_dpdencies):
    if isinstance(added_dpdencies, (list, tuple)):
      for dency in added_dpdencies:
        self.appendDependency(dency)
    else:
      self.appendDependency(added_dpdencies)
    return self
  def __iter__(self):
    return self.__props.__iter__()
  def appendDependency(self, dency):
    if dency in self.__props:
      raise RuntimeError('Dependency %r already in this Property\'s dependencies.' % dency)
    elif isinstance(dency, (PropertyProxy, PropertyProxyQualifier)):
      self.__props.append(dency)
    else:
      raise RuntimeError('Unsupported dependency type for %r. Dependencies should be a list of PropertyProxy or a PropertyProxy.' % dency)

class PropertyProxy(FrameworkObject):
  '''
    Property proxy is a generic proxy used to define a plugin's manifest.
    But you should use concrete classes 'DataProperty','FunctionProperty'
    from mepinta.plugins_manifest package
  '''
  def __init__(self):
    self.id = None
    #by default the connection is bidirectional. This may be overrided by wrapping it in a Directed
    self.direction = '<>'
    #TODO: check that a property is not added twice, or two _declaration_order with the same name
    self.__dpdencies = PropertyDepedencies()
    self.name = None
    self.parent = None

  def __qualified__(self):
    return self

  def __wrapped_lo__(self):
    if self.id != None:
      return self.id
    else:
      raise RuntimeError('Property: %s has no id defined' % self.name)
  def variableString(self):
    return self.name
  def __str__(self):
    return self.name
  def __repr__(self):
    return '<%s %r %s>' % (self.__class__.__name__, self.name, FrameworkObject.__repr__(self))

  #Properties
  def get_dpdencies(self):
    '''You can get dpdencies, but never set it. Always add or remove _declaration_order from the list.'''
    return self.__dpdencies
  def set_dpdencies(self, value):
    if self.__dpdencies != value:
      raise RuntimeError('Trying to change %r property\'s dpdencies object. You should use the += operator instead.' % str(self))
  dpdencies = property(get_dpdencies, set_dpdencies, None, None)

class BaseInOutPropertyProxy(PropertyProxy):
  def __init__(self, data_type_alias, data_type_version=1, backend_name=''):
    PropertyProxy.__init__(self)
    self.backend_name = backend_name
    #name is from the __dict__ in the container
    self.data_type_name = self.getRealDataTypeName(data_type_alias)
    self.data_type_alias = data_type_alias
    self.data_type_version = data_type_version
    #On a concrete property
    #self.dtype_id = None
  def getDataTypeShortName(self):
    return self.data_type_name.split('.')[-1]

  def getAliasDict(self):
    if self.backend_name == 'python':
      return self._getPythonAliasDict()
    elif self.backend_name == 'c_and_cpp':
      return self._getCAndCppAliasDict()
    else:
      return self._getPythonAliasDict()

  def _getPythonAliasDict(self):
    alias_dict = {
                  'int':'python.builtin.int',
                  'float':'python.builtin.float',
                  'str':'python.builtin.str',
                  }
    return alias_dict

  def _getCAndCppAliasDict(self):
    alias_dict = {
                  'std::string':'cpp.std.string',
                  ##
                  'MP_generic_enum':'c.builtin.int',
                  'mepinta::generic_enum':'c.builtin.int',#'mepinta.generic_enum', #MP_generic_enum
                  'MP_functum':'mepinta.functum', #MP_functum
                  'mepinta::functum':'mepinta.functum', #MP_functum
                  'MP_internal_any':'mepinta.internal_any', #MP_internal_any
                  'mepinta::internal_any':'mepinta.internal_any', #MP_internal_any
                  #k3d
                  'k3d::mesh':'k3dv1.mesh',#'k3dv1.mesh',
                  #'k3d::filesystem::path':'k3dv1_FilesystemPath',#'k3dv1.filesystem.path',
                  'k3d::filesystem::path':'c.builtin.charp',#'k3dv1.filesystem.path',
                  'k3d::imaterial':'k3dv1.imaterial', #k3dv1.imaterial
                  #####==========Correct ones!
                  'int':'c.builtin.int',
                  'double':'c.builtin.double',
                  'uint':'c.builtin.uint',
                  'char*':'c.builtin.charp',#'c.boehm_gc.charp',
                  'charp':'c.builtin.charp',#'c.boehm_gc.charp',
                  'std::string*':'cpp.std.string',
                  ##
                  'MP_generic_enum*':'c.builtin.int',
                  'mepinta::generic_enum*':'c.builtin.int',#'mepinta.generic_enum', #MP_generic_enum
                  'MP_functum*':'mepinta.functum', #MP_functum
                  'mepinta::functum*':'mepinta.functum', #MP_functum
                  'MP_internal_any*':'mepinta.internal_any', #MP_internal_any
                  'internal_any':'mepinta.internal_any', #MP_internal_any
                  'mepinta::internal_any*':'mepinta.internal_any', #MP_internal_any
                  ##
                  'k3d::int32_t':'c.builtin.int', #'c_builtin.int'
                  'k3d::double_t':'c.builtin.double',
                  'k3d::string_t':'cpp.std.string', #'std.string'
                  'k3d::bool_t':'c.builtin.int',
                  ##
                  'k3d::mesh*':'k3dv1.mesh',#'k3dv1.mesh',
                  #'k3d::filesystem::path':'k3dv1_FilesystemPath',#'k3dv1.filesystem.path',
                  'k3d::filesystem::path*':'c.builtin.charp',#'k3dv1.filesystem.path',
                  'k3d::imaterial*':'k3dv1.imaterial', #k3dv1.imaterial
                 }
    return alias_dict

  def getRealDataTypeName(self, data_type_alias):
    '''
      This is a current hack to support data_type aliases
      Later
    '''
    if data_type_alias == 'k3d::filesystem::path*':
      log_warning("The conversion of %s is to char*.(this is wrong, and is a hack) WORK IN PROGRESS!" % data_type_alias)

    alias_dict = self.getAliasDict()
    if data_type_alias in alias_dict:
      return alias_dict[data_type_alias]
    else:
      return data_type_alias

  def directed(self, direction):
    '''
      if direction='>' means other property depends on this property in the relation.(but is not notified)
      if direction='<' means this property notifies changes to the other property in the relation.(but won't be in it's args)
    '''
    return PPDirectionQualifier(self, direction)

class DataPropertyProxy(BaseInOutPropertyProxy):
  '''
    Class used by a plugin's manifest
      You should use alias 'DataProperty'
      from mepinta.plugins_manifest package
  '''
  def validateDefault(self, expression, default_value):
    return PPValidationQualifier(self, expression, default_value)
  def validateReturn(self, expression):
    return PPValidationQualifier(self, expression, None)

class InotifyPropertyProxy(DataPropertyProxy):
  def getPath(self, pline, context):
    raise RuntimeError('Implement on child class. (could be on concrete class %s)' % self.__class__)

class InputFilePropertyProxy(InotifyPropertyProxy):
  def __init__(self):
    InotifyPropertyProxy.__init__(self, 'c.builtin.charp')
  def getPath(self, pline, context):
    from mepinta.pipeline.hi.value_manager.ValueManager import ValueManager
    value_mngr = ValueManager(context)
    return value_mngr.getValue(pline, self)

class GenericEnumProxy(DataPropertyProxy):
  '''
    Class used by a plugin's manifest
      You should use alias 'GenericEnum'
      from mepinta.plugins_manifest package
  '''
  def __init__(self, **enum_dict):
    DataPropertyProxy.__init__(self, 'MP_generic_enum', data_type_version=1)
    self.__validateEnumDict(enum_dict)
    self.enum_dict = enum_dict
    #the smallest value is the first default. Later can be changed with the 'setDefault' method.
    self.default_value = sorted(self.enum_dict.values())[0]
    self.enum_id = None
  def invertedDict(self):
    return dict((value, label) for label, value in self.enum_dict.items())
  def __validateEnumDict(self, enum_dict):
    if len(enum_dict) == 0:
      raise RuntimeError('At least you should provide one label=value pair.')
    for value in enum_dict.values():
      if not isinstance(value, int):
        raise RuntimeError('For a GenericEnum you must supply a label=value dictionary. Where value is of int type.')
    if len(set(enum_dict.values())) != len(enum_dict):
      raise RuntimeError('For a GenericEnum you must supply a label=value dictionary. All values must differ.')
  def setDefault(self, value):
    '''
      Set the default value for this enum. (when the given value doesn't
        correspond to an existing value)
      May be an integer value or a string with the label.
      Example:
        inputs.axis = GenericEnum(X=0, Y=1, Z=2).setDefault('SPHERE')
    '''
    if value in self.enum_dict.values():
      self.default_value = value
    elif value in self.enum_dict:
      self.default_value = self.enum_dict[value]
    else:
      raise RuntimeError('Default value %r was not defined for this enum %r' % (value, self.enum_dict))
    return self
  #Properties
  def get_enum_id(self):
    if self.__enum_id == None:
      raise RuntimeError('A enum id must be set from the PropertyProxyContainer class.')
    return self.__enum_id
  def set_enum_id(self, value):
    self.__enum_id = value
  enum_id = property(get_enum_id, set_enum_id, None, None)

class FunctumPropertyProxy(BaseInOutPropertyProxy):
  '''
    Class used by a plugin's manifest
      You should use alias 'FunctumProperty'
      from mepinta.plugins_manifest package
  '''
  def __init__(self):
    BaseInOutPropertyProxy.__init__(self, "MP_functum", data_type_version=1)

class FunctionPropertyProxy(PropertyProxy):
  '''
    Class used by a plugin's manifest
      You should use alias 'FunctionProperty'
      from mepinta.plugins_manifest package
  '''
  pass

class PropertyProxyContainer(FrameworkObject):
  '''
    Beware: every public attribute set that is of type 'str' will become a
      DataPropertyProxy tacking the type from the string passed.
    All private attributes are not converted.
  '''
  def __init__(self, backend_name):
    #keep the properties declaration order in the manifest
    self._declaration_order = []
    self.container_type = None
    self.__backend_name = backend_name

  def get_properties(self, *types):
    '''
      Get the properties in this container of a specific property type.
      Possible types: (with hierarchy)
        PropertyProxy
          FunctionPropertyProxy    (functions _declaration_order)
          BaseInOutPropertyProxy   (_declaration_order carrying information)
            FunctumPropertyProxy   (property carrying information and other _declaration_order: functum = function + datum)
            DataPropertyProxy      (pure data property)
              InotifyPropertyProxy (The property receives signals from inotify, probably related to a File or Folder)
              GenericEnumProxy     (data property implementing a generic enum data type)
      If no types are provided, then the type is choosen based on this container
        name.
        FunctionPropertyProxy if th
    '''
    if len(types) == 0:
      types = self.__getContainerTypes()
    properties = {}
    for prop_name, prop_proxy in self.__dict__.items():
      if self.__inTypes(prop_proxy, types):
        properties[prop_name] = prop_proxy
    return properties

  def __getContainerTypes(self):
    '''Get the container's default type, based on container name'''
    if self.container_type == 'function':
      return [FunctionPropertyProxy]
    else:
      return [BaseInOutPropertyProxy]

  def __inTypes(self, prop_proxy, types):
    '''Checks if a PropertyProxy is in a list of types.'''
    for tpe in types:
      if isinstance(prop_proxy, tpe) and isinstance(tpe, type):
        return True
    return False

  def __setattr__(self, name, value):
    '''
      Intercepts PropertyProxy values to set their names.
      If the attribute is public and value is of str type, then it will be
        converted to a DataPropertyProxy, taking the string as the type.
    '''
    #not name.startswith('_%s' % self.__class__.__name__) \
    if not name.startswith('_') \
      and name not in ['container_type'] :
      if isinstance(value, str):
        value = DataPropertyProxy(value, backend_name=self.__backend_name)
      if isinstance(value, tuple) and len(value) == 2  and \
         isinstance(value[0], str): #Passing a tuple like 'int',1 (data type, minor version)
        value = DataPropertyProxy(value[0], value[1], backend_name=self.__backend_name)
      if isinstance(value, PropertyProxy): #TODO: filter according to the container type. #TODO: here filter when its a function or a In/Out/Internal?
        self.__addProp(name, value)
        value.parent = self
    FrameworkObject.__setattr__(self, name, value)

  def getDeclarationOrder(self):
    return self._declaration_order

  def __addProp(self, name, value):
    value.name = name
    value.type = self.container_type
    if name in self._declaration_order:
      raise RuntimeError('Declaring property %r twice for this container.' % name)
    self._declaration_order.append(name)

  def __delattr__(self, name):
    '''
      When deleting an attribute, make sure to delete it from the
        _declaration_order list.
    '''
    prop = getattr(self, name)
    if isinstance(prop, PropertyProxy):
      self._declaration_order.remove(prop.name)
    return FrameworkObject.__delattr__(self, name)

class ProcessorProxy(FrameworkObject):
  #TODO: see what to move from
  #TODO: create functions to get all containers together
  #affects TopologyManager, Node and ProcessorPluginsManager (any other?)
  def __init__(self, name, backend_name):
    #TODO: rename to processor_name
    self.name = name
    self.backend_name = backend_name
    self.containers = {}
    self.inputs = PropertyProxyContainer(backend_name)
    self.internals = PropertyProxyContainer(backend_name)
    self.outputs = PropertyProxyContainer(backend_name)
    self.functions = PropertyProxyContainer(backend_name)
    #TODO: check if this below is necessary
    #self.ui_functions = PropertyProxyContainer()
    #self.non_cached_mandatory = [] #TODO: completely remove unnecesary feature
    #self.variable_properties = [] #TODO: delete this, is unused?
    #TODO: make filters for these list, so that they get the correct values
    self.non_cached_capable = [] # a string
    self.marked_outputs = [] #a function property
    #self.marked_inputs = [] #a function property #TODO: is this ever used?
  def __setattr__(self, name, value):
    if isinstance(value, PropertyProxyContainer):
      value.container_type = name[:-1] #remove the plural
      self.containers[name[:-1]] = value
    FrameworkObject.__setattr__(self, name, value)
  def getRequiredDataTypes(self, types_classes=[DataPropertyProxy]):
    '''Get a dict of the required data types for this processor. Avoid repeating data types.'''
    #return a dict like: {dt_name:{versions:[]}}
    data_types = {}
    for container in self.containers.values():
      props = container.get_properties(*types_classes)
      for node_property in props.values():
        dt_name = node_property.data_type_name
        if dt_name not in data_types:
          data_types[dt_name] = []# {'versions':[]}
        if node_property.data_type_version not in data_types[dt_name]:
          insort_left(data_types[dt_name], node_property.data_type_version) #create a sorted list, so latest version is at end
    return data_types
  def get_functions_dict(self):
    '''Get the Functions and Functums defined on this proxy'''
    #returns a dict like: {name:propertyProxy_instance}
    func_dict = {}
    for container in self.containers.values():
      #filter _declaration_order from containers
      container_funcs = container.get_properties(FunctionPropertyProxy, FunctumPropertyProxy)
      if set(container_funcs.keys()) & set(func_dict.keys()):
        #functions name should never repeat
        msg = 'You should\'t make functions or functums with the same name on the same plugin.'
        msg += 'Plugin: %r Functions: %r ' % (self.name, set(container_funcs.key()) & set(func_dict.keys()))
        self.context.log.error(msg)
      func_dict.update(container_funcs)
    return func_dict
  def set_functions_id(self, func_dict_ids):
    '''When a processor library was loaded, then set the id of the functions stored in ContextLo.'''
    for func_name, func_id in func_dict_ids.items():
      getattr(self.get_container(func_name), func_name).func_ptr_id = func_id
  def get_container(self, func_name):
    '''Get the container for a specific function name. Names of functions cannot be repeated across containers.'''
    containers = []
    for container in self.containers.values():
      if func_name in container.get_properties():
        containers.append(container)
    if len(containers) > 1:
        msg = 'You should\'t make functions or functums with the same name on the same plugin.'
        msg += 'Plugin: %r  ' % (self.name)
        self.context.log.error(msg)
    return containers[0]

if __name__ == '__main__':
  #TODO: review this
  from mepinta.context.MepintaContext import MepintaContext
  context = MepintaContext('python')
  def test():
    prop1 = DataPropertyProxy('charp', '10_v10')
    #TODO: check out that user defined versions should compare correctly
    prop2 = DataPropertyProxy('charp', 1)
    fprop1 = FunctionPropertyProxy()
    container = PropertyProxyContainer()
    container.container_type = 'input'
    container.count = DataPropertyProxy('int')
    container.expression = DataPropertyProxy('charp')
    container.operation = FunctionPropertyProxy()
    print (container.get_properties())

  test()

  def get_processor_proxy(context):
    pp = ProcessorProxy('ScalarExpression')
    #Inputs
    pp.inputs.expression = DataPropertyProxy('charp', 1)
    pp.inputs.scalar_number = DataPropertyProxy('double', 1)
    pp.inputs.scalar_number_name = DataPropertyProxy('charp', 1)
    pp.inputs.count = 'k3d::int32_t'
    #Internal values
    pp.internals.variables_count = DataPropertyProxy('uint', 1)
    pp.internals.parser = DataPropertyProxy('internal_any', 1)
    #Output result
    pp.outputs.scalar_number = DataPropertyProxy('double', 1)
    #Functions
    pp.functions.eval_expression = FunctionPropertyProxy()
    pp.functions.parse_expression = FunctionPropertyProxy()

    #Set dependencies
    pp.functions.parse_expression.dpdencies += [ pp.inputs.expression
                                                 , pp.inputs.scalar_number_name
                                                 , pp.inputs.count
                                                 ]
    pp.internals.parser.dpdencies += [ pp.functions.parse_expression ]
    pp.internals.variables_count.dpdencies += [ pp.functions.parse_expression ]

    pp.functions.eval_expression.dpdencies += [ directedReadable('<', pp.inputs.scalar_number)
                                                , pp.internals.parser
                                                , pp.internals.variables_count
                                                 ]
    pp.outputs.scalar_number.dpdencies += [ pp.functions.eval_expression ]

    #pp.outputs.scalar_number.dpdencies = []

    return pp

  pp = get_processor_proxy(context)

  def print_processor_definition(context, pp):
    for cont_name, props in pp.containers.items():
      context.log.info("Container %r" % cont_name)
      props_dict = props.get_properties()
      for name in props._declaration_order:
        if name in props_dict:
          prop = props_dict[name]
          if isinstance(prop, BaseInOutPropertyProxy):
            context.log.info('  %r type:%r data_type_name:%r' % (name, prop.type, prop.data_type_name))
          else:
            context.log.info('  %r type:%r ' % (name, prop.type))

  print_processor_definition(context, pp)

  def test_qualifiers():
    qualified = PPDirectionQualifier(pp.inputs.expression, '<')
    qualified1 = qualified
    print qualified
    #qualified = DataPropertyProxy('name')
    print qualified.direction
    print qualified.name
    print qualified.data_type_name
    print qualified.hasQualifier('direction')
    qualified = PPValidationQualifier(qualified, '#prop > 1', 2)
    print qualified.hasQualifier('Validation')
    print qualified == pp.inputs.expression
    print qualified == qualified1
    print qualified == pp.inputs.scalar_number
    qualified2 = PPDirectionQualifier(pp.inputs.scalar_number, '<')
    print qualified == qualified2
    print qualified2 == pp.inputs.scalar_number
    print pp.inputs.expression.directed('<')
    print qualified == pp.inputs.expression.directed('<')
    print qualified2 == pp.inputs.scalar_number.validateDefault('#prop < 1', 0).directed('<')
    print qualified2 == directedReadable('<', pp.inputs.scalar_number.validateDefault('#prop < 1', 0))
    print repr(qualified)
    print repr(directedReadable('<', pp.inputs.scalar_number.validateDefault('#prop < 1', 0)))

  test_qualifiers()
