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
from common.inotify.base import ModuleReloadBase
from common.inotify.InotifyActionManager import InotifyActionManager
from common.type_checking.isiterable import isiterable
from common.inotify.actions.PathAction import PathAction
from common.inotify.mask import IN_CLOSE_WRITE  # , IN_ALL_EVENTS


class ModuleAutoReload(ModuleReloadBase):

    def __post_init__(self):
        self.inotify_mngr = InotifyActionManager(self.context)
        self._watched_modules = []

    def registerModules(self, modules, functions):
        # is it one module or a list of modules?
        if not isiterable(modules):
            modules = [modules]
        if not isiterable(functions):
            functions = [functions]
        # regiter each provided module
        for module, function in zip(modules, functions):
            self._createModuleAction(module, function)
            # append to the list
            self._watched_modules.append(module)

    def _createModuleAction(self, module, function):
        # define the action function
        def moduleFunction(event, action, manager):
            try:
                reloaded_module = self._reloadModule(module)
            except Exception as e:
                action.log.error('Could\'t reload %s exception %s.' % (module, e))
                return
            action.log.debug('event: %s' % event)
            action.log.debug('calling: %s' % function)
            function(reloaded_module, event, action, manager)
            action.log.debug('finished: %s' % function)
        # define the action for the module file
        path_action = PathAction(self.context, path=module.__file__)
        # append function
        path_action.appendFunction(moduleFunction, mask=IN_CLOSE_WRITE)
        # add it to the inotify manager
        self.inotify_mngr.registerAction(path_action)

    def blockListeningEvents(self, modules=[], functions=[], timeout=None):
        # register modules, if any
        self.registerModules(modules, functions)
        # check that there are modules
        if not len(self._watched_modules):
            raise RuntimeError('Should should at least watch one module.')
        # listen to events
        self.inotify_mngr.blockListeningEvents(timeout)

if __name__ == "__main__":
    pass
