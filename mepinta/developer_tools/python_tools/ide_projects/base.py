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
from mepinta.plugins_creation.templates.base import MethodPerTemplateVar, \
  ProjectTemplatesBase
from common.path import joinPath
from mepinta.plugins_creation.base import GenericProjectCreatorBase

class ConfigDictProjectCreatorBase(GenericProjectCreatorBase):
  def _getTargetPath(self, eclipse_root):
    '''Get the path of the created project.'''
    raise NotImplementedError('Implement')

class ConfigDictTemplateProcessorBase(MethodPerTemplateVar):
  def __post_init__(self, config_dict):
    self.config_dict = config_dict

class ConfigDictProjectTemplatesBase(ProjectTemplatesBase):
  def __post_init__(self, config_dict):
    self.config_dict = config_dict
  def _initTemplateProcessor(self, template_processor, templates_root, path):
    return template_processor(context=self.context, path=joinPath(templates_root, path), config_dict=self.config_dict)

if __name__ == "__main__":
  pass
