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

from plugins_manifest import PluginManifestBase, DataProperty, FunctionProperty,\
  Functum, directed
from plugins.python.sdk.props_utilities import get_prop_value,\
  has_changed_by_name

class DeformationExpression(PluginManifestBase):
  def define(self, inputs, internals, functions, outputs):
    #Inputs
    inputs.geometry_2d = DataProperty('Geometry2D_v1',1)
    inputs.x_expression = DataProperty('Py_str',1)
    inputs.y_expression = DataProperty('Py_str',1)
    inputs.time = DataProperty('Py_float',1)
    #Outputs
    outputs.geometry_2d = DataProperty('Geometry2D_v1',1)
    
    internals.modify_geometry = Functum()
    
    functions.demux_signal = FunctionProperty()
    
    #Set sinks & dpdencies
    internals.modify_geometry.dpdencies += [  inputs.x_expression
                                             ,inputs.y_expression
                                             ,inputs.time]
    
    functions.demux_signal.dpdencies += [internals.modify_geometry,
                                         inputs.geometry_2d]
    outputs.geometry_2d.dpdencies += [functions.demux_signal,
                                      directed('<',internals.modify_geometry)
                                      ]
    #We can work directly on the output
    self.non_cached(outputs.geometry_2d)

manifest = DeformationExpression

def eval_expression(expression,locals_dict):
  #print locals_dict
  try:
    value = eval(expression,{"__builtins__":None},locals_dict)
    return float(value)
  except:
    return 0.

def get_func_dict():
  from math import acos, asin, atan, atan2, ceil, cos, cosh, degrees \
                  , e, exp, fabs, floor, fmod, frexp, hypot, ldexp, log, \
                  log10, modf, pi, pow, radians, sin, sinh, sqrt, tan, tanh
  #make a list of safe functions #'math',??
  safe_list = ['abs','acos', 'asin', 'atan', 'atan2', 'ceil', 'cos', 'cosh', 'de grees', 'e', 'exp', 'fabs', 'floor', 'fmod', 'frexp', 'hypot', 'ldexp', 'log', 'log10', 'modf', 'pi', 'pow', 'radians', 'sin', 'sinh', 'sqrt', 'tan', 'tanh'] 
  #use the list to filter the local namespace 
  functions_dict = dict([ (k, locals().get(k, None)) for k in safe_list ]) #add any needed builtins back in. 
  #functions_dict['abs'] = abs 
  return functions_dict

functions_dict = get_func_dict()

def modify_geometry(args):
  #Inputs
  x_expression = get_prop_value(args,'inputs','x_expression') 
  y_expression = get_prop_value(args,'inputs','y_expression')
  time = get_prop_value(args,'inputs','time')
  #Outputs
  geom2d = get_prop_value(args,'outputs','geometry_2d')
  #Big deal!!
  locals_dict = {}
  locals_dict.update(functions_dict)
  locals_dict['t'] =time
  for point in geom2d.points:
    locals_dict['x'] = point[0]
    locals_dict['y'] = point[1]
    point[0] = eval_expression(x_expression,locals_dict)
    point[1] = eval_expression(y_expression,locals_dict)

def demux_signal(args):
#  print(args)
#  print(get_prop_value(args, 'inputs', 'modify_geometry'))
  print("Has changed: %r"%has_changed_by_name(args, 'modify_geometry'))
  functum = get_prop_value(args, 'inputs', 'modify_geometry')
  functum.function_ptr(functum.args)

if __name__ == '__main__':
  from context.MepintaContext import MepintaContext
  from plugins_manifest.PluginManifestTester import PluginManifestTester
  context = MepintaContext('python')
  plugin_instance = manifest(context=context)
  context.log(manifest)
  PluginManifestTester(context=context).test(plugin_instance)

