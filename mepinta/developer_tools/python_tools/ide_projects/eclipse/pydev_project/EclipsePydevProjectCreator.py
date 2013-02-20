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

from ide_projects.base import ConfigDictProjectCreatorBase
from ide_projects.eclipse.pydev_project.EclipsePydevProjectTemplates import EclipsePydevProjectTemplates

class EclipsePydevProjectCreator(ConfigDictProjectCreatorBase):
  '''
    Create a Eclipse Pydev Project. (given it's name in config_dict and target root)
  '''
  def _getTemplates(self, target_root):
    templates = EclipsePydevProjectTemplates(context=self.context, config_dict=self.config_dict).getTemplatePerPath(target_root)
    return templates

if __name__ == "__main__":
  pass
