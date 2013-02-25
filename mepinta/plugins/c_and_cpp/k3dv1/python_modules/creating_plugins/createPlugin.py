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
from mepinta.context.MepintaContext import MepintaContext
from mepinta.plugins_creation.module_to_cpp.eclipse_project.K3dv1EclipseProjectCreator import K3dv1EclipseProjectCreator
from mepinta.plugins_creation.module_to_cpp.qt_project.K3dv1QtProjectCreator import K3dv1QtProjectCreator

def createPlugin(plugin_module, eclipse_root, translation_dict, overwrite=False):  
  context = MepintaContext('python')  
  plugin_manifest = plugin_module.manifest(context=context)
  eclipse_creator = K3dv1EclipseProjectCreator(context=context)
  eclipse_creator.create(plugin_manifest, eclipse_root, translation_dict, overwrite)

def createPluginQt(plugin_module, qt_root, translation_dict, overwrite=False):  
  context = MepintaContext('python')  
  plugin_manifest = plugin_module.manifest(context=context)
  eclipse_creator = K3dv1QtProjectCreator(context=context)
  eclipse_creator.create(plugin_manifest, qt_root, translation_dict, overwrite)


if __name__ == "__main__":
  pass
