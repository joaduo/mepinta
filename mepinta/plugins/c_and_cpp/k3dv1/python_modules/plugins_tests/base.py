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
from pipeline_backend.logging.logging import LOG_INFO

class MepintaTestPipeline:
  def __init__(self, context_name, log_level=LOG_INFO):
    pass
  def evalProp(self, prop):
    pass
  def prepareForAnimation(self):
    pass
  def autoAppendNode(self, plugin_package):
    pass
  def appendNode(self, plugin_package, inprop=None, outprop=None):
    pass
  def getPropertiesMap(self, props=None):
    #name:type,node
    pass
  #agregar plugins a traves de módulos
  #generar la lista de inputs para la GUI
    #a partir de un nodo
    #a partir del pipeline
        
if __name__ == "__main__":
  pass
