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
    inputs.x_expression = 'str'
    inputs.y_expression = 'str'
    inputs.time = 'float'
    #Outputs
    outputs.geometry = 'demov1.Geometry2D'
    functions.modifyGeometry = FunctionProperty()

    #Set sinks & dpdencies
    outputs.geometry.dpdencies += [functions.modifyGeometry]
    functions.modifyGeometry.dpdencies += [   inputs.geometry
                                             , inputs.x_expression
                                             , inputs.y_expression
                                             , inputs.time]

    #We can work directly on the output
    self.nonCached(outputs.geometry)

from mepinta_python_sdk.props import get_prop_value

def evalExpression(expression, locals_dict):
  #debugPrint locals_dict
  try:
    value = eval(expression, {"__builtins__":None}, locals_dict)
    return float(value)
  except:
    return 0.

def getFunctionsDict():
  from math import acos, asin, atan, atan2, ceil, cos, cosh, degrees \
                  , e, exp, fabs, floor, fmod, frexp, hypot, ldexp, log, \
                  log10, modf, pi, pow, radians, sin, sinh, sqrt, tan, tanh
  #make a list of safe functions #'math',??
  safe_list = ['abs', 'acos', 'asin', 'atan', 'atan2', 'ceil', 'cos', 'cosh', 'de grees', 'e', 'exp', 'fabs', 'floor', 'fmod', 'frexp', 'hypot', 'ldexp', 'log', 'log10', 'modf', 'pi', 'pow', 'radians', 'sin', 'sinh', 'sqrt', 'tan', 'tanh']
  #use the list to filter the local namespace
  functions_dict = dict([ (k, locals().get(k, None)) for k in safe_list ]) #add any needed builtins back in.
  #functions_dict['abs'] = abs
  return functions_dict

functions_dict = getFunctionsDict()

def modifyGeometry(args):
  #Inputs
  x_expression = get_prop_value(args, 'inputs', 'x_expression')
  y_expression = get_prop_value(args, 'inputs', 'y_expression')
  time = get_prop_value(args, 'inputs', 'time')
  #Outputs
  geom2d = get_prop_value(args, 'outputs', 'geometry')
  #Big deal!!
  locals_dict = {}
  locals_dict.update(functions_dict)
  locals_dict['t'] = time
  for point in geom2d.points:
    locals_dict['x'] = point[0]
    locals_dict['y'] = point[1]
    point[0] = evalExpression(x_expression, locals_dict)
    point[1] = evalExpression(y_expression, locals_dict)

if __name__ == "__main__":
  from getDefaultContext import getDefaultContext
  from mepinta.testing.plugins_testing.PluginManifestAutoTester import PluginManifestAutoTester
  PluginManifestAutoTester(context=getDefaultContext()).test(manifest)
