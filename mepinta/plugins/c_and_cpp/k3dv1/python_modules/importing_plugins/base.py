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

from mepinta.plugins_creation.PluginStorageConfig import PluginStorageConfig
from mepinta.context.MepintaContext import MepintaContext
from mepinta.plugins_creation.PluginPackageCreator import PluginPackageCreator
from mepinta.plugins_creation.import_cpp.PluginCPPImplementationImporter import PluginCPPImplementationImporter

plugins_root = "/home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/Mepinta/Mepinta_k3dv1_Plugins/src/plugins"
# plugins_root =  "/home/jduo/001-Mepinta/tmp/plugins"

def addOption(config_options, name, value):
  if name not in config_options:
    config_options[name] = value

def createPackageImport(name, type_, package, module_name, **config_dict):
  context = MepintaContext('python')  # TODO: use getDefaultContext or pass the context
  logger = context.get_config('log')
  logger.setLevel(50)

  addOption(config_dict, "plugins_root", plugins_root)
  # TODO: minor_version = 1
  plugin_fdirs = PluginStorageConfig(name, "c_and_cpp", type_, package, module_name, 1, **config_dict)
  pc = PluginPackageCreator(context=context)
  pc.createPlugin(plugin_fdirs)
  pi = PluginCPPImplementationImporter(context=context)
  pi.importPlugin(plugin_fdirs)

def importPlugins(plugin_imports, plugins_type, **config_dict):
  for data_types, eclipse_root in plugin_imports:
    for package, p_names in data_types.items():
      for module_name in p_names:
        name = module_name
        config_dict.update(dict(eclipse_root=eclipse_root, minor_version_format='%04d'))
        createPackageImport(name, plugins_type, package, module_name, **config_dict)

def importProcessors(processors_imports, **config_dict):  # TODO: don't use **config_dict for deeper levels
  return importPlugins(processors_imports, plugins_type="processors", **config_dict)

def importDataTypes(data_type_imports, **config_dict):
  config_dict.update(dict(data_types_include_root="/home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/Mepinta/Mepinta_k3dv1_DataTypes_Includes/data_types"))
  return importPlugins(data_type_imports, plugins_type="data_types", **config_dict)

if __name__ == "__main__":
  pass
