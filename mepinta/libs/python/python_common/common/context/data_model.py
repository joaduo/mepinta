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
import inspect
from common.config.constants import global_config_namespace

class BaseNode(object):
  def __init__(self):
    self._config = dict()
    self._childs = set()

  @property
  def config(self): #can only get the attribute
    return self._config

  def hasConfig(self, key):
    return key in self._config

  def getConfig(self, key):
    if key in self._config:
      return self._config[key]
    else:
      raise KeyError('No config for key %r.' % str(key))

  def setConfig(self, key, value):
    self._config[key] = value

  def updateConfig(self, update_dict):
    self._config.update(update_dict)

  def newChild(self):
    node = ChildNode(parent=self)
    self._childs.add(node)
    return node

  def getConfigDict(self):
    return dict(self._config)

class ChildNode(BaseNode):
  def __init__(self, parent):
    self.__parent = parent
    BaseNode.__init__(self)

  def hasConfig(self, key):
    return key in self._config or self.__parent.hasConfig(key)

  def getConfig(self, key):
    if key in self._config:
      return self._config[key]
    else:
      return self.__parent.getConfig(key)

class TreeContextStore(object):
  def __init__(self, config_tree_node=None):
    #Set default values for new configstore
    if not config_tree_node:
      self._root_node = BaseNode()
    else:
      self._root_node = config_tree_node

  def getConfigDict(self):
    return self._root_node.getConfigDict()

  def newChildConfig(self, **kwargs):
    copy = self.__class__(self._root_node.newChild())
    copy.updateConfig(kwargs)
    return copy

  def updateConfig(self, update_dict):
    self._root_node.updateConfig(update_dict)

  def hasConfig(self, name, owner=global_config_namespace):
    return self._root_node.hasConfig(self.__getConfigKey(name, owner))

  def getConfig(self, name, owner=global_config_namespace):
    return self._root_node.getConfig(self.__getConfigKey(name, owner))

  def setConfig(self, name, value, owner=global_config_namespace):
    key = self.__getConfigKey(name, owner)
    self._root_node.setConfig(key, value)

  def __getConfigKey(self, name, owner=global_config_namespace):
    return (self.__getOwnerStr(owner), name)

  def __getOwnerStr(self, owner):
    if inspect.isclass(owner):
      owner_str = "class::%s.%s" % (owner.__module__.__str__(),
                    owner.__name__)
    elif isinstance(owner, str):
      owner_str = owner
    else:#TODO: debugPrint warning!!
      self.getConfig('log').w('owner (%r) should be a class or a string, type'
                              ' is %r' % (owner, type(owner)))
      owner_str = "%s" % owner
    return owner_str

def smokeTestModule():
  from common.log.debugPrint import debugPrint
  p = debugPrint
  def assertAndPrint(gc, name, owner, value):
    p(gc.getConfig(name, owner))
    assert(gc.getConfig(name, owner) == value)
  gc = TreeContextStore()
  gc.setConfig('hello', 10, owner='yo')
  gc.setConfig('hello2', 12, owner='yo')
  p(gc.getConfig('hello', owner='yo'))
  assert(gc.getConfig('hello', owner='yo') == 10)
  gc1 = gc.newChildConfig()
  gc1.setConfig('hello', 11, owner='yo')
  p(gc1.getConfig('hello', owner='yo'))
  assert(gc1.getConfig('hello', owner='yo') == 11)
  p(gc.getConfig('hello', owner='yo'))
  p(gc1.getConfig('hello2', owner='yo'))
  gc.setConfig('hello3', 13, owner='yo')
  p(gc1.getConfig('hello3', owner='yo'))

if __name__ == "__main__":
  smokeTestModule()
