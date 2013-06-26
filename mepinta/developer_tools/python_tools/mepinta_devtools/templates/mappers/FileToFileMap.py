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
from mepinta_devtools.templates.mappers.base import MapperBase
from mepinta_devtools.templates.logic.base import TemplateLogicBase
from mepinta.abstract.MepintaError import MepintaError
from common.path import getPackagePath, joinPath, splitPath, getObjectModulePath
from mepinta_devtools.templates.FileBasedTemplate import FileBasedTemplate

class FileToFileMap(MapperBase):
  def __init__(self, template, dst_path, overwrite=False, repo_package=None, template_set=None):
    if isinstance(template, TemplateLogicBase):
      self.template_logic = template
    elif isinstance(template, str):
      self.template_logic = None
      self.__template_path = template
    else:
      raise MepintaError('Template %r of invalid type (should be str or TemplateLogicBase).' % template)
    self.dst_path = dst_path
    self.overwrite = overwrite
    self.repo_package = repo_package
    self.template_set = template_set

  def setRepoPackageAndTemplateSet(self, repo_package, template_set):
    if self.repo_package == None:
      self.repo_package = repo_package
    if self.template_set == None:
      self.template_set = template_set

  def _getAbsolutSrcFilePath(self, file_path):
    return joinPath(splitPath(getPackagePath(self.repo_package)) + [self.template_set, file_path])

  def getTemplatePath(self):
    if self.repo_package == None or self.template_set == None:
        raise MepintaError('For %r repo_package or template_set wasn\'t set' % self)
    else:
      if self.template_logic == None:
        return self._getAbsolutSrcFilePath(self.__template_path)
      else:
        file_dir = splitPath(getObjectModulePath(self.template_logic))[:-1]
        return joinPath(file_dir, self.template_logic.getFileName())

  def getTemplate(self):
    return str(FileBasedTemplate(self.getTemplatePath()))

  template_path = property(getTemplatePath, None, None, None)
  template = property(getTemplate, None, None, None)

def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  testModule()
