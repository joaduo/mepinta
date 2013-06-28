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
'''
Created on Sep 23, 2011

@author: jduo
'''
from proxy.data_model import ProcessorProxy,\
  InOutPropertyProxy, FunctionPropertyProxy
from plugins.python.data_types.Geometry2D_v1.gemoetry2dv1__001 import Path2D
from plugins.python.sdk.props_utilities import getPropValue

def getProcessorProxy(context):
  pp = ProcessorProxy('Geometry2DAddPath')
  #Inputs
  pp.inputs.geometry_2d = InOutPropertyProxy('Geometry2D_v1',1)
  pp.inputs.point_indexes = InOutPropertyProxy('Py_list',1)
  #Outputs
  pp.outputs.geometry_2d = InOutPropertyProxy('Geometry2D_v1',1)
  pp.functions.modifyGeometry = FunctionPropertyProxy()
  
  #Set sinks & dpdencies
  pp.outputs.geometry_2d.dpdencies += [pp.functions.modifyGeometry]
  pp.functions.modifyGeometry.dpdencies += [pp.inputs.geometry_2d,pp.inputs.point_indexes]
  
  #We can work directly on the output
  pp.non_cached_capable += ['geometry_2d']
  
  return pp

def modifyGeometry(args):
  #Inputs
  point_indexes = getPropValue(args, 'inputs','point_indexes')
  #Outputs
  geom2d = getPropValue(args, 'outputs','geometry_2d')
  #Big deal!!
  max_point_index = len(geom2d.points)
  p_indexes_new = filter(lambda x: isinstance(x, int) and x < max_point_index and x >= 0, point_indexes)
  geom2d.bezier_paths.append(p_indexes_new)

if __name__ == '__main__':
  pp = getProcessorProxy(None)
  debugPrint( pp)
