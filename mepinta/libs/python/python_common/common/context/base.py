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
from common.config.ConfigFactory import ConfigLoader
from common.log.Logger import Logger
from common.context.data_model import TreeContextStore, BaseNode

class ContextBase(TreeContextStore):
  def __init__(self, arg):
    if isinstance(arg, str):
      name = arg
      TreeContextStore.__init__(self)
      self.updateConfig(ConfigLoader().load(name))
      self.setConfig('name', name)
      self.setConfig('log', Logger())
    elif isinstance(arg, BaseNode):
      config_tree_node = arg
      TreeContextStore.__init__(self, config_tree_node)

def smokeTestModule():
  raise RuntimeWarning('No smoke test')

if __name__ == "__main__":
  smokeTestModule()
