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

import re
import inspect
from common.abstract.FrameworkBase import FrameworkBase
from common.path import joinPath, splitPath
from mepinta.plugins_manifest.proxy.data_model import DataPropertyProxy, \
  FunctumPropertyProxy

# TODO: renaming, moving and documenting. UGLY!

class TemplateTranslatorBase(FrameworkBase):
#  def __post_init__(self, template_config):
#    self.template_config = template_config
  def getContent(self):
    '''Implement this method to create a Translator.'''
    raise RuntimeError('Implement method.')
  def __str__(self):
    '''Use the str operator to mimic a string.'''
    return self.getContent()
  def __call__(self, *a, **ad):
    self.context.log.debug('If you are calling this methos, probably you may want to reimplement it on the children class.')
    return self
  def getOverwritePolicy(self):
    '''Default overwrite policy.'''
    return False

class FileBasedTemplate(TemplateTranslatorBase):
  '''
    Template based on file. Will be translated by a dictionary
      in an Child class or on other translator.
  '''
  def __post_init__(self, path):
    self.path = path
  def getContent(self):
    template_file = open(self.path, 'r')
    template = template_file.read()
    template_file.close()
    return template

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

class MethodPerTemplateVar(FileBasedTemplate):
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

    _getTranslationDict() will return {'templateVariable':'Bar'}
  '''
  def _getTranslationDict(self):
    translation_dict = {}
    for name, attr in inspect.getmembers(self):
      if isinstance(attr, on_template_decorator):
        self.context.log.debug('Calling %r decorated template method.' % name)
        translation_dict[name] = attr(self)
    return translation_dict

class ManifestAndFileTemplateBase(MethodPerTemplateVar):
  '''
    A FileBased template that stores a plugin_manifest.
    It implements a method for each variable on the template.
  '''
  def __post_init__(self, plugin_manifest):
    self.plugin_manifest = plugin_manifest
  def _requiredDataTypes(self):
    required_data_types = self.plugin_manifest.getRequiredDataTypes(types_classes=[DataPropertyProxy, FunctumPropertyProxy])
    self.context.log('Using data type minor version from eclipse projects.')
    return required_data_types.keys()
  def getTemplateStr(self):
    return FileBasedTemplate.getContent(self)
  def getContent(self):
    template = self.getTemplateStr()
    translation_dict = self._getTranslationDict()
    content = str(DictionaryBasedTranslator(self.context, template=template, translation_dict=translation_dict))
    return content
  def __call__(self, context, plugin_manifest, path):
    self.path = path
    self.plugin_manifest = plugin_manifest
    return self

class DictionaryBasedTranslator(TemplateTranslatorBase):
  ''''''
  def __post_init__(self, template, translation_dict, start_mark='##'):
    self.template = template
    self.translation_dict = translation_dict
    self.start_mark = start_mark
  def __replace(self, processed_template, name, replacement, start_mark):
    re_replace = re.compile(r'%s%s' % (start_mark, name))
    if not isinstance(replacement, str):
      raise RuntimeError('replacement %r for %r variable should be a string.' % (replacement, name))
    return re_replace.sub(replacement, processed_template)
  def getContent(self):
    processed_template = str(self.template)
    for name, replacement in self.translation_dict.items():
      processed_template = self.__replace(processed_template, name, replacement, self.start_mark)
    return processed_template

class ProjectTemplatesBase(FrameworkBase):
#  def getCreatedDirs(self, plugin_manifest, target_root): #TODO: remove
#    raise NotImplementedError('Implement in children!')
  def _getTemplatesRoot(self):
    '''
      Implementation Example:
        import plugins_creation.templates.c_and_cpp.processor_plugin as processor_plugin
        return joinPath(processor_plugin.__path__[0],'repository')
    '''
    raise NotImplementedError('Implement in children!')
  def _getMapDict(self, **kwargs):
    '''
    Implementation Example:
      return {
              (DeclarationH,'src/properties/declaration.h'):None,
              (WrappersH,'src/properties/wrappers.h'):None,
              (ProcessorCPP,'src/processor.cpp'):'src/%s.cpp'%plugin_name,
             }
    '''
    raise NotImplementedError('Implement in children!')
  def _buildTemplateRoot(self, package, path_list):
    '''
      Builds the templates root given a package a and a path list relative to that package.
      (get the full path given a package)
    '''
    return joinPath(splitPath(package.__path__[0]) + path_list)

  def getTemplatePerPath(self, target_root, **kwargs):
    '''
      Given a plugin manifest and a target root path for a Eclipse project
      returns the map of the Template translator and their target files.
    '''
    templates_root = self._getTemplatesRoot()
    map_dict = self._getMapDict(**kwargs)
    return self._convertToAbsolutPaths(map_dict, target_root, templates_root, **kwargs)
  def _convertToAbsolutPaths(self, map_dict, target_root, templates_root, **kwargs):
    '''
      Convert given relative paths and roots to their absolut path.
      Also it creates the Template classes to be used on the translation.
    '''
    templates_root = self._getTemplatesRoot()
    map_dict_absolut = {}
    for template_config, target_subpath in map_dict.items():
      template_processor, path = template_config
      if target_subpath == None:
        target_subpath = path
      template = self._initTemplateProcessor(template_processor, templates_root, path, **kwargs)
      map_dict_absolut[template] = joinPath(target_root, target_subpath)
    return map_dict_absolut
  def _initTemplateProcessor(self, template_processor, templates_root, path, **kwargs):
    return template_processor(context=self.context, path=joinPath(templates_root, path))


class PluginTemplatesBase(ProjectTemplatesBase):  # TODO: rename to ProjectTemplatesBase
  '''
    Base class for Templates per Path classes.
  '''
  def _initTemplateProcessor(self, template_processor, templates_root, path, plugin_manifest):
    return template_processor(context=self.context, plugin_manifest=plugin_manifest, path=joinPath(templates_root, path))

if __name__ == "__main__":
  from mepinta.context.MepintaContext import MepintaContext
  context = MepintaContext('python')
  template = '< ##FOO > < ##BAR>'
  translation_dict = {'FOO':'value=10', 'BAR':'other="some"'}
  print(DictionaryBasedTranslator(context, template=template, translation_dict=translation_dict))

