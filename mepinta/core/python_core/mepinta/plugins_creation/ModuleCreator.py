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

class Templates(object):
  processors ="""# -*- coding: utf-8 -*-
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

from mepinta.plugins_manifest import PluginManifestBase, DataProperty, FunctionProperty, \\
  directed, Functum

class ##name(PluginManifestBase):
  def define(self, inputs, internals, functions, outputs):
    #inputs. = DataProperty('')
    #outputs. = DataProperty('')
    #functions. = FunctionProperty()
    pass
    #functions..dpdencies += [inputs.,]
    #outputs..dpdencies += [functions.]

manifest = ##name

if __name__ == "__main__":
  from getDefaultContext import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  PluginManifestAutoTester(getDefaultContext()).test(manifest, gui=True)
"""
  data_types ="""
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

data_type_description = {
 'plugin_url':'http://',
 'future_plugin_url':'http://',
 'additional_urls':{},
 'authors':'',
 'description':'''.''',
 'changes':'',
 'api':'##api', #What kind of api is available for accessing this data
}

"""
  empty =""
  processor = processors
  data_type = data_types

class ModuleCreator(FrameworkBase):
  def __post_init__(self):
    self.templates = Templates()
  def getContents(self, template,tmplt_values):
    if not hasattr(self.templates, template):
      self.log.warning("There is no template %r for module creator."%template)
      return ""
    else:
      contents = getattr(self.templates, template)
      for name, value in tmplt_values.items():
        contents = contents.replace('##%s'%name, value)
      return contents
  def create(self, os_path, template="empty", tmplt_values={}):
    if not os_path.lower().endswith('.py'):
      os_path = '%s.py'%os_path
    self.log.verbose('Creating module at %r'%(os_path))
    file_contents = self.getContents(template,tmplt_values)
    f = open(os_path,"w") 
    if file_contents != "":
      f.write(file_contents)
    f.close()
        
if __name__ == "__main__":
  pass
