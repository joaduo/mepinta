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
from mepinta.testing.plugins_testing.test_pipeline.SimpleTestPipeline import SimpleTestPipeline
from mepinta.context.MepintaContext import MepintaContext
from mepinta.testing.plugins_testing.gui.SimpleTestPipelineGui import SimpleTestPipelineGui
from mepinta.testing.plugins_testing.test_pipeline.InotifySimpleTestPipeline import InotifySimpleTestPipeline

def smokeTestModule():
  context = MepintaContext()
#  pline = SimpleTestPipeline(context)
  pline = InotifySimpleTestPipeline(context)

  gui = SimpleTestPipelineGui(context, test_pline=pline)
  import plugins.c_and_cpp.processors.k3dv1.mesh.generators.polyhedron.PolyCube as processor
  node = pline.append(processor)
  pline.setValue(node.inputs.rows, 2)
  pline.setValue(node.inputs.columns, 2)
  pline.setValue(node.inputs.slices, 2)
  pline.setValue(node.inputs.width, 1.)
  pline.setValue(node.inputs.height, 1.)
  pline.setValue(node.inputs.depth, 1.)
  pline.defaultEvaluated.append(node.outputs.mesh)
  print node
  gui.run()

if __name__ == "__main__":
  smokeTestModule()
