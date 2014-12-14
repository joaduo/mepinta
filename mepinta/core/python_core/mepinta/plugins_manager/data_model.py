# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

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
from common.abstract.FrameworkObject import FrameworkObject


class PluginMetadata(FrameworkObject):

    def __init__(self, name, build_name, version):
        self.name = name
        # TODO: rename build_name to minor_name?
        self.build_name = build_name
        self.version = version
        # TODO: review #To be initialized #TODO: make a decorator to make sure they are initialized
        #self.info = None

    def __str__(self):
        return self.name

    def __repr__(self):
        return '%r,%r' % (self.name, self.version)

    # TODO: add module to DataType,  and call manifest to solve this
    def getPreLoadPostUnload(self):
        return {}


class DataTypeMetadata(PluginMetadata):

    def __init__(self, name, build_name, version):
        PluginMetadata.__init__(self, name, build_name, version)
        # Initialize
        self.processors = []
        self.property_id = None

    def __wrapped_lo__(self):
        if self.property_id != None:
            return self.property_id
        else:
            raise RuntimeError(
                'Property: %s has no property_id defined' % self.name)

    def getShortName(self):
        return self.name.split('.')[-1]

    def getCNamespace(self):
        if self.name.startswith('c.') or self.name.startswith('mepinta.'):
            return self.getShortName()
        return self.name.replace('.', '_')

    c_namespace = property(getCNamespace)


class ProcessorMetadata(PluginMetadata):

    def __init__(self, name, build_name, version):
        PluginMetadata.__init__(self, name, build_name, version)
        # We need to keep the functions ids across reloads #name:property_id
        self.functions = {}

    def getFollowLibraryPath(self):
        pass
