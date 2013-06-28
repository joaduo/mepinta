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
import random
from plugins.python.sdk.props_utilities import getPropValue

def getProcessorProxy(context):
  pp = ProcessorProxy('Geometry2DRandomPoints')
  #Inputs
  pp.inputs.geometry_2d = InOutPropertyProxy('Geometry2D_v1',1)
  pp.inputs.amount = InOutPropertyProxy('Py_int',1)
  pp.inputs.seed = InOutPropertyProxy('Py_int',1)
  pp.inputs.x_limit = InOutPropertyProxy('Py_float',1)
  pp.inputs.y_limit = InOutPropertyProxy('Py_float',1)  
  #Outputs
  pp.outputs.geometry_2d = InOutPropertyProxy('Geometry2D_v1',1)
  pp.functions.modifyGeometry = FunctionPropertyProxy()
  
  #Set sinks & dpdencies
  pp.outputs.geometry_2d.dpdencies += [pp.functions.modifyGeometry]
  pp.functions.modifyGeometry.dpdencies += [pp.inputs.geometry_2d
                                           ,pp.inputs.amount
                                           ,pp.inputs.x_limit
                                           ,pp.inputs.y_limit
                                           ,pp.inputs.seed]
  
  #We can work directly on the output
  pp.non_cached_capable += ['geometry_2d']
  
  return pp

def modifyGeometry(args):
  #Inputs
  amount = getPropValue(args, 'inputs','point_indexes')
  x_limit = getPropValue(args, 'inputs','x_limit')
  y_limit = getPropValue(args, 'inputs','y_limit')
  seed = getPropValue(args, 'inputs','seed')
  #Outputs
  geom2d = getPropValue(args, 'outputs','geometry_2d')
  #Big deal!!
  random.seed(seed)
  for i in xrange(amount):
    #geom2d.points.append(Point2D(random.random()*x_limit,random.random()*y_limit))
    geom2d.points.append([random.random()*x_limit-x_limit/2,random.random()*y_limit-y_limit/2])

if __name__ == '__main__':
  pp = getProcessorProxy(None)
  debugPrint( pp)
