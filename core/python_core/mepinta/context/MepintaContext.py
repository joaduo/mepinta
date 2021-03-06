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
from common.context.Context import context_singleton
from common.context.base import ContextBase
from mepinta.pipeline.hi.context_lo.ContextLo import ContextLo
from mepinta.pipeline.hi.LogOutput import LogOutput
from pipeline_backend.logging.logging import LOG_INFO, logWarning
from inspect import currentframe
from common.context.ContextManager import ContextManager
import os
import re


class singleton_autocontext(context_singleton):

    '''
    We would like to select context based on the package that is calling the
      context.
    '''

    def __call__(self, name=None, *args, **kwargs):
        if not name:
            name = self.solveContextName(self._getCallerFilePath())
        return super(singleton_autocontext, self).__call__(name, *args, **kwargs)

    def _getCallerFilePath(self):
        frame = self._getFrame(back=3)
        return frame.f_code.co_filename

    def _getFrame(self, back):
        frame = currentframe()
        for _ in range(back):
            frame = frame.f_back
        return frame

    def solveContextName(self, path):
        # TODO: solve based on the main script also (if this method fails)
        regex = r'plugins.(?P<backend>(?:python)|(?:c_and_cpp)).(?:[a-z_0-9]+)'
        regex = regex.replace('.', os.path.sep)
        m = re.search(regex, path)
        if m:
            name = m.group('backend')
            return name
        else:
            logWarning('Setting backend_name="python". '
                       '(Could not resolve backend automatically by path %r )' % path)
            return 'python'

    def __getattr__(self, name):
        print name


@singleton_autocontext
class MepintaContext(ContextBase):

    '''
    Specializes the "encapsulated context pattern" for a Mepinta environment.
    This means:
      -having a 'backend_name' property
      -initializing lower level 'ContextLo' based on backend
      -setting logging output to the based on backend and specific for mepinta
    '''

    def __init__(self, name, log_level=LOG_INFO, register=True):
        ContextBase.__init__(self, name)
        if isinstance(name, basestring):
            # Means this is not a fork of a context, so we need to init it
            self._initConfig(log_level)
        ctx_mngr = ContextManager()
        if register and not ctx_mngr.getContext():
            self._logger().d('Registering first MepintaContext as root context')
            ctx_mngr.register(self)
        elif register and ctx_mngr.getContext():
            msg = ('Cannot register %r as root context, there is already a root'
                   ' context. (you should fork from root context)' %  self)
            raise TypeError(msg)

    def _logger(self):
        return self.getConfig('log')

    def _initConfig(self, log_level):
        deployment_path = self.getConfig('deployment_config').deployment_path
        context_lo = ContextLo(
            context=self, deployment_path=deployment_path)
        self.setConfig('context_lo', context_lo)
        self._logger().setOutput(LogOutput(context=self))
        self._logger().setLevel(log_level)

    def _getDefaultConfig(self, name):
        #TODO: backend should not be defined by configuration, but by code
        from mepinta_config import mepinta_config
        config = mepinta_config()
        if not hasattr(config, 'backend_name'):
            if 'python' in name:
                config.backend_name = 'python'
            elif 'cpp' in name:
                config.backend_name = 'c_and_cpp'
            else:
                raise LookupError('Cannot find backend name for context name')
        return config


def smokeTestModule():
    import logging
    from common.log.debugPrint import debugPrint
#     context = MepintaContext('python', log_level=logging.DEBUG)
#     context = MepintaContext('c_and_cpp')
    context = MepintaContext('python', log_level=logging.DEBUG)
    with context.fork(name='fork') as context:
        pprint = debugPrint
        pprint(context.getConfig('backend_name'))
        pprint(context.getConfig('plugin_build_targets'))
        pprint(context.getConfigDict())
        pprint(context.getLocalConfigDict())
    pprint(context.getConfigDict())

if __name__ == "__main__":
    smokeTestModule()
