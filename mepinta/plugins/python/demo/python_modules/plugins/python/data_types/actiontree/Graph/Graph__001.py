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
from mepinta.pipelineview.graph.data_model import Graph

class DataTypeManifestBase(object):
  pass

class manifest(DataTypeManifestBase):
  def define(self):
    self.force_non_cached = True
    #self.addLibraries('bla.so')

data_type_description = {
# 'plugin_url':'http://mepinta.joaquinduo.com.ar/plugins/',
# 'future_plugin_url':'http://mepinta.joaquinduo.com.ar/plugins/',
# 'additional_urls':{},
# 'authors':'Joaquín Duo',
# 'description':'''Simple python float data type. In fact there is no real API for this, since it handles consistency easily''',
# 'changes':'First writing',
# 'api':'python', #What kind of api is available for accessing this data
# 'python_module':None,
}

def new():
  return Graph()

def copy(u_graph):
  return u_graph

def delete(u_graph):
  pass

def copy_to(to_u_graph, from_u_graph):
  to_u_graph.setGraph(from_u_graph.graph)

