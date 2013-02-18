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
  on_template, DictionaryBasedTranslator
from mepinta.plugins_creation.module_to_cpp.templates.processor_plugin.properties.FunctionPropertiesDeclaration import FunctionPropertiesDeclaration
from common.path import joinPath
from mepinta.plugins_manifest.proxy.data_model import GenericEnumProxy

gpl_header = '''//Mepinta
//Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar
//
//This file is part of Mepinta.
//
//Mepinta is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//Mepinta is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Mepinta. If not, see <http://www.gnu.org/licenses/>.'''

function_template = '''
//Give a brief explanation for your function property.
EXPORTED_SYMBOL
int ##functionName(MP_args* args){
  ##inputsDeclaration
  ##outputsDeclaration
  
  log_info("Printing from ##functionName.\\\\n");

  return EXIT_NORMAL;
}
'''

class ProcessorCPP(ManifestAndFileTemplateBase):
#  def getOverwritePolicy(self):
#    '''Default overwrite policy.'''
#    return False
  @on_template
  def genericEnums(self):
    cpp_string = ''
    for container in self.plugin_manifest.containers.values():
      for name,prop in container.get_properties(GenericEnumProxy).items():
        cpp_string += '//Generic enum %s_t\n'%name
        cpp_string += 'typedef enum \n{\n'
        cpp_list = []
        inverted_dict = prop.invertedDict()
        for value in sorted(inverted_dict.keys()):
          label = inverted_dict[value]
          cpp_list.append('  %s=%s'%(label,value))
        cpp_string += ',\n'.join(cpp_list)
        cpp_string += '\n} %s_t;\n'%name
    return cpp_string
  @on_template
  def pluginName(self):
    return self.plugin_manifest.getName()
  @on_template
  def licenseHeader(self):
    return gpl_header
  @on_template
  def cppIncludes(self):
    include_template = '#include <data_types/%s.h>\n'
    includes_str = '\n//Included Data Types\n'
    for data_type in self._requiredDataTypes():
      split_path = data_type.split('.')
      includes_str += include_template%joinPath(split_path,split_path[-1])
    return includes_str
  @on_template
  def processorFunctions(self):
    content = ''
    for name,proxy in self.plugin_manifest.get_functions_dict().items():
      self.context.log.debug('Processing function %s template'%name)
      props_declaration = FunctionPropertiesDeclaration(self.context, proxy=proxy, plugin_manifest=self.plugin_manifest)
      #translation_dict = {'functionName':name,
      #                    'inputsDeclaration':'//Declare Inputs\n  %s_INPUTS_DECLARATION();'%name,
      #                    'outputsDeclaration':'//Declare Outputs\n  %s_OUTPUTS_DECLARATION();'%name,
      #                    }
      translation_dict = {'functionName':name,
                          'inputsDeclaration':props_declaration.getInputs(),
                          'outputsDeclaration':props_declaration.getOutputs(),
                          #'outputsReplacement':props_declaration.getReplacements(),
                          }
      content += str(DictionaryBasedTranslator(self.context, template=function_template, translation_dict=translation_dict))
    return content

if __name__ == "__main__":
  pass
