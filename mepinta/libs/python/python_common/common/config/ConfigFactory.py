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

class ModuleDummy:
  class config_base(dict):
    def __init__(self):
      self[("global", 'backend_name')] = str(self.__class__.__name__)[len('config_'):]
      self[("global", 'minor_version_separator')] = '__'
      self[("global", 'plugin_build_targets')] = ['Debug', 'Release', 'ReleasePointerSafe', 'ReleaseTypeSafe', 'ReleaseArgumentsSafe', ]
      self[("global", 'nodebox_gui')] = True

  class config_python(config_base):
    pass
  class config_c_and_cpp(config_base):
    pass

class ConfigLoader(object):
  # TODO copy and deepcopy
  __configs = {}
  # __default_config = 'python'
  def load(self, config_name):
    if config_name in  self.__configs:
      return self.__configs[config_name]
    else:
      if hasattr(ModuleDummy, 'config_%s' % config_name):
        self.__configs[config_name] = getattr(ModuleDummy, 'config_%s' % config_name)()
        return self.__configs[config_name]
      else:
        raise RuntimeError('Non existing config %r' % config_name)
        # return self.load(self.__default_config)
