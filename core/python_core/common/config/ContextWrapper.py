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
from common.context.data_model import global_namespace


class ContextWrapper(object):

    '''
      Provides a wrapper for a context object.
      This wrapper is used by other classes for managing the global config.
      ContextClientBase
          They will do to save some config:
            self.context.config.some_parameter = <value>
            self.context.some_parameter = <value>
          And to retrieve it:
            <variable> = self.context.config.some_parameter
          Where 'self' would be an instance of this class.
          Without this wrapper the class should have to do:
            <variable> = self.context.getConfig('global','some_parameter')
          This way, accessing to the global config is straightforward.
    '''

    def __init__(self, context):
        '''
        :param context: context to be wrapped
        '''
        object.__setattr__(self, 'context', context)

    def __getattr__(self, name):
        '''
        If:
          - name matches a ContextWrapper's attr, return it, if not
          - name matches stored global config inside context, return it, if not
          - raises exception
        :param name: attribute to be retrieved (in config or intance's attr)
        :raises: AttributeError
        '''
        if name in ['context', '__deepcopy__','set', 'get', 'fork','__enter__', '__exit__', '__deepcopy__']:
            return object.__getattribute__(self, name)
        elif name in ['hasConfig', 'getConfig', 'setConfig', 'newChildConfig', 'getConfigDict']:
            return getattr(self.context, name)
        elif self.context.hasConfig(name):
            return self.context.getConfig(name)
        else:
            raise AttributeError(
                'There is no global config named %r ' % (name))

    def get(self, k):
        return self.context.get(k)

    def set(self, k, v, owner=global_namespace):
        return self.context.setConfig(k, v, owner)

    def fork(self, **kwargs):
        return ContextWrapper(self.context.fork(**kwargs))

    def __setattr__(self, name, value):
        '''
        If:
          - name matches a ContextWrapper's attr, raise KeyError, if not
          - store value in global config inside context, set it

        :param name: global config paramter to be set in
        :param value: value of parameter
        :raises: KeyError
        '''
        reserved_props = [
            'context', '__deepcopy__', 'config', 'hasConfig', 'getConfig', 'setConfig']
        if name not in reserved_props:
            self.context.setConfig(name, value)
        else:
            raise KeyError(
                'Cannot set config with name in %r. Those are reserved names.' % reserved_props)

    def __deepcopy__(self, memo):  # Disable DeepCopy
        '''
        Disable deepcopying, since the class has its own forking mechanism.
        :param memo:
        '''
        return self

    def __enter__(self):
        return ContextWrapper(self.context.__enter__())
    
    def __exit__(self, type_, value, traceback):
        return self.context.__exit__(type_, value, traceback)


def smokeTestModule():
    pass

if __name__ == "__main__":
    smokeTestModule()
