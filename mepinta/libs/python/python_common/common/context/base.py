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
from common.log.Logger import Logger
from common.context.data_model import TreeContextStore, BaseNode

class ContextBase(TreeContextStore):
  def __init__(self, arg):
    if isinstance(arg, str):
      name = arg
      TreeContextStore.__init__(self)
      #self.updateConfig(ConfigLoader().load(name))
      self._setDefaultConfig(name)
      self.setConfig('name', name)
      self.setConfig('log', Logger())
    elif isinstance(arg, BaseNode):
      config_tree_node = arg
      TreeContextStore.__init__(self, config_tree_node)

  def _getMepintaConfig(self, name):
    from mepinta_config import mepinta_config
    settings = mepinta_config(name)
    return settings

  def _setDefaultConfig(self, name):
    settings = self._getMepintaConfig(name)
    for name in dir(settings):
      if not name.startswith('_'):
        self.setConfig(name, getattr(settings, name))
    config_dict = settings._config_dict
    for name, owner in config_dict:
      self.setConfig(name, config_dict[(name, owner)], owner)

def smokeTestModule():
  context = ContextBase('python')
  from common.log.debugPrint import debugPrint
  pprint = debugPrint
  pprint(context.getConfig('backend_name'))
  pprint(context.getConfig('plugin_build_targets'))
  pprint(context.getConfigDict())


if __name__ == "__main__":
  smokeTestModule()
