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
from mepinta_devtools.ide_projects.ProjectCreator import ProjectCreator
from mepinta_devtools.templates.mappers.FileToFileMap import FileToFileMap

class EclipseProjectCreator(FrameworkBase):
  ''' Create a Eclipse Pydev Project. (given it's name in config_dict and target root) '''
  def __post_init__(self):
    self.project_creator = ProjectCreator(self.context)

  def _setTemplateSet(self, templates_config, template_set):
    import mepinta_devtools.ide_projects.eclipse.repository as repo_package
    for map_config in templates_config:
      if isinstance(map_config, FileToFileMap):
        map_config.setRepoPackageAndTemplateSet(repo_package, template_set)

  def _getTranslationDict(self, project_name, translation_dict):
    local_translation_dict = dict(projectName=project_name)
    local_translation_dict.update(translation_dict)
    return local_translation_dict

  def _createSrcDir(self, projects_dir, project_name, create_src):
    if create_src:
      self.project_creator.createProjectDirs(projects_dir, project_name, 'src')
    else:
      self.project_creator.createProjectDirs(projects_dir, project_name)

  def _appendTemplatesConfig(self, templates_config, *templates):
    return templates_config + list(templates)

  def createProject(self, projects_dir, project_name, config_dict, translation_dict, templates_config, overwrite, create_src, template_set):
    translation_dict = self._getTranslationDict(project_name, translation_dict)
    self._setTemplateSet(templates_config, template_set)
    self._createSrcDir(projects_dir, project_name, create_src)
    self.project_creator.create(projects_dir, project_name, templates_config, config_dict, translation_dict, overwrite)

  def createPydev(self, projects_dir, project_name, config_dict={}, translation_dict={}, templates_config=[], overwrite=False, create_src=True, template_set='python_default'):
    templates_config = self._appendTemplatesConfig(templates_config,
      FileToFileMap('project.xml', '.project',),
      FileToFileMap('pydevproject.xml', '.pydevproject',),
    )
    self.createProject(projects_dir, project_name, config_dict, translation_dict, templates_config, overwrite, create_src, template_set)

  def createCDT(self, projects_dir, project_name, config_dict={}, translation_dict={}, templates_config=[], overwrite=False, create_src=True, template_set='cdt_default'):
    templates_config = self._appendTemplatesConfig(templates_config,
      FileToFileMap('project.xml', '.project'),
    )
    self.createProject(projects_dir, project_name, config_dict, translation_dict, templates_config, overwrite, create_src, template_set)


if __name__ == "__main__":
  pass
