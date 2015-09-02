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
import logging


@singleton_decorator
class ContextManager(object):
    def __init__(self):
        self._contexts = set()
        self._context_stacks = defaultdict(list)
        # Caching main thread
        self._main_thread = None

    def getContext(self, thread=None):
        stack = self.getStack(thread)
        if stack:
            # Return latest context registered for this thread
            return stack[-1]
        else:
            # If we are inside a thread and there is no context defined
            # we get the context of the maint thread
            if not isinstance(self._getThread(), threading._MainThread):
                return self.getContext(self._getMainThread())
        logging.warn('No context defined in thread, neither in main thread.')
        # Make return explicit
        return None

    def _getMainThread(self):
        if not self._main_thread:
            for t in self._context_stacks:
                if isinstance(t, threading._MainThread):
                    self._main_thread = t
        return self._main_thread

    def _getThread(self):
        return threading.current_thread()
    
    def getStack(self, thread=None):
        thread = thread or self._getThread()
        return self._context_stacks[thread]

    def register(self, context):
        stack = self.getStack()
        # Trying to append the context twice
        if context in self._contexts:
            raise ValueError('Context %r already registered' % context)
        self._contexts.add(context)
        stack.append(context)

    def unregister(self, context):
        stack = self.getStack()
        if context not in self._contexts:
            raise LookupError('Context %r is not registered' % context)
        elif context != stack[-1]:
            # Context is not registered
            raise LookupError('Context %r is not the last context in stack' % context)
        else:
            self._contexts.remove(context)
            stack.pop()


def smokeTestModule():
    from common.log.debugPrint import debugPrint
    mngr = ContextManager()
    debugPrint(mngr)
    context = 'foo'
    context2 = 'bar'
    mngr.register(context)
    try:
        mngr.register(context)
    except ValueError as e:
        debugPrint(e)
    mngr.register(context2)
    try:
        mngr.unregister(context)
    except LookupError as e:
        debugPrint(e)
    mngr.unregister(context2)
    mngr.unregister(context)

if __name__ == '__main__':
    smokeTestModule()
