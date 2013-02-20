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
import inspect
from common.abstract.FrameworkBase import FrameworkBase

class on_template_decorator(object):
  '''Decorates methods corresponding to a template variable.'''
  def __init__(self, method):
    '''Stores the decorated method for later use.'''
    self.method = method
  def __call__(self, *a, **ad):
    '''Calls stored method.'''
    return self.method(*a, **ad)
# Nice Alias
on_template = on_template_decorator

class TemplateLogicBase(FrameworkBase):
  '''
    A file based template.
    Also classes inheriting this class, will implement a method (decorated)
      for each variable inside the template.
    Then other class can ask for the translation with calling the method
      _getTranslationDict()

    Example:
    class Foo(MethodPerTemplateVar):
      @on_template
      def templateVariable(self):
        return 'Bar'

    getTranslationDict() will return {'templateVariable':'Bar'}
  '''
  def getTranslationDict(self, config_dict):
    translation_dict = {}
    for name, method in inspect.getmembers(self):
      if isinstance(method, on_template_decorator):
        self.context.log.debug('Calling %r decorated template method.' % name)
        translation_dict[name] = method(self, config_dict)
    return translation_dict


