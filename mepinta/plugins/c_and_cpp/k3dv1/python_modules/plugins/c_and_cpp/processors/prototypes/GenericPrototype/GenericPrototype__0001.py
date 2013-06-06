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

from mepinta.plugins_manifest import PluginManifestBase, FunctionProperty, \
  directed, Functum, DataProperty

class GenericPrototype(PluginManifestBase):
  def define(self, inputs, internals, functions, outputs):
    inputs.count = 'k3d::int32_t'
    inputs.phrase = 'k3d::string_t'
    functions.fooFunction = FunctionProperty()
    
    functions.fooFunction.dpdencies += inputs.count, inputs.phrase
    
    #inputs. = DataProperty('')
    #outputs. = DataProperty('')
    #functions. = FunctionProperty()
    #functions..dpdencies += [inputs.,]
    #outputs..dpdencies += [functions.]

manifest = GenericPrototype

if __name__ == "__main__":
  from getDefaultContext import getDefaultContext
  from mepinta.plugins_manifest.PluginManifestTester import PluginManifestAutoTester
  PluginManifestAutoTester(getDefaultContext()).test(manifest(getDefaultContext()))
