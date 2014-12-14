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
import os
from common.path import joinPath
import sys
import imp


class LoaderBase(object):

    def __init__(self, plugins_root, path):
        self.plugins_root = plugins_root
        self.path = path

    def _getPluginsSets(self, plugins_root):
        def getDirs(path):
            return os.walk(path).next()[1]
        plugins_dict = dict((backend, getDirs(joinPath(plugins_root, backend)))
                            for backend in getDirs(plugins_root))
        return plugins_dict


class PluginLoader(LoaderBase):

    def load_module(self, fullname):
        split = fullname.split('.')
        plugins_dict = self._getPluginsSets(self.plugins_root)
        backend = split[1]
        if backend not in plugins_dict:
            raise ImportError(
                'No plugins repository for backend %r.' % backend)
        found = self._findModule(split, backend, plugins_dict)
        if found:
            return imp.load_module(fullname, *found)

    def _findModule(self, split, backend, plugins_dict):
        # Check if it has the plugins_set name inside?
        # plugins.*.processors.{plugins_set}
        # plugins.*.data_types.{plugins_set}
        p_sets = plugins_dict[backend]
        if len(split) >= 4 and split[3] in p_sets:
            p_sets = set([split[3]])

        def getPath(plugin_set):
            return joinPath(self.plugins_root, backend, plugin_set, 'python_modules',
                            split[:-1])
        path = [getPath(s) for s in p_sets]
        try:
            return imp.find_module(split[-1], path)
        except ImportError:
            return None


class BrutePluginLoader(LoaderBase):

    def load_module(self, fullname):
        split = fullname.split('.')
        plugins_dict = self._getPluginsSets(self.plugins_root)
        found = self._findModule(split, plugins_dict)
        if found:
            return imp.load_module(fullname, *found)

    def _findModule(self, split, plugins_dict):
        # Check if it has the plugins_set name inside?
        # Brute force Search
        def getPath(plugin_set, backend):
            return joinPath(self.plugins_root, backend, plugin_set, 'python_modules', *split[:-1])
        path = []
        for backend in plugins_dict:
            p_sets = plugins_dict[backend]
            path += [getPath(s, backend) for s in p_sets]
        try:
            return imp.find_module(split[-1], path)
        except ImportError:
            return None


class PluginImportHook(object):

    def __init__(self, plugins_root):
        self.plugins_root = plugins_root
        self.prefixes = self.getPrefixes()
        self.enabled = True

    def getPrefixes(self):
        namespaces = {  # python2x or python3x
            'plugins.python%sx' % sys.version_info[0]: PluginLoader,
                      'plugins.python': PluginLoader,
                      'plugins.c_and_cpp': PluginLoader,
                      'plugins_tests': BrutePluginLoader,
        }
        return namespaces

    def find_module(self, fullname, path):
        if self.enabled:
            # Find accepted prefixes
            names = filter(lambda p: fullname.startswith(p), self.prefixes)
            if names:
                return self.prefixes[names[0]](self.plugins_root, path)


def smokeTestModule():
    #  from getDefaultContext import getDefaultContext
    #  context = getDefaultContext()
    plugins_root = '/home/jduo/001-Mepinta/git/mepinta/mepinta/plugins'
    mt = PluginImportHook(plugins_root)
#  mt.enabled = False
    import sys
    sys.meta_path.append(mt)
    import mepinta
    import plugins.c_and_cpp
    import plugins.c_and_cpp.data_types.k3dv1.bitmap as d
#  print d
    import plugins.c_and_cpp.data_types.mepinta.functum as m
#  print m
    import plugins.c_and_cpp.data_types.cpp.std.string as s
    import pprint
    import plugins_tests.demo
    import k3d
    import importing_plugins.common_data_types
    pprint.pprint(sys.modules)
#  import plugins_tests.demo
#  print sd

if __name__ == "__main__":
    smokeTestModule()
