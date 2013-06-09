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

props_declaration_template='''
#define ${FUNCTION_NAME_INPUTS_DECLARATION} \
  ${INPUTS_DECLARATION}
  
#define ${FUNCTION_NAME_OUTPUTS_DECLARATION} \
  ${OUPUTS_DECLARATION}  
'''

class DeclarationH(ManifestAndFileTemplateBase):
  @on_template
  def functionsPropertiesDeclaration(self):
    #return None
    return ''
        
if __name__ == "__main__":
  pass
