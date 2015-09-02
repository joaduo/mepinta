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
from common.abstract.FrameworkBase import FrameworkBase
from common.inotify.mask import IN_CREATE, IN_DELETE_SELF, IN_MOVED_TO, IN_ALL_EVENTS
from common.path import pathExists, pathHead, realPath


class PathAction(FrameworkBase):

    def __post_init__(self, path, mask=0):
        self.__mask = mask
        self.__path = path
        self.__watch_head = not pathExists(path)
        self.__functions = {}
        self.appendFunction(self.deletionAction, IN_DELETE_SELF)

    def __call__(self, event, manager):
        if self.__watch_head:
            self.__pathHeadAction(event, manager)
        else:
            for mask, functions in self.__functions.items():
                if mask & event.mask:
                    self.__callFunctions(functions, event, manager)

    def __callFunctions(self, functions, event, manager):
        for function in functions:
            function(event, self, manager)

    def deletionAction(self, event, action, manager):
        self.__watch_head = True
        manager.registerAction(self)

    def __pathHeadAction(self, event, manager):
        if event.mask & IN_DELETE_SELF:
            raise RuntimeError('Path head deleted. Can\'t keep watching it: %r' % self.path)
        if pathExists(self.getRealPath()):
            self.log.debug('Path exists: %r' % self.getRealPath())
            # No longer watching the head folder
            self.__watch_head = False
            # Now we watch the file egain (remove and readds)
            manager.registerAction(self)
            # Call this action to processes the file events
            self.__call__(event, manager)
        else:
            self.log.debug('Path still doesn\'t exist: %r' % self.getRealPath())

    def appendFunction(self, function, mask=None):
        if mask == None:
            mask = self.mask
        else:
            self.__mask |= mask
        if mask not in self.__functions:
            self.__functions[mask] = []
        if function not in self.__functions[mask]:
            self.__functions[mask].append(function)

    def removeFunction(self, function, mask=None):
        if mask == None:  # remove function from all lists
            for mask, functions in self.__functions.items():
                if function in functions:
                    functions.remove(function)
        else:  # remove function for a specific mask
            if mask in self.__functions:
                if function in self.__functions[mask]:
                    self.__functions[mask].remove(function)

    def getRealPath(self):
        return realPath(self.__path)

    def getPath(self):
        if self.__watch_head:
            return pathHead(self.getRealPath())
        else:
            return self.getRealPath()

    def getMask(self):
        if self.__watch_head:
            return IN_CREATE |IN_MOVED_TO  # |IN_ALL_EVENTS
        else:
            return self.__mask
    path = property(getPath, None, None, None)
    mask = property(getMask, None, None, None)

if __name__ == "__main__":
    from getDefaultContext import getDefaultContext
    context = getDefaultContext()
    path_action = PathAction(context, path='/path')
    context.log(path_action)
