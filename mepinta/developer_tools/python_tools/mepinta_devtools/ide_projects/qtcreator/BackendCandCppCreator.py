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
from mepinta_devtools.ide_projects.qtcreator.QtTemplateManager import QtTemplateManager
from mepinta_devtools.ide_projects.FileManager import FileManager
from common.path import joinPath

class BackendCandCppCreator(FrameworkBase):
  def __post_init__(self):
    self.templates = QtTemplateManager(self.context)
    self.file_manager = FileManager(self.context)

  def __getBackendsPath(self):
    mepinta_src = self.context.deployment_config.mepinta_source_path
    return joinPath(mepinta_src, 'backend', 'c_and_cpp')

  def _getSourcesPri(self, template_name, api):
    backends_path = self.__getBackendsPath()
    #Build where the sources are
    files_path = joinPath(backends_path, 'backend_api_%s' % api)
    src_path = 'src/'
    sources_paths = self.file_manager.findFiles(files_path, '.*\.%s$' % api)
    sources = '\\\n'.join([src_path + f for f in sources_paths])
    headers_paths = self.file_manager.findFiles(files_path, r'.*\.h$')
    headers = '\\\n'.join([src_path + f for f in headers_paths])
    sources_pri = self.templates.getTemplate(template_name,
                                             SOURCES=sources,
                                             HEADERS=headers,
                                             INCLUDEPATH='')
    return sources_pri

  def _createSourcesPri(self, project_path, api, overwrite):
    file_name = 'sources.pri'
    sources_pri = self._getSourcesPri(file_name, api)
    file_path = joinPath(project_path, file_name)
    self.file_manager.saveTextFile(file_path, sources_pri, overwrite)

  def createBackendProject(self, project_path, api, overwrite=False):
    scripts_names = ['backend_api_%s.pro' % api]
    repo_subpath = 'backend_api_%s' % api
    self.templates.copyScripts(repo_subpath, project_path, scripts_names)
    self._createSourcesPri(project_path, api, overwrite)


def smokeTestModule():
  from common.log.debugPrint import debugPrint
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()
#  project_path = '/home/jduo/001-Mepinta/EclipseProjects_GitRepo/mepinta_test_folders/deployment/build/backend'
#  api = 'c'
  pc = BackendCandCppCreator(context)
#  pc.createBackendProject(project_path, api)
  debugPrint(pc._getSourcesPri('sources.pri', 'c'))

if __name__ == "__main__":
  smokeTestModule()
