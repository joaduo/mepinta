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
from common.context.ContextManager import ContextManager
from common.abstract.SelfConfigBase import SelfConfigBase
from common.abstract.PostInitStrategyBase import PostInitStrategyBase


class MepintaBase(PostInitStrategyBase, SelfConfigBase):

    '''
    Base class for all logic classes in the framework.
    Data classes should inherit from object or FrameworkObject
    '''

    def __init__(self, context=None, *a, **ad):
        # We need to solve the context for this class
        if not context:
            # Check if there is a root context
            context = ContextManager().getContext()
            if not context:
                # We need to import here to avoid chicken-egg problem
                from mepinta.context.MepintaContext import MepintaContext
                # Create the root context and register it
                context = MepintaContext()
        elif isinstance(context, basestring):
            # User passed the string identifying the context
            context = MepintaContext(context)
        # Now having the context solved, we can initialize super class
        SelfConfigBase.__init__(self, context=context)
        PostInitStrategyBase.__init__(self, *a, **ad)


def smokeTestModule():
    from common.log.debugPrint import debugPrint
    mp = MepintaBase()


if __name__ == '__main__':
    smokeTestModule()
