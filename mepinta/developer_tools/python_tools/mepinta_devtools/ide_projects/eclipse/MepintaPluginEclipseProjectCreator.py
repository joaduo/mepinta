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

class MepintaPluginEclipseProjectCreator(FrameworkBase):
  def createK3dv1PluginProject(self, projects_dir, plugin_manifest):
    templates_config = [
      #      FileToFileMap(CProjectXML(), '.cproject',),
      #      FileToFileMap(ProcessorCPP(), 'src/%s.cpp' % plugin_manifest.getName())
      # TODO: Plugin.cpp
    ]
    config_dict = dict(plugin_manifest=plugin_manifest)
    project_name = plugin_manifest.getName()
    self.ep_creator.createCDT(projects_dir, project_name, config_dict=config_dict, templates_config=templates_config, template_set='cdt_k3dv1_plugin', create_src=False)


def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  testModule()
