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
from PackageCreator import PackageCreator
from ModuleCreator import ModuleCreator
import os
from base import PluginCreatorBase


class PluginPackageCreator(PluginCreatorBase):

    def __post_init__(self):
        self.package_creator = PackageCreator(context=self.context)
        self.module_creator = ModuleCreator(context=self.context)

    def createPlugin(self, plugin_fdirs):
        if not self._pathExists(plugin_fdirs.getPath("package"), package=True):
            self.package_creator.create(
                plugin_fdirs.getPath("package", split=True))
        if not self._pathExists("%s.py" % plugin_fdirs.getPath("module")):
            self.module_creator.create(plugin_fdirs.getPath("module"),
                                       template=plugin_fdirs.type_,
                                       tmplt_values={'name': plugin_fdirs.name})
        if plugin_fdirs.lang_group == "c_and_cpp":
            if not self._pathExists(plugin_fdirs.getPath("code")):
                os.mkdir(plugin_fdirs.getPath("code"))
            if plugin_fdirs.plugin_group == 'data_types':
                if not self._pathExists(plugin_fdirs.getPath("data_types_include")):
                    os.makedirs(plugin_fdirs.getPath("data_types_include"))

if __name__ == "__main__":
    context = MepintaContext('python')
    logger = context.getConfig('log')
    logger.setLevel(40)
    pc = PluginPackageCreator(context=context)
    #plugin_fdirs = PluginStorageConfig("DeformationExpression", "c_and_cpp", "processor", "Geometry2D.modifier", "deformation_expression", 1)
    #plugin_fdirs = PluginStorageConfig("Matrix4", "c_and_cpp", "data_types", "k3dv1", "k3dv1_Matrix4", 1)
    from PluginStorageConfig import PluginStorageConfig
    plugin_fdirs = PluginStorageConfig(
        "Matrix4", "c_and_cpp", "data_types", "", "k3dv1_Matrix4", 1)
    pc.createPlugin(plugin_fdirs)
    from import_cpp.PluginCPPImplementationImporter import PluginCPPImplementationImporter
    pi = PluginCPPImplementationImporter(context=context)
    pi.importPlugin(plugin_fdirs)
