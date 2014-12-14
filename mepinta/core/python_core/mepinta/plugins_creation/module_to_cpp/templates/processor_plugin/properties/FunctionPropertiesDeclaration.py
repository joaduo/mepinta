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
from mepinta.plugins_creation.templates.base import TemplateTranslatorBase
from mepinta.plugins_manifest import DataProperty, FunctionProperty, Functum,\
    GenericEnum
from mepinta.plugins_manifest.proxy.data_model import InOutPropertyProxyBase


class FunctionPropertiesDeclaration(TemplateTranslatorBase):

    def __post_init__(self, proxy, plugin_manifest):
        self.proxy = proxy
        self.plugin_manifest = plugin_manifest

    def __mapGenericEnum(self, input_prop):
        return '%s_t' % input_prop.name

    def __mapDataType(self, prop):
        # generic_enums create its own types (user provided or automatically)
        if isinstance(prop.__qualified__(), GenericEnum):
            return self.__mapGenericEnum(prop)

        data_type_name = prop.data_type_name.split('.')[-1]
        data_type_alias = prop.data_type_alias
        # charp -> is char* in fact
        map = {'charp': 'char*'}
        if data_type_name in map:
            return map[data_type_name]
        # Non references (by value data types)
        by_value = ['double', 'int', 'uint']
        if data_type_name in by_value:
            return data_type_alias
        else:
            return '%s*' % data_type_alias

    def __filterDpdencies(self, dpdencies):
        '''Only get DataProperty and Functums.'''
        new_dpdencies = []
        for dency in dpdencies:
            if isinstance(dency, InOutPropertyProxyBase):
                new_dpdencies.append(dency)
        return new_dpdencies

    def getInputs(self):
        declare_dict = {}
        for input_prop in self.__filterDpdencies(self.proxy.dpdencies):
            declare_dict[input_prop.name] = '  INPUT(%s,%s,args);\n' %(self.__mapDataType(input_prop), input_prop.name)
        inputs_str = '//Declare Inputs\n' + \
            self.__sortDeclaration(declare_dict)
        return inputs_str

    def __sortDeclaration(self, declare_dict):
        declarations = ""
        names = sorted(declare_dict.keys())
        for name in names:
            declarations += declare_dict[name]
        return declarations

    def getOutputs(self):
        declare_dict = {}
        for output_prop in self.__getDpdants().values():
            declare_dict[output_prop.name] = '  //OUTPUT(%s,%s,args);\n' %(self.__mapDataType(output_prop), output_prop.name)
        outputs_str = '//Declare Outputs\n' + \
            self.__sortDeclaration(declare_dict)
        return outputs_str

    def __getDpdants(self):
        dpdants = {}
        for name, container in self.plugin_manifest.containers.items():
            for name, prop in container.getProperties(DataProperty).items():
                for dpdency in prop.dpdencies:
                    if self.proxy == dpdency:
                        dpdants[name] = prop
        return dpdants

    def getReplacements(self):
        return ''


if __name__ == "__main__":
    pass
