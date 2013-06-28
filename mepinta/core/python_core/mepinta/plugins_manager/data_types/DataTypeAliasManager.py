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

class DataTypeAliasManager(FrameworkBase):
  def __getAliasDict(self, backend_name):
    if backend_name == 'python':
      return self._getPythonAliasDict()
    elif backend_name == 'c_and_cpp':
      return self._getCAndCppAliasDict()
    else:
      return self._getPythonAliasDict()

  def getFunctumAliases(self):
    functum_aliases = []
    alias_dict = self.__getAliasDict(self.context.backend_name)
    functum_name = alias_dict['functum']
    for alias, name in alias_dict.items():
      if name == functum_name:
        functum_aliases.append(alias)
    return functum_aliases

  def _getPythonAliasDict(self):
    alias_dict = {
                  'int':'python.builtin.int',
                  'float':'python.builtin.float',
                  'str':'python.builtin.str',
                  'list':'python.builtin.list',
                  'dict':'python.builtin.dict',
                  'actiontree.Processor':'python.builtin.str',
                  'actiontree.NodesSelection':'python.builtin.list',
                  'functum':'mepinta.functum',
                  #'internal_any':'mepinta.internal_any', #TODO review
                  }
    return alias_dict

  def _getCAndCppAliasDict(self):
    alias_dict = {
                  'std::string':'cpp.std.string',
                  ##
                  'MP_generic_enum':'c.builtin.int',
                  'mepinta::generic_enum':'c.builtin.int',#'mepinta.generic_enum', #MP_generic_enum
                  'functum':'mepinta.functum', #MP_functum
                  'MP_functum':'mepinta.functum', #MP_functum
                  'mepinta::functum':'mepinta.functum', #MP_functum
                  'MP_internal_any':'mepinta.internal_any', #MP_internal_any
                  'mepinta::internal_any':'mepinta.internal_any', #MP_internal_any
                  #k3d
                  'k3d::mesh':'k3dv1.mesh',#'k3dv1.mesh',
                  #'k3d::filesystem::path':'k3dv1_FilesystemPath',#'k3dv1.filesystem.path',
                  'k3d::filesystem::path':'c.builtin.charp',#'k3dv1.filesystem.path',
                  'k3d::imaterial':'k3dv1.imaterial', #k3dv1.imaterial
                  #####==========Correct ones!
                  'int':'c.builtin.int',
                  'double':'c.builtin.double',
                  'uint':'c.builtin.uint',
                  'char*':'c.builtin.charp',#'c.boehm_gc.charp',
                  'charp':'c.builtin.charp',#'c.boehm_gc.charp',
                  'std::string*':'cpp.std.string',
                  ##
                  'MP_generic_enum*':'c.builtin.int',
                  'mepinta::generic_enum*':'c.builtin.int',#'mepinta.generic_enum', #MP_generic_enum
                  'MP_functum*':'mepinta.functum', #MP_functum
                  'mepinta::functum*':'mepinta.functum', #MP_functum
                  'MP_internal_any*':'mepinta.internal_any', #MP_internal_any
                  'internal_any':'mepinta.internal_any', #MP_internal_any
                  'mepinta::internal_any*':'mepinta.internal_any', #MP_internal_any
                  ##
                  'k3d::int32_t':'c.builtin.int', #'c_builtin.int'
                  'k3d::double_t':'c.builtin.double',
                  'k3d::string_t':'cpp.std.string', #'std.string'
                  'k3d::bool_t':'c.builtin.int',
                  ##
                  'k3d::mesh*':'k3dv1.mesh',#'k3dv1.mesh',
                  #'k3d::filesystem::path':'k3dv1_FilesystemPath',#'k3dv1.filesystem.path',
                  'k3d::filesystem::path*':'c.builtin.charp',#'k3dv1.filesystem.path',
                  'k3d::imaterial*':'k3dv1.imaterial', #k3dv1.imaterial
                 }
    return alias_dict

  def getRealDataTypeName(self, data_type_alias):
    '''
      Support data_type aliases. (avoiding redundant data types)
    '''
    if data_type_alias == 'k3d::filesystem::path*':
      self.log.w("Conversion of %s is to char*.(this is wrong and is just a hack) WORK IN PROGRESS!" % data_type_alias)

    alias_dict = self.__getAliasDict(self.context.backend_name)
    if data_type_alias in alias_dict:
      return alias_dict[data_type_alias]
    else:
      return data_type_alias

def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  testModule()
