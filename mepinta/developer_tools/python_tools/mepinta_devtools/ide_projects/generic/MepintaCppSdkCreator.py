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
from common.abstract.FrameworkBase import FrameworkBase
from mepinta_devtools.ide_projects.FileManager import FileManager
from common.path import joinPath
from mepinta_devtools.ide_projects.qtcreator.BackendProjectsCreator import BackendProjectsCreator
from mepinta_devtools.plugins.PluginsBrowser import PluginsBrowser
from mepinta_devtools.deployment.PythonPathManager import PythonPathManager


class MepintaCppSdkCreator(FrameworkBase):

    def __post_init__(self):
        self.backend_creator = BackendProjectsCreator(self.context)
        self.file_manager = FileManager(self.context)
        self.plugins_browser = PluginsBrowser(self.context)
        self.python_path = PythonPathManager()

    def _getLatestDataTypesManifests(self, plugins_set, backend):
        # get module manifests
        manifests = self.plugins_browser.getManifests(plugins_set, backend,
                                                      'data_types')
        # link to each code
        sep = self.context.minor_version_separator
        latest_manifests = {}
        for m in manifests:
            m = m(self.context)
            name, version = m.__module__.split(sep)
            if name not in latest_manifests:
                latest_manifests[name] = dict(version=version, manifest=m)
            if version > latest_manifests[name]['version']:
                latest_manifests[name] = dict(version=version, manifest=m)
        return latest_manifests

    def createDataTypesInclude(self, project_path, plugins_set, overwrite=False):
        # create data_types include path
        dtypes_path = joinPath(project_path, 'data_types')
        self.file_manager.makedirs(dtypes_path)
        # add plugins path
        backend = 'c_and_cpp'
        self._linkIncludeFolders(project_path, plugins_set, backend, overwrite)

    def _linkIncludeFolders(self, project_path, plugins_set, backend, overwrite):
        manifests = self._getLatestDataTypesManifests(plugins_set, backend)
        for m in manifests.values():
            m = m['manifest']
            # create directories
            link_dir = joinPath(project_path, m.getIncludeDir())
            # Ignore, since it will be repeated
            self.file_manager.makedirs(link_dir)
            # link src dir
            link_dst = joinPath(link_dir, m.getName())
            # always force, since they are not removed
            self.file_manager.symlink(m.getSourcesPath(), link_dst, overwrite)

    def createProject(self, project_path, overwrite=False):
        # TODO: this is a hack, since there will be a link inside the source files
        # should be mepintasdk/c and mepintasdk/cpp but mepintasdk/c = mepintasdk now
        # make mepintasdk/ dir
        mepintasdk_path = joinPath(project_path, 'mepintasdk')
        #self.file_manager.mkdir(sdk_path, overwrite)
        api_c_path = self.backend_creator.getSourcesPath('c')
        # link c directory
        self.file_manager.symlink(api_c_path, mepintasdk_path, overwrite)
        # link cpp directory
        api_cpp_path = self.backend_creator.getSourcesPath('cpp')
        cpp_dst = joinPath(mepintasdk_path, 'cpp')
        self.file_manager.symlink(api_cpp_path, cpp_dst, force=True)


def smokeTestModule():
    #  from getDefaultContext import getDefaultContext
    #  context = getDefaultContext()
    raise RuntimeWarning('No smoke test')

if __name__ == "__main__":
    smokeTestModule()
