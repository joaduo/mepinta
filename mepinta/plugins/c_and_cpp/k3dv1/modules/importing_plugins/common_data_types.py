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
from importing_plugins.base import createPackageImport, importDataTypes

def importCommonDataTypes():
  eclipse_root_basic = "/home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/Basic/DataTypes"
  data_types_basic= {
                    "c.builtin" : "charp int double uint".split(),
                    "cpp.std" : "string".split(),
                    "mepinta" : "internal_any functum".split(),
                   }
  data_type_imports = [(data_types_basic,eclipse_root_basic)]
  
  eclipse_root_GC = "/home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/Basic/Boehm_GC"
  data_types_GC= {"c.boehm_gc" : "charp".split(), }  
  data_type_imports.append((data_types_GC, eclipse_root_GC))
  
  importDataTypes(data_type_imports)

if __name__ == "__main__":   
  importCommonDataTypes()

