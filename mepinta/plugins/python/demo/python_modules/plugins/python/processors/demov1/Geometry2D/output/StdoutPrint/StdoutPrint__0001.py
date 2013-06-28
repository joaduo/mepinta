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

class manifest(PluginManifestBase):
  def define(self, inputs, internals, functions, outputs):
    #Inputs
    inputs.geometry = 'demov1.Geometry2D'
    #Outputs
    functions.render = FunctionProperty()

    #Set sinks & dpdencies
    functions.render.dpdencies += [ inputs.geometry ]

def render(args):
  from mepinta_python_sdk.props import get_prop_value
  from pipeline_backend.logging.logging import log_info
  #Inputs
  geometry = get_prop_value(args, 'inputs', 'geometry')
  stdout_str = ''
  stdout_str += 'points:%s ' % geometry.points
  stdout_str += 'bezier_paths:%s' % geometry.bezier_paths
  stdout_str += '\nSummary points:%s paths:%s ' % (len(geometry.points), len(geometry.bezier_paths))
  if len(geometry.bezier_paths):
    stdout_str += '\nFirst bezier path length:%s ' % len(geometry.bezier_paths[0])
  log_info(stdout_str)

if __name__ == "__main__":
  from getDefaultContext import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  context = getDefaultContext()
  PluginManifestAutoTester(context=context).test(manifest)
