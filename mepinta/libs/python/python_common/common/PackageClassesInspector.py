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
from inspect import isclass


class PackageClassesInspector(FrameworkBase):
  def getChildModules(self, package):
    return self._gatherModules(package)

  def builDict(self, package, class_type, one_per_module=True):
    modules = self._gatherModules(package)
    modules_dict = {}
    for module in modules:
      classes = self._filterModule(module, class_type)
      if one_per_module:
        if len(classes):
          modules_dict[module] = classes[0]
#        else:
#          print module
      else:
        modules_dict[module] = classes
    return modules_dict

  def _filterModule(self, module, class_type):
    classes = []
    for class_ in module.__dict__.values():
      if isclass(class_) and \
      issubclass(class_, class_type):
        classes.append(class_)
    return classes

  def _gatherModules(self, package):
    modules = []
    prefix = package.__name__ + "."
    for _, modname, ispkg in pkgutil.iter_modules(package.__path__, prefix):
      if not ispkg:
        module = __import__(modname, fromlist="dummy")
        modules.append(module)
      else:
        package = __import__(modname, fromlist="dummy")
        modules += self._gatherModules(package)
    return modules

def smokeTestModule():
  raise RuntimeWarning('No smoke test')

if __name__ == "__main__":
  smokeTestModule()
