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

from mepinta.plugins_creation.eclipse_project.EclipseProjectCreator import EclipseProjectTemplates,\
    EclipseProjectCreator


def create_test():
    from mepinta.context.MepintaContext import MepintaContext
    context = MepintaContext('python')
    import plugins.c_and_cpp.processors.k3dv1.Mesh.modifiers.deformation.DeformationExpression.DeformationExpression__0001 as plugin_module
    plugin_manifest = plugin_module.manifest(context=context)
    eclipse_projects_root = "/home/jduo/001-Mepinta/tmp/eclipse_example"
    eclipse_templates = EclipseProjectTemplates(context=context)
    templates = eclipse_templates.getTemplatePerPath(
        plugin_manifest, eclipse_projects_root)
    context.get_log().info(templates)
    eclipse_creator = EclipseProjectCreator(context=context)
    eclipse_creator.create(
        plugin_manifest, eclipse_projects_root, translation_dict={}, overwrite=True)

if __name__ == "__main__":
    create_test()
