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
from mepinta.plugins_manifest import ProcessorManifestBase, DataProperty, FunctionProperty, \
Functum, directed

class SimpleGeometryModifierBase(ProcessorManifestBase):
  def _superClassDefine(self, inputs, internals, functions, outputs):
    '''
      Creates a common geometry pipeline for mesh modifiers. 
      (demuxing the mesh Topology and Geometry updates signals)
    '''
    inputs.mesh = DataProperty('k3d::mesh')
    outputs.mesh = DataProperty('k3d::mesh')
    
    internals.updateMesh = Functum()
    functions.demuxMeshSignal = FunctionProperty()
    
    internals.updateMesh.dpdencies +=[directed('>',inputs.mesh),]
    
    functions.demuxMeshSignal.dpdencies += [internals.updateMesh,
                                            inputs.mesh,]
    outputs.mesh.dpdencies += [functions.demuxMeshSignal,
                               directed('<',internals.updateMesh),]
    return internals.updateMesh

  def define(self, inputs, internals, functions, outputs, updateMesh):
    '''
      Implement this method on children classes.
      Example:
        inputs.rows = DataProperty('uint')
        updateMesh.dpdencies += [inputs.rows]
    '''
    pass
  
        
if __name__ == "__main__":
  pass
