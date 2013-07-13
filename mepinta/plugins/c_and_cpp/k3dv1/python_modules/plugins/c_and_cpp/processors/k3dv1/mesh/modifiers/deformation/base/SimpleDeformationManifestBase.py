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
  directed, Functum

class SimpleDeformationManifestBase(ProcessorManifestBase):
  def _superClassDefine(self, inputs, internals, functions, outputs):
    '''Creates the common topology pipeline for SimpelMeshDeformation modifiers.'''
    inputs.mesh = DataProperty('k3d::mesh')
    outputs.mesh = DataProperty('k3d::mesh')
    internals.deformMesh = Functum()
    functions.demuxMeshSignal = FunctionProperty()
    
    internals.deformMesh.dpdencies +=[directed('>',inputs.mesh),]
    
    functions.demuxMeshSignal.dpdencies += [internals.deformMesh,
                                            inputs.mesh,]
    outputs.mesh.dpdencies += [functions.demuxMeshSignal,
                               directed('<',internals.deformMesh),]
    return internals.deformMesh

  def define(self, inputs, internals, functions, outputs, deformMesh):
    '''
      Implement this method on children classes.
      Example:
        inputs.rows = DataProperty('uint')
        deformMesh.dpdencies += [inputs.rows]
    '''
    pass

manifest = SimpleDeformationManifestBase

if __name__ == "__main__":
  from mepinta.context.MepintaContext import MepintaContext
  from mepinta.plugins_manifest.PluginManifestTester import PluginManifestTester
  context = MepintaContext('c_and_cpp')
  plugin_instance = manifest(context=context)
  context.log(manifest)
  PluginManifestTester(context=context).test(plugin_instance)
