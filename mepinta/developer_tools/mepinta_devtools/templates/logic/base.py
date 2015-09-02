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
from mepinta.abstract.MepintaError import MepintaError
from common.abstract.FrameworkObject import FrameworkObject
from common.python3 import portableGetArgspec


class on_template_decorator(object):

    '''Decorates methods corresponding to a template variable.'''

    def __init__(self, method):
        '''Stores the decorated method for later use.'''
        self.method = method

    def __call__(self, *a, **ad):
        '''Calls stored method.'''
        portableGetArgspec(self.method)
        return self.method(*a, **ad)
# Nice Alias
on_template = on_template_decorator


class TemplateLogicBase(FrameworkObject):

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
    _file_ext = ''  # Specify file extensions in intermediate child

    def getFileName(self):
        if self._file_ext != '':
            file_ext = self._file_ext.lower()
            class_name = self.__class__.__name___.lower()
            if class_name.endswith(file_ext):
                return "%s.%s" % (class_name[:-len(file_ext)], file_ext)
        else:
            raise MepintaError('Cannot build file name. File extensio %r and class %r' % (
                self._file_ext, self.__class__.__name___))

    def getTranslationDict(self, config_dict):
        translation_dict = {}
        for name, method in inspect.getmembers(self):
            if isinstance(method, on_template_decorator):
                translation_dict[name] = method(self, config_dict)
        return translation_dict
