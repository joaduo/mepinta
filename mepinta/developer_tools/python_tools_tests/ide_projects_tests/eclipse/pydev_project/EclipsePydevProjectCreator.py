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
from ide_projects.eclipse.pydev_project.EclipsePydevProjectCreator import EclipsePydevProjectCreator

class EclipsePydevProjectCreator_test(ProjectCreatorBase):
  def run(self):
    config_dict = dict(projectName='MepintaCore')
    test_instace = EclipsePydevProjectCreator(self.context, config_dict=config_dict)
    projects_root = '/home/jduo/001-Mepinta/EclipseProjects_GitRepo/mepinta_test_folders/EclipseProjects'
    translation_dict = {}
    overwrite = True
    test_instace.create(projects_root, translation_dict, overwrite)
    return True

def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()
  test = EclipsePydevProjectCreator_test(context=context)
  return test.run()

if __name__ == "__main__":
  print(test_module())
