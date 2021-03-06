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



This data model represents the configuration of a plugin manifest (a processors
manifest by now)

The biggest container is the ProcessorProxy class.
The composition hierarchy (but not class hierarchy) is as follow:
ProcessorProxy (has 4)
  PropertyProxyContainer (has 0 or more)
    PropertyProxy
    QualifierBase (has one or
        ... many Qualifiers can wrap other qualifiers until you get to the property)
          PropertyProxy

PropertyProxyContainer objects intercept attributes in the __setattr__
  This way a container sets a PropertyProxy, for example:
    container.expression = 'charp'
  Its the same as
    container.expression = DataPropertyProxy('charp')
  Then container.expression.name will be 'expression'.

As illustrated above, QualifierBase children classes can wrap a
property and other qualifiers. The qualifiers mask one or more property from a
PropertyProxy.

#TODO: better real world examples
Examples of qualifiers usage:
  """
    In a real world manifest you should use aliases found in plugin_manifest.__init__ package
      Usin DataProperty instead of DataPropertyProxy, and so on..
  """
  inputs.expression = DataPropertyProxy('charp',1) #no qualification
  #add validation qualifier (always)
  inputs.expression = DataPropertyProxy('charp',1).validateReturn('strlen(%s) > 1')
  #is the same as
  inputs.expression = ValidationQualifier( DataPropertyProxy('charp',1), '#prop > 1',2)

  #When connecting to functions the 'directedReadable' function makes it more readable
  functions.eval_expression.dpdencies +=  [ directedReadable('<',inputs.expression) ]
  #or better alias 'directed' in plugin_manifest package
  functions.eval_expression.dpdencies +=  [ directed('<',inputs.expression) ]
  #is the same as
  functions.eval_expression.dpdencies +=  [ inputs.expression.directed('<') ]
  #or as
  functions.eval_expression.dpdencies +=  [ DirectionQualifier(inputs.expression, '<') ]
  #With the alias you can clearly understand the direction of the connection

  #Validation only for the connection
  functions.eval_expression.dpdencies +=  [ inputs.scalar_number.validateDefault('%s > 1',2) ]

Note that when you qualify in the connection, the qualification won't last in the property.
But when you qualify in initialization, you qualify the property for any future
 connection. (you may get the inner property with the __qualified__() method.

This is the class Hierarchy for Qualifiers:
  PropertyAndQualifierBase
    QualifierBase
      DirectionQualifier
      ValidationQualifier

The hierarchy of Properties Proxies:
  PropertyAndQualifierBase
    PropertyProxy
      FunctionPropertyProxy    (functions declarationOrder)
      InOutPropertyProxyBase   (declarationOrder carrying information)
        FunctumPropertyProxy   (property carrying information and other declarationOrder: functum = function + datum)
        DataPropertyProxy      (pure data property)
          InotifyPropertyProxy (The property receives signals from inotify, probably related to a File or Folder)
          GenericEnumProxy     (data property implementing a generic enum data type)

'''

from common.abstract.FrameworkObject import FrameworkObject
from common.type_checking.isiterable import isiterable


class PropertyAndQualifierBase(FrameworkObject):
    pass


class QualifierBase(PropertyAndQualifierBase):

    def __init__(self, wrapped_prop):
        self.wrapped_prop = wrapped_prop

    def __qualified__(self):
        return self.wrapped_prop.__qualified__()

    def hasQualifier(self, name):
        return hasattr(self, name.lower())

    def _interceptedAttr(self):
        '''
          Reimplement this method on children classes to intercept more attributes.
            Remember adding the _interceptedAttr() result from the parent class.
          Example on children: (suppose adding 'direction' attribute to the children class).
            def _interceptedAttr(self):
              return ['direction'] + QualifierBase._interceptedAttr(self)
        '''
        return ['wrapped_prop']

    def __getattr__(self, name):
        '''
          Intercept attributes from this class and child classes.
            (who should re-implement _interceptAttr).
        '''
        if name == '_interceptedAttr' or name in self._interceptedAttr():
            return object.__getattribute__(self, name)
        else:
            return PropertyProxy.__getattribute__(self.wrapped_prop, name)

    def __eq__(self, other):
        '''
          When comparing (for declarationOrder for example), use the real property without qualifications.
        '''
        return self.__qualified__() == other.__qualified__()

    def __str__(self):
        return str(self.__qualified__())

    def __repr__(self):
        return '<%s wrapping %r>' % (self.__class__.__name__, self.wrapped_prop)


class DirectionQualifier(QualifierBase):

    def __init__(self, wrapped_prop, direction):
        QualifierBase.__init__(self, wrapped_prop)
        if direction not in ['<', '>']:
            raise RuntimeError(
                "Direction parameter should be '<' or '>'. %r is not supported." % direction)
        self.direction = direction

    def _interceptedAttr(self):
        return ['direction'] + QualifierBase._interceptedAttr(self)


class ValidationQualifier(QualifierBase):

    class Validation(FrameworkObject):

        def __init__(self, expression, default_value=None):
            self.expression = expression
            self.default_value = default_value

        def isValidateDefault(self):
            return self.defaul_value != None

        def isValidateReturn(self):
            return self.defaul_value == None

    def __init__(self, wrapped_prop, expression, default_value):
        QualifierBase.__init__(self, wrapped_prop)
        self.validation = self.Validation(expression, default_value)

    def _interceptedAttr(self):
        return ['validation'] + QualifierBase._interceptedAttr(self)


def directedReadable(direction, wrapped_prop):
    '''
      Better direction qualifier alias (easier to read)
      This alias is used to wrap a property in order to set its connection
      direction.
      It's used when assigning the dependencies, for example:
        functions.onEvaluation.dpdencies = +[ directed('<',inputs.number),
                                               directed('>',inputs.text),
                                               inputs.mesh,
                                             ]
      In this example:
        - 'number': will only propagate changes to 'onEvaluation',
          it won't be evaluated from 'onEvaluation' function and
          won't be included on the function's args
        - 'text': will be included in the args of 'onEvaluation',
          but won't propagate changes to 'onEvaluation'
        - 'mesh': will propagate changes and be included in the function's args.
      Use the 'directed' function of the plugins_manifest package to set the
      direction.
    '''
    return DirectionQualifier(wrapped_prop, direction)


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
        if isiterable(added_dpdencies):
            for dency in added_dpdencies:
                self.appendDependency(dency)
        else:
            self.appendDependency(added_dpdencies)
        return self

    def __iter__(self):
        return self.__props.__iter__()

    def appendDependency(self, dency):
        if dency in self.__props:
            raise RuntimeError('Dependency %r already in this Property\'s '
                               'dependencies.' % dency)
        elif isinstance(dency, (PropertyProxy, QualifierBase)):
            self.__props.append(dency)
        else:
            raise RuntimeError('Unsupported dependency type for %r. Dependencies '
                               'should be a list of PropertyProxy or a PropertyProxy.'
                               % dency)


class PropertyProxy(PropertyAndQualifierBase):

    '''
      Property proxy is a generic proxy used to define a plugin's manifest.
      But you should use concrete classes 'DataProperty','FunctionProperty'
      from mepinta.plugins_manifest package
    '''

    def __init__(self):
        self.property_id = None
        # by default the connection is bidirectional. This may be overrided by
        # wrapping it in a Directed
        self.direction = '<>'
        # TODO: check that a property is not added twice, or two
        # declarationOrder with the same name
        self.__dpdencies = PropertyDepedencies()
        self.name = None
        # self.parent = None #later we need to know who this property belongs
        # to? #TODO: remove?

    def __qualified__(self):
        return self

    def __wrapped_lo__(self):
        if self.property_id != None:
            return self.property_id
        else:
            raise RuntimeError(
                'Property: %s has no property_id defined' % self.name)

    def variableString(self):
        return self.name

    def __str__(self):
        return self.name

    def __repr__(self):
        return '<%s %r %s>' % (self.__class__.__name__, self.name, FrameworkObject.__repr__(self))

    # Properties
    def getDpdencies(self):
        '''You can get dpdencies, but never set it. Always add or remove
        declarationOrder from the list.'''
        return self.__dpdencies

    def setDpdencies(self, value):
        if self.__dpdencies != value:
            raise RuntimeError('Trying to change %r property\'s dpdencies object. '
                               'You should use the += operator instead.' % str(self))
    dpdencies = property(getDpdencies, setDpdencies, None, None)


class InOutPropertyProxyBase(PropertyProxy):

    def __init__(self, data_type_alias, data_type_version=1):
        PropertyProxy.__init__(self)
        self.data_type_name = None
        self.data_type_alias = data_type_alias
        self.data_type_version = data_type_version
        # On a concrete property
        #self.dtype_id = None

    def getDataTypeShortName(self):
        return self.data_type_name.split('.')[-1]

    def directed(self, direction):
        '''
          if direction='>' means other property depends on this property in the
            relation.(but is not notified)
          if direction='<' means this property notifies changes to the other
            property in the relation.(but won't be in it's args)
        '''
        return DirectionQualifier(self, direction)


class DataPropertyProxy(InOutPropertyProxyBase):

    '''
      Class used by a plugin's manifest
        You should use alias 'DataProperty'
        from mepinta.plugins_manifest package
    '''

    def validateDefault(self, expression, default_value):
        return ValidationQualifier(self, expression, default_value)

    def validateReturn(self, expression):
        return ValidationQualifier(self, expression, None)


class InotifyPropertyProxy(DataPropertyProxy):

    '''
    This class is just used to clasify those properties that represent a path in
    the system. So they can be watched by Inotify.
    '''
# def getPath(self, pline, context): #TODO: remove
#    '''
#    getPath makes room for any InotifyPropertyProxy to solve the path to be
#      watched by inotify. The property may have more than just the string of the
#      path. getPath can filter just the path.
#    :param pline:
#    :param context:
#    '''
#    raise RuntimeError('Implement on child class. (could be on concrete class %s)' % self.__class__)


class InputFilePropertyProxy(InotifyPropertyProxy):

    '''
    A default implementation for a input file path. Will be watched by Inotify.
    '''

    def __init__(self):
        InotifyPropertyProxy.__init__(self, 'c.builtin.charp')


class GenericEnumProxy(DataPropertyProxy):

    '''
      Class used by a plugin's manifest
        You should use alias 'GenericEnum'
        from mepinta.plugins_manifest package
    '''

    def __init__(self, **enum_dict):
        DataPropertyProxy.__init__(
            self, 'MP_generic_enum', data_type_version=1)
        self.__validateEnumDict(enum_dict)
        self.enum_dict = enum_dict
        # the smallest value is the first default. Later can be changed with
        # the 'setDefault' method.
        self.default_value = sorted(self.enum_dict.values())[0]
        self.enum_id = None

    def invertedDict(self):
        return dict((value, label) for label, value in self.enum_dict.items())

    def __validateEnumDict(self, enum_dict):
        if len(enum_dict) == 0:
            raise RuntimeError(
                'At least you should provide one label=value pair.')
        for value in enum_dict.values():
            if not isinstance(value, int):
                raise RuntimeError('For a GenericEnum you must supply a label=value '
                                   'dictionary. Where value is of int type.')
        if len(set(enum_dict.values())) != len(enum_dict):
            raise RuntimeError('For a GenericEnum you must supply a label=value '
                               'dictionary. All values must differ.')

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
            raise RuntimeError('Default value %r was not defined for this enum %r' %
                               (value, self.enum_dict))
        return self
    # Properties

    def getEnumId(self):
        if self.__enum_id == None:
            raise RuntimeError('A enum property_id must be set from the '
                               'PropertyProxyContainer class.')
        return self.__enum_id

    def setEnumId(self, value):
        self.__enum_id = value
    enum_id = property(getEnumId, setEnumId, None, None)


class FunctumPropertyProxy(InOutPropertyProxyBase):

    '''
      Class used by a plugin's manifest
        You should use alias 'FunctumProperty'
        from mepinta.plugins_manifest package
    '''

    def __init__(self):
        InOutPropertyProxyBase.__init__(self, 'functum', data_type_version=1)


class FunctionPropertyProxy(PropertyProxy):

    '''
      Class used by a plugin's manifest
        You should use alias 'FunctionProperty'
        from mepinta.plugins_manifest package
    '''
    pass

if __name__ == '__main__':
    # TODO: review this
    from getDefaultContext import getDefaultContext
    context = getDefaultContext
    #  def test():
    #    prop1 = DataPropertyProxy('charp', '10_v10')
    # TODO: check out that user defined versions should compare correctly
    #    prop2 = DataPropertyProxy('charp', 1)
    #    fprop1 = FunctionPropertyProxy()
    #    container = PropertyProxyContainer()
    #    container.containerType = 'input'
    #    container.count = DataPropertyProxy('int')
    #    container.expression = DataPropertyProxy('charp')
    #    container.operation = FunctionPropertyProxy()
    #    debugPrint (container.getProperties())
    #
    #  test()
    #
    #  def getProcessorProxy(context):
    #    pp = ProcessorProxy('ScalarExpression')
    # Inputs
    #    pp.inputs.expression = DataPropertyProxy('charp', 1)
    #    pp.inputs.scalar_number = DataPropertyProxy('double', 1)
    #    pp.inputs.scalar_number_name = DataPropertyProxy('charp', 1)
    #    pp.inputs.count = 'k3d::int32_t'
    # Internal values
    #    pp.internals.variables_count = DataPropertyProxy('uint', 1)
    #    pp.internals.parser = DataPropertyProxy('internal_any', 1)
    # Output result
    #    pp.outputs.scalar_number = DataPropertyProxy('double', 1)
    # Functions
    #    pp.functions.eval_expression = FunctionPropertyProxy()
    #    pp.functions.parse_expression = FunctionPropertyProxy()
    #
    # Set dependencies
    #    pp.functions.parse_expression.dpdencies += [ pp.inputs.expression
    #                                                 , pp.inputs.scalar_number_name
    #                                                 , pp.inputs.count
    #                                                 ]
    #    pp.internals.parser.dpdencies += [ pp.functions.parse_expression ]
    #    pp.internals.variables_count.dpdencies += [ pp.functions.parse_expression ]
    #
    #    pp.functions.eval_expression.dpdencies += [ directedReadable('<', pp.inputs.scalar_number)
    #                                                , pp.internals.parser
    #                                                , pp.internals.variables_count
    #                                                 ]
    #    pp.outputs.scalar_number.dpdencies += [ pp.functions.eval_expression ]
    #
    # pp.outputs.scalar_number.dpdencies = []
    #
    #    return pp
    #
    #  pp = getProcessorProxy(context)
    #
    #  def print_processor_definition(context, pp):
    #    for cont_name, props in pp.containers.items():
    #      context.log.info("Container %r" % cont_name)
    #      props_dict = props.getProperties()
    #      for name in props.declarationOrder:
    #        if name in props_dict:
    #          prop = props_dict[name]
    #          if isinstance(prop, InOutPropertyProxyBase):
    #            context.log.info('  %r type:%r data_type_name:%r' % (name, prop.type, prop.data_type_name))
    #          else:
    #            context.log.info('  %r type:%r ' % (name, prop.type))
    #
    #  print_processor_definition(context, pp)
    #
    #  def test_qualifiers():
    #    qualified = DirectionQualifier(pp.inputs.expression, '<')
    #    qualified1 = qualified
    #    debugPrint qualified
    # qualified = DataPropertyProxy('name')
    #    debugPrint qualified.direction
    #    debugPrint qualified.name
    #    debugPrint qualified.data_type_name
    #    debugPrint qualified.hasQualifier('direction')
    # qualified = ValidationQualifier(qualified, '#prop > 1', 2)
    #    debugPrint qualified.hasQualifier('Validation')
    #    debugPrint qualified == pp.inputs.expression
    #    debugPrint qualified == qualified1
    #    debugPrint qualified == pp.inputs.scalar_number
    #    qualified2 = DirectionQualifier(pp.inputs.scalar_number, '<')
    #    debugPrint qualified == qualified2
    #    debugPrint qualified2 == pp.inputs.scalar_number
    #    debugPrint pp.inputs.expression.directed('<')
    #    debugPrint qualified == pp.inputs.expression.directed('<')
    # debugPrint qualified2 == pp.inputs.scalar_number.validateDefault('#prop < 1', 0).directed('<')
    # debugPrint qualified2 == directedReadable('<', pp.inputs.scalar_number.validateDefault('#prop < 1', 0))
    #    debugPrint repr(qualified)
    # debugPrint repr(directedReadable('<', pp.inputs.scalar_number.validateDefault('#prop < 1', 0)))
    #
    #  test_qualifiers()
