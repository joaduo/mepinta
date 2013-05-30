# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

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
from mepinta.plugins_manifest import PluginManifestBase, FunctionProperty

class Circle(PluginManifestBase):
  def define(self, inputs, internals, functions, outputs):
    #Inputs
    inputs.geometry = 'demov1.Geometry2D' #TODO: review if necessary for nonCached
    inputs.radius = 'float'
    inputs.segments = 'int'
    #Outputs
    outputs.geometry = 'demov1.Geometry2D'
    functions.create_geometry = FunctionProperty()

    #Set sinks & dpdencies
    outputs.geometry.dpdencies += [functions.create_geometry]
    functions.create_geometry.dpdencies += [ inputs.geometry,
                                             inputs.radius,
                                             inputs.segments, ]

    #We can work directly on the output
    self.nonCached(outputs.geometry)

manifest = Circle

import math
from mepinta_python_sdk.props import get_prop_value

def create_geometry(args):
  #Inputs
  radius = get_prop_value(args, 'inputs', 'radius')
  segments = get_prop_value(args, 'inputs', 'segments')
  #Outputs
  geometry = get_prop_value(args, 'outputs', 'geometry')
  #Big deal!!
  segments = int(segments)
  if segments < 2:
    segments = 2
  points = segments * 3
  delta = math.pi * 2 / points
  for point_i in range(points):
    #TODO: use the correct approximation of a circle's arc with a cubic function
    p = [ math.cos(point_i * delta) * radius
         , math.sin(point_i * delta) * radius]
    geometry.points.append(p)
  geometry.bezier_paths.append(range(points) + [0])

if __name__ == "__main__":
  from default_context import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  context = getDefaultContext()
  PluginManifestAutoTester(context=context).test(manifest)