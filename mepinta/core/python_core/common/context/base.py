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

    '''
    Implements a "encapsulated context pattern".
    All FrameworkBase children will generally need a context as first argument.

    This context enables:
      - Context storage of shared configuration among classes
      - Ability to fork a context into a new one and inherit non overridden
        configuration. (creating a tree of inheritance between contexts, check
        :class:`common.context.data_model.TreeContextStore`)
    '''

    def __init__(self, arg):
        '''
        If arg is a string, creates a new Context.
        If arg is a Context instance, creates of fork of that context (WIP)

        :param arg: a string with the name of the context or an instances of
          :class:`common.context.data_model.BaseNode`
        '''
        if isinstance(arg, str):
            name = arg
            TreeContextStore.__init__(self)
            self.setConfig('name', name)
            self.setConfig('log', Logger())
            self._setDefaultConfig(name)

        elif isinstance(arg, BaseNode):
            config_tree_node = arg
            TreeContextStore.__init__(self, config_tree_node)

    def _getDefaultConfig(self, name):
        '''
        Function to be overridden in child classes in order to obtain configuration
        from anywhere.
        :param name: name of the context instantiated
        '''
        class Config(object):
            _config_dict = {}
        return Config()

    def _setDefaultConfig(self, name):
        '''
        Loads the default config parameters into the context data structure (tree).
        :param name: name of the context instantiated
        '''
        config = self._getDefaultConfig(name)
        for name in dir(config):
            if not name.startswith('_'):
                self.setConfig(name, getattr(config, name))
        config_dict = config._config_dict
        for name, owner in config_dict:
            self.setConfig(name, config_dict[(name, owner)], owner)


def smokeTestModule():
    context = ContextBase('python')
    from common.log.debugPrint import debugPrint
    pprint = debugPrint
    context.setConfig('backend_name', 'python')
    pprint(context.getConfig('backend_name'))
    pprint(context.getConfigDict())


if __name__ == "__main__":
    smokeTestModule()
