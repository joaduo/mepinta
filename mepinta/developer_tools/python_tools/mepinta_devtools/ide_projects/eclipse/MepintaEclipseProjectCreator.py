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
from mepinta_devtools.ide_projects.eclipse.EclipseProjectCreator import EclipseProjectCreator
from mepinta_devtools.ide_projects.FileManager import FileManager
from common.path import joinPath, splitPath, getObjectModulePath
from mepinta_devtools.templates.mappers.FileToFileMap import FileToFileMap
from mepinta_devtools.ide_projects.eclipse.repository.cdt_k3dv1_plugin.CProjectXML import CProjectXML
from mepinta_devtools.ide_projects.eclipse.repository.cdt_k3dv1_plugin.src.ProcessorCPP import ProcessorCPP

class MepintaEclipseProjectCreator(FrameworkBase):
  def __post_init__(self):
    self.ep_creator = EclipseProjectCreator(self.context)
    self.file_manager = FileManager(self.context)

  def _getMepintaRoot(self):
    return splitPath(getObjectModulePath(self))[:-6]

  def _getAbsoluteSrcPath(self, relative_path):
    return joinPath(self._getMepintaRoot() + splitPath(relative_path))

  def _createPydevLinked(self, projects_dir, project_name, mepinta_src_dir):
    self.ep_creator.createPydev(projects_dir, project_name, create_src=False)
    dst = joinPath(projects_dir, project_name, 'src')
    self.file_manager.symlink(self._getAbsoluteSrcPath(mepinta_src_dir), dst)

  def createMepintaCoreProject(self, projects_dir):
    self._createPydevLinked(projects_dir, 'MepintaCore', 'core/python_core')

  def createMepintaCommonProject(self, projects_dir):
    self._createPydevLinked(projects_dir, 'MepintaCommon', 'common_libs/python/common')

  def createMepintaArgsApiProject(self):
    pass

  def createMepintaArgsApiCPPProject(self):
    pass

#  def createK3dv1PluginProject(self, projects_dir, plugin_manifest):
#    templates_config = [
#      FileToFileMap(CProjectXML(), '.cproject',),
#      FileToFileMap(ProcessorCPP(), 'src/%s.cpp' % plugin_manifest.getName())
#      # TODO: Plugin.cpp
#    ]
#    config_dict = dict(plugin_manifest=plugin_manifest)
#    project_name = plugin_manifest.getName()
#    self.ep_creator.createCDT(projects_dir, project_name, config_dict=config_dict, templates_config=templates_config, template_set='cdt_k3dv1_plugin')

def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()
  mepc = MepintaEclipseProjectCreator(context)
  print mepc.__class__.__module__
  print "%r" % mepc.file_manager.__class__.__module__
  print type(mepc.file_manager.__class__.__module__)
  print mepc._getMepintaRoot()
  print mepc._getAbsoluteSrcPath('core/python_core')
#  mepc.createMepintaCoreProject('/home/jduo/001-Mepinta/EclipseProjects_GitRepo/mepinta_test_folders/EclipseProjects')
  mepc.createMepintaCommonProject('/home/jduo/001-Mepinta/EclipseProjects_GitRepo/mepinta_test_folders/EclipseProjects')

if __name__ == "__main__":
  test_module()
