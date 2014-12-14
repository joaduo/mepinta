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
from mepinta.plugins_creation.module_to_cpp.eclipse_project.templates.CProjectXML import CProjectXML
from mepinta.plugins_creation.module_to_cpp.eclipse_project.templates.ProjectXML import ProjectXML
from mepinta.plugins_creation.templates.base import PluginTemplatesBase
from mepinta.plugins_creation.module_to_cpp.templates.processor_plugin.ProcessorCPP import ProcessorCPP


class K3dv1EclipseProjectTemplates(PluginTemplatesBase):

    '''Maps the templates files and their corresponding translators classes to the
    path for the final translated file.
    '''

    def _getTemplatesRoot(self):
        import mepinta.plugins_creation.module_to_cpp.eclipse_project as eclipse_project
        return self._buildTemplateRoot(eclipse_project, ['repository', 'k3dv1'])

    def _getMapDict(self, plugin_manifest):
        return {
            (ProcessorCPP, 'src/processor.cpp'): 'src/%s.cpp' % plugin_manifest.getName(),
                (CProjectXML, 'cproject.xml'): '.cproject',
                (ProjectXML, 'project.xml'): '.project',
        }

if __name__ == "__main__":
    pass
