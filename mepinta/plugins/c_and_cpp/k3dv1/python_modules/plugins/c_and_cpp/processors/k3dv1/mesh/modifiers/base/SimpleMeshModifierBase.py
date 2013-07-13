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
from mepinta.plugins_manifest import ProcessorManifestBase, DataProperty, FunctionProperty

class SimpleMeshModifierBase(ProcessorManifestBase):
  def _superClassDefine(self, inputs, internals, functions, outputs):
    '''
      Creates a common topology pipeline for simple mesh modifiers. 
      (no demuxing is necessary)
    '''
    #properties
    inputs.mesh = DataProperty('k3d::mesh')
    outputs.mesh = DataProperty('k3d::mesh')
    functions.createMesh = FunctionProperty()
    #functions
    functions.createMesh.dpdencies += inputs.mesh
    #output
    outputs.mesh.dpdencies += functions.createMesh
    #return the new argument for define
    return functions.createMesh

  def define(self, inputs, internals, functions, outputs, createMesh):
    '''
      Implement this method on children classes.
      Example:
        inputs.rows = DataProperty('uint')
        createMesh.dpdencies += [inputs.rows]
    '''
    pass
  
        
if __name__ == "__main__":
  pass
