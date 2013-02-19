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
from mepinta_tests.base import MepintaTestBase
from mepinta.plugins_creation.module_to_cpp.eclipse_project.K3dv1EclipseProjectCreator import K3dv1EclipseProjectCreator
from mepinta_tests.dummy_classes.PluginManifestDummy import PluginManifestDummy

class K3dv1EclipseProjectCreator_test(MepintaTestBase):
  def run(self):
    test_instace = K3dv1EclipseProjectCreator(self.context)
    plugin_manifest = PluginManifestDummy(self.context)
    projects_root = '/home/jduo/001-Mepinta/EclipseProjects_GitRepo/mepinta_test_folders/EclipseProjects'
    translation_dict = {}
    overwrite = False
    test_instace.create(plugin_manifest, projects_root, translation_dict, overwrite)
    return True

def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()
  test = K3dv1EclipseProjectCreator_test(context=context)
  return test.run()

if __name__ == "__main__":
  test_module()

