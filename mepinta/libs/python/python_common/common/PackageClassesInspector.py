# -*- coding: utf-8 -*-
'''
Copyright (c) 2013, Joaquin G. Duo
Copyright (c) 2012-2013, LastSeal S.A.

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
import pkgutil
from importlib import import_module

class PackageClassesInspector(FrameworkBase):
  def getChildModules(self, package):
    return self.gatherModules(package)

  def builDict(self, package, filter_func, reload_=True):
    modules = self.gatherModules(package, reload_)
    modules_dict = {}
    for module in modules:
      filtered = self._filterModule(module, filter_func)
      modules_dict[module] = filtered
    return modules_dict

  def _filterModule(self, module, filter_func):
    classes = []
    for obj in module.__dict__.values():
      if filter_func(obj, module):
        classes.append(obj)
    return classes

  def gatherModules(self, package, reload_):
    prefix = package.__name__ + '.'
    for _, modname, ispkg in pkgutil.walk_packages(package.__path__, prefix):
      if not ispkg:
        module = import_module(modname)
        if reload_:
          module = reload(module)
        yield module

def smokeTestModule():
  raise RuntimeWarning('No smoke test')

if __name__ == "__main__":
  smokeTestModule()
