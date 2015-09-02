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
import sys
import imp
import pkgutil
from bisect import bisect_left
from mepinta.plugins_manager.data_model import PluginMetadata
from common.abstract.FrameworkBase import FrameworkBase
import importlib
from mepinta.plugins_manager.plugins_manager_detail.PluginImportError import PluginImportError
from mepinta_devtools.deployment.PythonPathManager import PythonPathManager
from importlib import import_module


class PluginPackageManager(FrameworkBase):

    '''
      This class is used as a helper for the PluginsManager class.
      - check plugin package existance.
      - loads the minor version (revision) list.
      - converts package to name and vice versa.
    '''

    def __post_init__(self, plugins_type):
        self.plugins_type = plugins_type
        self.python_path = PythonPathManager()

    def getBackendNamespaces(self):
        if self.context.backend_name == 'python':
            prefixes = ['plugins.python',
                        #python2x or python3x
                        'plugins.python%sx' % sys.version_info[0], ]
        else:  # We are on c_and_cpp
            prefixes = ['plugins.c_and_cpp']
        return prefixes

    def python2x3xImport(self, short_name):
        prefixes = self.getBackendNamespaces()
        return self._importPackage(prefixes, short_name)

    def _getMissingPluginError(self, prefixes, short_name):
        namespace = '(%s).%s.%s' % (
            '|'.join(prefixes), self.plugins_type, short_name)
        msg = 'Couldn\'t load {namespace} plugin.'.format(namespace=namespace)
        return PluginImportError(msg)

    def _importPackage(self, prefixes, short_name):
        for prfx in prefixes:
            try:
                name = '%s.%s.%s' % (prfx, self.plugins_type, short_name)
                # __import__(name, fromlist="dummy")
                module = import_module(name)
                return module
            except ImportError as e:
                # TODO: add an config for this printing
                self.log.lastException()
                self.log.debug(
                    'Could not import %s. Exception: %s' % (name, e))
        # Couldn't find the requested package
        raise self._getMissingPluginError(prefixes, short_name)

    def getPackageAndName(self, plugin):
        '''
          PluginsManager can receive a package/module or a string.
          This functions gets whatever we don't have and returns both.
        '''
        if isinstance(plugin, (str, unicode)):  # We have the name, then we need to get the package
            plugin_name = plugin
            plugin_package = self.python2x3xImport(plugin)
        elif isinstance(plugin, PluginMetadata):
            # Is a Processor or DataType object, build the name
            # The package is already there
            plugin_name = self.prefix + plugin.name
            plugin_package = plugin.package
        else:  # It's a package, we need the name
            plugin_package = plugin
            # TODO: fix this?? plugin name is relative?
            plugin_name = '.'.join(plugin_package.__name__.split('.')[3:])
        self.log.debug('Name: %r, package: %s' % (plugin_name, plugin_package))
        return plugin_name, plugin_package

    def getRevisionModules(self, plugin_package):
        '''
          Within a plugin package we can find several modules. Each for one build.
          Each build is a minor version.
          We need to list them and get them sorted by the versions.
        '''
        # TODO: reuse the PluginsBrowser and make getName en el PluginManifest
        prefix = plugin_package.__name__ + "."
        other_modules = []
        modules_names = []
        name_version_separator = self.context.minor_version_separator  # '__'
        # TODO: remove prefix
        for importer, modname, ispkg in pkgutil.iter_modules(plugin_package.__path__, prefix):
            # TODO: with prefix removed, this is not necessary
            module_name = modname.split('.')[-1]
            self.log.debug("Found submodule %s (is a plugin_package: %s)" %
                           (module_name, ispkg))
            if not ispkg:
                if name_version_separator in module_name:
                    modules_names.append(module_name)
                else:
                    other_modules.append(module_name)
        vers_mod_name = 'plugin_versioning'
        if vers_mod_name in other_modules:
            self.log.debug('Found versioning module for plugin: %s' %
                           plugin_package.__name__)
            vers_namespace = '%s.%s' % (plugin_package.__name__, vers_mod_name)
            versioning_mod = importlib.import_module(vers_namespace)
            if hasattr(versioning_mod, 'str_to_version'):
                # The developer can implement it's own minor versioning
                # convention
                str_to_version = versioning_mod.str_to_version
            else:
                self.log.w('Found plugin versioning module, but has no versioning '
                           ' function "str_to_version". Using default')
                str_to_version = int
        else:
            self.log.d(
                'There is no versioning module for this plugin. Using default')
            str_to_version = int

        sorted_names_list = []
        sorted_version_list = []
        for module_name in modules_names:
            version_str = module_name.split(name_version_separator)[-1]
            try:
                version = str_to_version(version_str)
            except Exception as e:  # If there is an exception while converting
                self.log.e('Exception while trying to convert version_str=%r to version'
                           ' object.' % version_str)
                raise e
            index = bisect_left(sorted_version_list, version)
            sorted_version_list.insert(index, version)
            sorted_names_list.insert(index, module_name)
        # TODO: review this
        return dict(names=sorted_names_list, versions=sorted_version_list)

    def getRevisionModule(self, package_name, build_name):
        '''
          Once we know which module we are interested in, we would like to access its contents.
          So let's load it and return it for later use.
        '''
        build_module = self.python2x3xImport(
            '%s.%s' % (package_name, build_name))
        # TODO: should we do a deep reload here? check also
        # pipeline_backend/load_unload_library.py
        build_module = imp.reload(build_module)
        return build_module
