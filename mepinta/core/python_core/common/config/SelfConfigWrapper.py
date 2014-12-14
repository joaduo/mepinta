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


class SelfConfigWrapper(object):

    '''
      Provides a wrapper for a context object to have easier access to a
      class' level configuration.

      This wrapper is used by classes inheriting from
      :class:`from common.abstract.SelfConfigBase.SelfConfigBase`.
    '''

    def __init__(self, owner_class, context):
        object.__setattr__(self, 'owner_class', owner_class)
        object.__setattr__(self, 'context', context)

    def __getattr__(self, name):
        # we shouldn't intercept these attrs
        if name in ['context', 'owner_class', '__deepcopy__']:
            object.__getattribute__(self, name)
        # Intercept other names
        elif self.context.hasConfig(name, self.owner_class):
            return self.context.getConfig(name, self.owner_class)
        else:  # there is no config for such name
            raise AttributeError(
                'There is no config for %r of the class %r' % (name, self.owner_class))

    def __deepcopy__(self, memo):
        return self

    def __setattr__(self, name, value):
        key_names = ['context', 'owner_class']
        if name not in key_names:  # context and owner_class shouldn't be intercepted
            self.context.setConfig(name, value, self.owner_class)
        else:
            class_str = "%s.%s" % (self.owner_class.__module__.__str__(),
                                   self.owner_class.__name__)
            msg = ('You shouldn\'t use the names in %r for a class\' own config. (%r'
                   ' in this case) \n The names in %r are reserved attributes for '
                   'the context wrapper. Please use any other config name.' %
                   (key_names, class_str, key_names))
            raise AttributeError(msg)
