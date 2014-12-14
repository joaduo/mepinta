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
from mepinta.plugins_creation.PluginPackageCreator import PluginPackageCreator
from mepinta.plugins_creation.base import PluginCreatorBase
from common.path import joinPath

# TODO: Add new data types to the data types database (done?)


class PluginCPPImplementationImporter(PluginCreatorBase):

    def __post_init__(self):
        self.plugin_creator = PluginPackageCreator(context=self.context)
        self.default_impl = "Debug"

    def __createSymlink(self, src, dst, force=True):
        if self._pathExists(dst) and force:
            os.remove(dst)
        self.log.debug("Linking %r <- %r" % (src, dst))
        os.symlink(src, dst)

    def __projectSrcPath(self, plugin_fdirs):
        project_path = plugin_fdirs.getPath("project")
        src_path = joinPath(project_path, 'src')
        if self._pathExists(src_path):
            return src_path
        return project_path

    def _acceptedExtension(self, file_path, header_only=False):
        if header_only:
            return file_path.endswith(".h") or file_path.endswith(".hpp")
        else:
            return file_path.endswith(".c") or file_path.endswith(".h") or file_path.endswith(".cpp") or file_path.endswith(".hpp")

    def _ignoredFiles(self, plugin_fdirs):
        return plugin_fdirs.build_names + ['.cproject', '.project']

    def _linkCPPFiles(self, src_path, plugin_fdirs):
        for file_path in os.listdir(src_path):
            if self._acceptedExtension(file_path):
                self.log.verbose("Linking %r " % file_path)
                self.__createSymlink(joinPath(src_path, file_path), joinPath(
                    plugin_fdirs.getPath("code"), file_path))
            elif file_path not in self._ignoredFiles(plugin_fdirs):
                self.log.warning("File or folder %r will not be synchronized. (in path %r)" % (
                    file_path, src_path))

    def _linkSharedLibraries(self, plugin_fdirs):
        build_paths = plugin_fdirs.implementationLibs()
        for build, path in build_paths.items():
            self.log.verbose("Linking %r." % build)
            self.__createSymlink(
                path, plugin_fdirs.getPath("module") + ".%s.so.implementation" % build)
        if self.default_impl in build_paths:
            self.log.verbose("Linking %r as default." % self.default_impl)
            self.__createSymlink(build_paths[self.default_impl], plugin_fdirs.getPath(
                "module") + ".so.implementation")

    def _linkEclipseFiles(self, plugin_fdirs):
        src_path = self.__projectSrcPath(plugin_fdirs)
        if self._pathExists(src_path):
            self._linkCPPFiles(src_path, plugin_fdirs)
            self._linkSharedLibraries(plugin_fdirs)
        else:
            self.log.warning("Eclipse path %r doesn't exist." % src_path)
            return False
        return True

    def _linkIncludeFiles(self, plugin_fdirs):
        # is it a data_type plugin? then do de link.
        if plugin_fdirs.lang_group == "data_types":
            src_path = self.__projectSrcPath(plugin_fdirs)
            for file_path in os.listdir(src_path):
                if self._acceptedExtension(file_path, header_only=True):
                    self.log.verbose("Linking %r " % file_path)
                    self.__createSymlink(joinPath(src_path, file_path), joinPath(
                        plugin_fdirs.getPath("data_types_include"), file_path))

    def importPlugin(self, plugin_fdirs):
        ''' Checks for existence of files in the independent project directory (Eclipse or QtCreator).
          Creates corresponding directories if they don't exist.
          Links files in the created directories.
            * .c, .cpp, .h and .hpp in the code directory
            * .so to .so.implementation in the plugin directory
          Creates the plugin manifest if not present.

          plugin_fdirs: provides all the configuration of the plugin.
            Where to get the files and where to send them.
        '''
        if self._linkEclipseFiles(plugin_fdirs):
            # if it was able to create the plugin module in the mepinta tree
            # then link the include files for data type plugins
            self._linkIncludeFiles(plugin_fdirs)


if __name__ == "__main__":
    pass
