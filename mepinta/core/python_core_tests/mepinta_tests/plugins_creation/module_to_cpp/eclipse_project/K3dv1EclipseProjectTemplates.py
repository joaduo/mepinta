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
from mepinta.plugins_creation.module_to_cpp.eclipse_project.K3dv1EclipseProjectTemplates import K3dv1EclipseProjectTemplates
from mepinta_tests.dummy_classes.PluginManifestDummy import PluginManifestDummy

class K3dv1EclipseProjectTemplates_test(MepintaTestBase):
  def run(self):
    tested_instance = K3dv1EclipseProjectTemplates(context=self.context)
    target_root = "../.."
    plugin_manifest = PluginManifestDummy(context=self.context)
    templates = tested_instance.getTemplatePerPath(target_root, plugin_manifest=plugin_manifest)
    # templates = K3dv1EclipseProjectTemplates(context=self.context).getTemplatePerPath(target_root, plugin_manifest=plugin_manifest)
    return self.validateOutputTemplates(templates)
  def validateOutputTemplates(self, templates):
    self.log(templates)
    for templ, dir_ in templates.items():
      self.log("%r:%r" % (templ, dir_))
    return True

def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()
  test = K3dv1EclipseProjectTemplates_test(context=context)
  return test.run()

if __name__ == "__main__":
  testModule()
