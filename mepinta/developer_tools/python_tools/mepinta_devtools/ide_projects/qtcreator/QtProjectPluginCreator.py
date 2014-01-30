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

class QtProjectPluginCreatorBase(FrameworkBase):
  def __post_init__(self):
    self.file_manager = FileManager(self.context)
    self.templates = QtTemplateManager(self.context)
    self.__backend = 'c_and_cpp'

  def _createSourcesPri(self, project_path, api, sdk_path, overwrite):
    file_name = 'sources.pri'
    sources_pri = self._getSourcesPri(file_name, api, sdk_path)
    file_path = joinPath(project_path, file_name)
    self.file_manager.saveTextFile(file_path, sources_pri, overwrite)

  def _createLibDirectory(self, plugins_path, rel_lib_dir, overwrite):
    #Create the directory where the lib is going to be stored
    dest_dir = joinPath(plugins_path, self.__backend, rel_lib_dir)
    self.file_manager.makedirs(dest_dir)
    return dest_dir

  def _getIncludesList(self):
    #TODO:INSTALL Distribution specific
    includes = '''/usr/lib/glibmm-2.4/include
/usr/include/glibmm-2.4
/usr/lib/x86_64-linux-gnu/glibmm-2.4/include/
/usr/lib/x86_64-linux-gnu/glib-2.0/include/
/usr/lib/x86_64-linux-gnu/sigc++-2.0/include/
/usr/lib/glib-2.0/include
/usr/include/glib-2.0
/usr/include/sigc++-2.0
/usr/lib/sigc++-2.0/include

/home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/k3dv1/k3dv1_Libs/include
/home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/k3dv1/k3dv1_Libs/boost

/home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/k3dv1/k3dv1MPExtension
'''
    return includes.splitlines()

  def _getSourcesPri(self, template_name, sources_path, sdk_path):
    #Build where the sources are
    prj_src_path = 'src/'
    sources_paths = self.file_manager.findFilesRel(sources_path, '.*\.(c|cpp)$')
    sources = ' \\\n'.join([prj_src_path + f for f in sources_paths])
    headers_paths = self.file_manager.findFilesRel(sources_path, '.*\.(h|hpp)$')
    headers = ' \\\n'.join([prj_src_path + f for f in headers_paths])
    includes = ' \\\n'.join([prj_src_path, sdk_path] + self._getIncludesList())
    sources_pri = self.templates.getTemplate(template_name,
                                             SOURCES=sources,
                                             HEADERS=headers,
                                             INCLUDEPATH=includes)
    return sources_pri

  def _createQtProject(self, qt_projects_path, sdk_path, manifest,
                       dest_dir, overwrite):
    #mk_cmd project dir
    target = manifest.getModuleName()
    project_path = joinPath(qt_projects_path, manifest.getRelDir(),
                            manifest.getName())
    self.file_manager.makedirs(project_path)
    #create pro file
    #TODO: also pring whole module path (in order to know how to call it from make)
    pro_str = self.templates.getTemplate('k3dv1_plugin.pro',
                                         DESTDIR=dest_dir,
                                         TARGET=target,)
    pro_path = joinPath(project_path, '%s.pro' % target)
    self.file_manager.saveTextFile(pro_path, pro_str, overwrite)
    #create sources.pri
    sources_path = manifest.getSourcesPath()
    #link sources
    self._linkSources(project_path, sources_path, overwrite)
    pri_name = 'sources.pri'
    pri_str = self._getSourcesPri(pri_name, sources_path, sdk_path)
    pri_path = joinPath(project_path, pri_name)
    self.file_manager.saveTextFile(pri_path, pri_str, overwrite)
    #create build script
    mk_cmd = 'build_library.py'
    build_text = self.templates.getTemplate(mk_cmd,
                                            TARGET=target)
    mk_cmd = joinPath(project_path, mk_cmd)
    self.file_manager.saveTextFile(mk_cmd, build_text, overwrite)
    return (manifest.getMakeName(), mk_cmd)

  def _linkSources(self, project_path, sources_path, overwrite):
    #link sources to get them inside the project
    dst = joinPath(project_path, 'src')
    self.file_manager.symlink(sources_path, dst, overwrite)

  def createProject(self, projects_path, plugins_path, sdk_path, manifest,
                    overwrite):
    #create the dest_dir directory for the library (.so)
    dest_dir = self._createLibDirectory(plugins_path, manifest.getRelDir(),
                                        overwrite)
    #create the Qt project .pro .pri and build_library.py
    mk_target = self._createQtProject(projects_path, sdk_path, manifest,
                          dest_dir, overwrite)
    #return build script
    return [mk_target]


def smokeTestModule():
#  from getDefaultContext import getDefaultContext
#  context = getDefaultContext()
  raise RuntimeWarning('No smoke test')

if __name__ == "__main__":
  smokeTestModule()
