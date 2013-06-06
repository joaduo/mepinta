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
from mepinta.plugins_manifest import PluginManifestBase, FunctionProperty
from mepinta_python_sdk.props import get_prop_value

class NodeboxRenderer(PluginManifestBase):
  def define(self, inputs, internals, functions, outputs):
    inputs.geometry = 'demov1.Geometry2D'
    functions.render = FunctionProperty()
    functions.render.dpdencies += [inputs.geometry, ]

manifest = NodeboxRenderer

def render(args):
  from nodebox.graphics import BezierPath, strokewidth, fill, directed, push, translate, rotate, pop, drawpath
  geom2d = get_prop_value(args, 'inputs', 'geometry')

  #Do the drawing here!!
  path = BezierPath()
  strokewidth(width=1)
  fill(0)

  ps = geom2d.points
  for b_path in geom2d.bezier_paths:
    if len(b_path) > 4:
      path.moveto(*geom2d.points[b_path[0]])
      for p_num in xrange((len(b_path) - 1) // 3):
        #print b_path,p_num
        path.curveto(ps[b_path[p_num * 3 + 1]][0], ps[b_path[p_num * 3 + 1]][1]
                     , ps[b_path[p_num * 3 + 2]][0], ps[b_path[p_num * 3 + 2]][1]
                     , ps[b_path[p_num * 3 + 3]][0], ps[b_path[p_num * 3 + 3]][1]
                     )

      #    points = path.points(amount=len(glyphs), start=0.05, end=0.95)
      points = path.points(amount=0, start=0.05, end=0.95)
      for angle, pt in directed(points):
          push()
          translate(pt.x, pt.y)
          rotate(angle)
          pop()
      drawpath(path, fill=None, stroke=(0, 0, 0, 1))

if __name__ == "__main__":
  from getDefaultContext import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  PluginManifestAutoTester(getDefaultContext()).test(manifest)#, gui=True)
