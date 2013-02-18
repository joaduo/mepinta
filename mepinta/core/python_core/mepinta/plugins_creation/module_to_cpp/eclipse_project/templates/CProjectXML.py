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
from mepinta.plugins_creation.templates.base import ManifestAndFileTemplateBase,\
  on_template

class CProjectXML(ManifestAndFileTemplateBase):
  external_includes = '''/usr/lib/glibmm-2.4/include
/usr/include/glibmm-2.4
/usr/lib/x86_64-linux-gnu/glib-2.0/include
/usr/lib/glib-2.0/include
/usr/include/glib-2.0
/usr/include/sigc++-2.0
/usr/lib/sigc++-2.0/include'''
  eclipse_includes = '''&quot;${workspace_loc:/k3dv1_Libs/include}&quot;
&quot;${workspace_loc:/k3dv1_Libs/boost}&quot;
&quot;${workspace_loc:/Mepinta_SDK/include_new}&quot;
&quot;${workspace_loc:/k3dv1MPExtension}&quot;
&quot;${workspace_loc:/Mepinta_k3dv1_DataTypes_Includes}&quot;'''
  def _includeXMLFromList(self, include_list):
    item_template = '<listOptionValue builtIn="false" value="%s"/>\n'
    xml_string = ''
    for include_dir in include_list:
      xml_string += item_template%include_dir
    return xml_string
  @on_template
  def includeDirs(self):
    xml_string = self._includeXMLFromList(self.external_includes.splitlines())
    xml_string += self._includeXMLFromList(self.eclipse_includes.splitlines())
    #xml_string += self._includeXMLFromTypes(self._requiredDataTypes())
    return xml_string
  @on_template
  def compilerArgs(self):
    return "-c -fmessage-length=0 -fPIC -fvisibility=hidden -D k3d=k3dv1"
  @on_template
  def linkerArgs(self):
    return "-shared"

        
if __name__ == "__main__":
  pass
