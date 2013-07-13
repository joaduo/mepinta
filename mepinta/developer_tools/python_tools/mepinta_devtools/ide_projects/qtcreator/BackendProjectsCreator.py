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

class BackendProjectsCreator(FrameworkBase):
  def __post_init__(self):
    self.templates = QtTemplateManager(self.context)
    self.file_manager = FileManager(self.context)
    self.__backend = 'c_and_cpp'

  def __getBackendsPath(self):
    mepinta_src = self.context.deployment_config.mepinta_source_path
    return joinPath(mepinta_src, 'backend', self.__backend)

  def getSourcesPath(self, api):
    return joinPath(self.__getBackendsPath(), 'backend_api_%s' % api)

  def _getSourcesPri(self, template_name, api, sdk_path):
    #Build where the sources are
    sources_path = self.getSourcesPath(api)
    prj_src_path = 'src/'
    sources_paths = self.file_manager.findFilesRel(sources_path, '.*\.%s$' % api)
    sources = ' \\\n'.join([prj_src_path + f for f in sources_paths])
    headers_paths = self.file_manager.findFilesRel(sources_path, r'.*\.h$')
    headers = ' \\\n'.join([prj_src_path + f for f in headers_paths])
    includes = ' \\\n'.join([prj_src_path, sdk_path])
    sources_pri = self.templates.getTemplate(template_name,
                                             SOURCES=sources,
                                             HEADERS=headers,
                                             INCLUDEPATH=includes)
    return sources_pri

  def _createSourcesPri(self, project_path, api, sdk_path, overwrite):
    file_name = 'sources.pri'
    sources_pri = self._getSourcesPri(file_name, api, sdk_path)
    file_path = joinPath(project_path, file_name)
    self.file_manager.saveTextFile(file_path, sources_pri, overwrite)

  def _createDirsLinkLib(self, project_path, api, libs_path, overwrite):
    #Create the src/ link
    src = self.getSourcesPath(api)
    dst = joinPath(project_path, 'src')
    self.file_manager.symlink(src, dst, overwrite)
    #create the built_objects/ dir
    built_path = joinPath(project_path, 'built_objects')
    self.file_manager.mkdir(built_path, overwrite)

  def _createProjectPro(self, project_path, api, libs_path, overwrite):
    target = 'backend_api_%s' % api
    pro_text = self.templates.getTemplate('mepinta_lib.pro',
                                          TARGET=target,
                                          DESTDIR=libs_path)
    path = joinPath(project_path, '%s.pro' % target)
    self.file_manager.saveTextFile(path, pro_text, overwrite)
    mk_cmd = 'build_library.py'
    build_text = self.templates.getTemplate(mk_cmd, TARGET=target)
    mk_cmd = joinPath(project_path, mk_cmd)
    self.file_manager.saveTextFile(mk_cmd, build_text, overwrite)
    return (target, mk_cmd)


  def createProject(self, project_path, api, sdk_path, libs_path, overwrite=False):
    make = self._createProjectPro(project_path, api, libs_path,
                                          overwrite)
    self._createSourcesPri(project_path, api, sdk_path, overwrite)
    self._createDirsLinkLib(project_path, api, libs_path, overwrite)
    return make

  def deployProjects(self, qt_projects_path, sdk_path, libs_path,
                             overwrite):
    mk_targets = []
    projects_path = joinPath(qt_projects_path, 'backend')
    for api in ('c', 'cpp'):
      backend_path = joinPath(projects_path, 'backend_api_%s' % api)
      self.file_manager.makedirs(backend_path, overwrite)
      mk_target = self.createProject(backend_path, api, sdk_path, libs_path,
                                     overwrite)
      mk_targets.append(mk_target)
    return mk_targets

def smokeTestModule():
  from common.log.debugPrint import debugPrint
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()
#  project_path = '/home/jduo/001-Mepinta/EclipseProjects_GitRepo/mepinta_test_folders/deployment/build/backend'
#  api = 'c'
  pc = BackendProjectsCreator(context)
#  pc.createProject(project_path, api)
  debugPrint(pc._getSourcesPri('sources.pri', 'cpp', 'some/mepintasdk'))

if __name__ == "__main__":
  smokeTestModule()
