# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2014, Joaquin G. Duo

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
from common.abstract.decorators.singleton import singleton_decorator
from collections import defaultdict
import threading


@singleton_decorator
class ContextManager(object):
    def __init__(self):
        self._context_stacks = defaultdict(list)

    def getContext(self, thread=None):
        stack = self.getStack(thread)
        if stack:
            return stack[-1]
        else:
            thread = self._getThread()
            # If we are inside a thread and there is no context defined
            # we get the context of the maint thread
            if not isinstance(thread, threading._MainThread):
                for t in self._context_stacks:
                    if isinstance(t, threading._MainThread):
                        return self.getContext(t)

    def _getThread(self):
        return threading.current_thread()
    
    def getStack(self, thread=None):
        if not thread:
            thread = self._getThread()
        return self._context_stacks[thread]

    def register(self, context):
        stack = self._context_stacks[self._getThread()]
        assert context not in stack or context == stack[-1]
        if not stack or context != stack[-1]:
            stack.append(context)

    def unregister(self, context):
        stack = self.getStack()
        if not stack or context != stack[-1]:
            raise LookupError('Could not solve the right context to be unregistered')
        else:
            stack.pop()


def smokeTestModule():
    from common.log.debugPrint import debugPrint
    mngr = ContextManager()
    debugPrint(mngr)
    context = 'foo'
    context2 = 'bar'
    mngr.register(context)
    mngr.register(context)
    mngr.register(context2)
    try:
        mngr.unregister(context)
    except LookupError as e:
        debugPrint(e)
    mngr.unregister(context2)
    mngr.unregister(context)

if __name__ == '__main__':
    smokeTestModule()
