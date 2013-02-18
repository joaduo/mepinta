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
from mepinta.plugins_creation.base import ProjectCreatorBase
from mepinta.plugins_creation.module_to_cpp.qt_project.QtProjectTemplates import QtProjectTemplates

class K3dv1QtProjectCreator(ProjectCreatorBase):
  '''
    Create a Qt Project from a plugin manifest and a given path to place 
    the project (could be the Eclipse workspace).
    Uses a template based creation. Right now there are templates for k3d plugins.
    But more could be added.
  '''
  def _getTemplates(self, plugin_manifest, target_root):
    templates = QtProjectTemplates(context=self.context).getTemplatePerPath(plugin_manifest, target_root)
    return templates

if __name__ == "__main__":
  from mepinta.context.MepintaContext import MepintaContext
  context = MepintaContext('python')  

