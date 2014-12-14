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
from creating_plugins.createPlugin import createPlugin
from mepinta.context.MepintaContext import MepintaContext
from mepinta.plugins_creation.PluginStorageConfig import PluginStorageConfig
from importing_plugins.base import addOption
from mepinta.plugins_creation.PluginPackageCreator import PluginPackageCreator
from mepinta.plugins_creation.import_cpp.PluginCPPImplementationImporter import PluginCPPImplementationImporter


def getModulePackagePath(module):
    full_path = module.__name__
    path_list = full_path.split('.')[3:-2]
    return '.'.join(path_list)


def createK3dv1PortAndImport(modules, overwrite=False, config_options={}):
    context = MepintaContext('python')
    plugins_root = "/home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/Mepinta/Mepinta_k3dv1_Plugins/src/plugins"
    eclipse_root = '/home/jduo/001-Mepinta/EclipseProjects_Basic_Data_Types/k3dv1_Prototypes'
    addOption(config_options, "plugins_root", plugins_root)
    addOption(config_options, "eclipse_root", eclipse_root)
    addOption(config_options, 'minor_version_format', '%04d')
    for plugin_module in modules:
        createPlugin(
            plugin_module, eclipse_root, translation_dict={}, overwrite=overwrite)
        name = plugin_module.manifest(context).getName()
        plugin_fdirs = PluginStorageConfig(name, 'c_and_cpp', type_='processors', package=getModulePackagePath(
            plugin_module), module_name=name, minor_version=1, **config_options)
        pc = PluginPackageCreator(context=context)
        pc.createPlugin(plugin_fdirs)
        pi = PluginCPPImplementationImporter(context=context)
        pi.importPlugin(plugin_fdirs)


def createK3dv1Port(modules, overwrite=False):
    eclipse_root = '/home/jduo/001-Mepinta/EclipseProjects_Basic_Data_Types/k3dv1_Prototypes'
    for plugin_module in modules:
        createPlugin(
            plugin_module, eclipse_root, translation_dict={}, overwrite=overwrite)

if __name__ == "__main__":
    modules = []
#  import plugins.c_and_cpp.processors.k3dv1.mesh.generators.polyhedron.PolyTorus.PolyTorus__0001 as module
#  modules.append(module)
#  import plugins.c_and_cpp.processors.k3dv1.mesh.generators.polyhedron.PolyCylinder.PolyCylinder__0001 as module
#  modules.append(module)
#  import plugins.c_and_cpp.processors.k3dv1.mesh.generators.polyhedron.PolyCube.PolyCube__0001 as module
#  modules.append(module)
#  import plugins.c_and_cpp.processors.k3dv1.mesh.input.file.OBJMeshReader.OBJMeshReader__0001 as module
#  modules.append(module)
#  import plugins.c_and_cpp.processors.k3dv1.mesh.input.file.SVGMeshReader.SVGMeshReader__0001 as module
#  modules.append(module)
#  import plugins.c_and_cpp.processors.k3dv1.mesh.output.file.K3DMeshWriter.K3DMeshWriter__0001 as module
#  modules.append(module)
#  import plugins.c_and_cpp.processors.k3dv1.mesh.input.file.K3DMeshReader.K3DMeshReader__0001 as module
#  modules.append(module)
#  import plugins.c_and_cpp.processors.k3dv1.mesh.generators.polyhedron.PolyCone.PolyCone__0001 as module
#  modules.append(module)
#  import plugins.c_and_cpp.processors.k3dv1.mesh.generators.polyhedron.PolySphere.PolySphere__0001 as module
#  modules.append(module)
#  import plugins.c_and_cpp.processors.k3dv1.mesh.generators.polyhedron.PolyGrid.PolyGrid__0001 as module
#  modules.append(module)
#  import plugins.c_and_cpp.processors.k3dv1.mesh.modifiers.deformation.DeformationExpression.DeformationExpression__0001 as module
#  modules.append(module)
#  import plugins.c_and_cpp.processors.k3dv1.mesh.modifiers.polyhedron.ExtrudeFaces.ExtrudeFaces__0001 as module
#  modules.append(module)
    import plugins.c_and_cpp.processors.prototypes.GenericPrototype.GenericPrototype__0001 as module
    modules.append(module)
    createK3dv1PortAndImport(modules, overwrite=False)
