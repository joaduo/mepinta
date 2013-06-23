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
from mepinta.context.MepintaContext import MepintaContext
from common.abstract.FrameworkBase import FrameworkBase
from ModuleCreator import ModuleCreator
import os
from common.path import joinPath

class PackageCreator(FrameworkBase):
  def __post_init__(self):
    self.module_creator = ModuleCreator(context=self.context)
  def validatePackagePath(self, type_, package_path):
    pass
  def create(self, split_path):
    full_path = joinPath(split_path)
    self.log.verbose('Creating package in: %r'%full_path)
    os.makedirs(full_path)
    for index in range(len(split_path)-1):
      init_file = joinPath(split_path[:len(split_path)-index] +
                              ['__init__.py'])
      self.log.debug('Checking %r'%(init_file))
      if os.access(init_file,os.R_OK):
        break
      else:
        self.module_creator.create(init_file)

if __name__ == "__main__":
  debugPrint FrameworkBase
  context = MepintaContext('python')
  pc = PackageCreator(context=context)
