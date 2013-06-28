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
from common.context.data_model import TreeContextStore, CommonNode

class ContextBase(TreeContextStore):
  def __init__(self, arg):
    if isinstance(arg, str):
      name = arg
      TreeContextStore.__init__(self)
      self.updateConfig(ConfigLoader().load(name))
      self.setConfig('name', name)
      self.setConfig('log', Logger())
    elif isinstance(arg, CommonNode):
      config_tree_node = arg
      TreeContextStore.__init__(self, config_tree_node)

def test_module():
  pass
  #TODO: clean?
#  from common.decorator.args_singleton import args_singleton
#  @args_singleton
#  class Context(ContextBase):
#    pass
#  from common.config.ContextWrapper import ContextWrapper
#  ctxp = Context('python')
#  ctxp2 = Context('python')
#  ctxp3 = Context('python')
#  ctxc = Context('c_and_cpp')
#  debugPrint (ctxp)
#  debugPrint (ctxp2)
#  debugPrint (ctxp3)
#  class Pototo:
#    pass
#  a = Pototo()
#  from common.config.SelfConfigWrapper import SelfConfigWrapper
#  cwrapper = SelfConfigWrapper(OwnerClass=a.__class__, context=ctxp)
#  cwrapper.hola = 1
#  debugPrint(cwrapper.hola)
#  try:
#    debugPrint(cwrapper.hola1)
#  except Exception as e:
#    debugPrint(e)
#  debugPrint (ctxp)
#  cwrapper = ContextWrapper(context=ctxp)
#  cwrapper.hola = 1
#  child = cwrapper.newChildConfig()
#  debugPrint (ctxp)
#  debugPrint (cwrapper.backend_name)


if __name__ == "__main__":
  test_module()
