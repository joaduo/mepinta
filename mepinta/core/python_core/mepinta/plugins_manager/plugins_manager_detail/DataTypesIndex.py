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

class DataTypesIndex(FrameworkBase):
  def __post_init__(self):
    pass
  def generate_index(self):
    #for each group package or data type package list its internal modules
    #and packages
    #for importer, modname, ispkg in pkgutil .iter_modules(plugin_package.__path__, prefix):
    #si son todos paquetes, entonces es un grupo?
    #si hay un módulo que comienza con el nombre del paquet y además implementa un plugin?
    #si quieren hacer un override entonces en __init__.py tienen que poner is_plugin_group=True
    pass
  
        
if __name__ == "__main__":
  pass
