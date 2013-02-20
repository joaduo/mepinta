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
from common.path import joinPath
from mepinta_devtools.ide_projects.FileManager import FileManager
from mepinta_devtools.templates.DictionaryBasedTranslator import DictionaryBasedTranslator

class ProjectCreator(FrameworkBase):
  def __post_init__(self):
    self.file_manager = FileManager(self.context)

  def _getAbsolutDstFilePath(self, project_dir, file_path):
    return joinPath(project_dir, file_path)

  def createProjectDirs(self, projects_dir, project_name, *other_dirs):
    '''Create the project's new directory and subdirs if necessary.'''
    path = joinPath(projects_dir, project_name, *other_dirs)
    if not self.file_manager.pathExists(path):
      self.file_manager.makedirs(path)
    else:
      self.log.warning("Path %r already exists." % path)

  def create(self, projects_dir, project_name, templates_config, config_dict, translation_dict={}, overwrite=False):
    project_dir = joinPath(projects_dir, project_name)
    for map_config in templates_config:
      local_translation_dict = {}
      local_translation_dict.update(translation_dict)
      if map_config.template_logic != None:
        local_translation_dict.update(
          map_config.template_logic.getTranslationDict(config_dict))
      content = DictionaryBasedTranslator().getContent(map_config.template, local_translation_dict)
      dst_path = self._getAbsolutDstFilePath(project_dir, map_config.dst_path)
      self.file_manager.saveTextFile(dst_path, content, overwrite | map_config.overwrite)


def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  test_module()
