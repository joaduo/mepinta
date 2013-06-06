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
from plugins_tests.base.K3dMeshPluginTest import K3dMeshPluginTest
from mepinta.plugins_manifest import DataProperty 

class BlendDeformation(K3dMeshPluginTest):
  def __post_init__(self):
    import plugins.c_and_cpp.processors.k3dv1.mesh.modifiers.deformation.BlendDeformation as blend
    self.tested_processors.append(blend)

  def definePluginPipeline(self, test_pline):
    import plugins.c_and_cpp.processors.k3dv1.mesh.modifiers.deformation.DeformationExpression as deform
    
    sphere_node = test_pline.getLastNode()
    deform_node = test_pline.append(deform) 
    blend_node = test_pline.append(self.tested_processors[0], connect=False)
    
    test_pline.connect(blend_node.inputs.original_mesh, sphere_node.outputs.mesh)
    test_pline.connect(blend_node.inputs.mesh, deform_node.outputs.mesh)
    
    test_pline.setLastNode(blend_node)
    
    test_pline.setValue(blend_node.inputs.blend_amount, 0.5)
    test_pline.setValue(deform_node.inputs.x_function, 'z')
    test_pline.setValue(deform_node.inputs.y_function, 'x')
    test_pline.setValue(deform_node.inputs.z_function, 'y')
    deform_node.inputs.force_name = DataProperty('k3d::string_t')
    deform_node.inputs.force = DataProperty('k3d::double_t')
    test_pline.syncNode(deform_node)
    test_pline.connect(deform_node.internals.deformMesh, deform_node.inputs.force_name)
    test_pline.connect(deform_node.internals.deformMesh, deform_node.inputs.force)

  def getTimeParameters(self):
    return self.time.startEndStepSleep(start=0., end=0., step=1., sleep=0.05)

  def stressPipeline(self, test_pline, time):
    K3dMeshPluginTest.stressPipeline(self, test_pline, time)
    blend_node = test_pline.getNodesDict()['BlendDeformation 1']
    test_pline.setValue(blend_node.inputs.blend_amount, 0.5 + time)

test = BlendDeformation
        
if __name__ == "__main__":
  from pipeline_backend.logging.logging import LOG_INFO
  from mepinta.testing.plugins_testing.test_pipeline.InotifySimpleTestPipeline import InotifySimpleTestPipeline
  from mepinta.testing.plugins_testing.PluginTestAutoTester import PluginTestAutoTester
  from getDefaultContext import getDefaultContext
#  context = getDefaultContext()
#  from mepinta.testing.plugins_testing.nodebox.NodeBoxSimplePipelineOutput import NodeBoxSimplePipelineOutput
#  test_pline = InotifySimpleTestPipeline(context)
#  test(context).definePipeline(test_pline)
#  mw = test_pline.getNodesDict()['K3DMeshWriter 1']
#  test_pline.evaluateProp(mw.functions.writeMesh)
  #NodeBoxSimplePipelineOutput(test_pline.getPipeline(), 600,600).run()
#  PluginTestAutoTester(getDefaultContext(LOG_INFO)).test(test,gui=True)
  PluginTestAutoTester(getDefaultContext(LOG_INFO)).test(test,gui=False)
#  PluginTestAutoTester(getDefaultContext()).test(test)#,gui=False)
