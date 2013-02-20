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
from common.abstract.FrameworkObject import FrameworkObject

class FileToFileMap(FrameworkObject):
  def __init__(self, template_logic, template_path, dst_path, overwrite=False, repo_package=None, template_set=None):
    self.template_logic = template_logic
    self.template_path = template_path
    self.dst_path = dst_path
    self.overwrite = overwrite
    self.repo_package = repo_package
    self.template_set = template_set
  def setRepoPackageAndTemplateSet(self, repo_package, template_set):
    if self.repo_package == None:
      self.repo_package = repo_package
    if self.template_set == None:
      self.template_set = template_set


class StrToFileMap(FrameworkObject):
  def __init__(self, template_logic, template, dst_path, overwrite=False):
    self.template_logic = template_logic
    self.template = template
    self.dst_path = dst_path
    self.overwrite = overwrite

def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  test_module()
