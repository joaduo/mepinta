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
from ide_projects.base import ConfigDictProjectTemplatesBase
from ide_projects.eclipse.templates.ProjectXML import ProjectXML

class EclipsePydevProjectTemplates(ConfigDictProjectTemplatesBase):
  '''Maps the templates files and their corresponding translators classes to the
  path for the final translated file.
  '''
  def _getTemplatesRoot(self):
    import ide_projects.eclipse as eclipse_project
    return self._buildTemplateRoot(eclipse_project, ['repository', 'python_default'])
  def _getMapDict(self, **kwargs):
    return {
            (ProjectXML, 'pydevproject.xml'):'.pydevproject',
            (ProjectXML, 'project.xml') :'.project',
           }

if __name__ == "__main__":
  pass
