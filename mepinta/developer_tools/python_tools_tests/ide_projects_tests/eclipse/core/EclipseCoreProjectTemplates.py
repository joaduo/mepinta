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
from ide_projects.eclipse.core.EclipseCoreProjectTemplates import EclipseCoreProjectTemplates

class EclipseCoreProjectTemplates_test(MepintaTestBase):
  def run(self):
    tested_instance = EclipseCoreProjectTemplates(context=self.context, config_dict={})
    target_root = "../.."
    templates = tested_instance.getTemplatePerPath(target_root)

    return self.validateOutputTemplates(templates)
  def validateOutputTemplates(self, templates):
    self.log(templates)
    for templ, dir_ in templates.items():
      self.log("%r:%r" % (templ, dir_))
    return True

def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()
  test = EclipseCoreProjectTemplates_test(context=context)
  return test.run()

if __name__ == "__main__":
  test_module()
