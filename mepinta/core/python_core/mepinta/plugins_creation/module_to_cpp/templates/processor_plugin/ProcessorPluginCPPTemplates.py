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
from mepinta.plugins_creation.templates.base import PluginTemplatesBase
from common.path import joinPath
from mepinta.plugins_creation.module_to_cpp.templates.processor_plugin.ProcessorCPP import ProcessorCPP

class ProcessorPluginCPPTemplates(PluginTemplatesBase):
  def _getTemplatesRoot(self):
    import mepinta.plugins_creation.module_to_cpp.templates.processor_plugin as processor_plugin
    return joinPath(processor_plugin.__path__[0],'repository','cpp_default')
  def _getMapDict(self, plugin_name):
    #Debug, TypeSafe, OrderSafe, Optimized
    return {
            #(DeclarationH,'src/properties/declaration.h'):None,
            #(WrappersH,'src/properties/wrappers.h'):None,
            (ProcessorCPP,'src/processor.cpp'):'src/%s.cpp'%plugin_name,
           }  
        
if __name__ == "__main__":
  pass
