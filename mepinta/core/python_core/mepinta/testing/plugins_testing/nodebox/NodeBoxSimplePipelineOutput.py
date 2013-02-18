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
# Add the upper directory (where the nodebox module is) to the search path.
#import os, sys; 
#sys.path.insert(0, os.path.join("..",".."))

#from nodebox.graphics import *

#from tests.integrated_tests.exactImage_plugins import test

from nodebox.graphics.physics import Graph, Text
from nodebox.graphics.context import canvas, background, color, translate
from mepinta.pipeline.lo.constants import NULL_UID,FUNCTION_PROPERTY_FLAG,INPUT_PROPERTY_FLAG,\
  INTERNAL_PROPERTY_FLAG, has_flags, CUSTOM_PROPERTY_FLAG, FUNCTUM_PROPERTY_FLAG

#TODO: should be of FrameworkBase type?
class NodeBoxSimplePipelineOutput(object):
  def __init__(self, pline, canvas_x, canvas_y, mc=None):
    self.canvas_x = canvas_x 
    self.canvas_y = canvas_y
    self.pline = pline
    self.mc = mc
    self.graph = self.create_graph()
    self.dragged = None
    self.dtypes_dict = self.create_dtypes_dict(mc)
  def get_node_color(self, p_type):
    input_color =  color(0  ,0.5,0  ,0.5)
    internal_color =  color(0.5  ,0.5,0  ,0.5)
    output_color = color(0.5,0  ,0  ,0.5)
    func_color =   color(0  ,0  ,0.5,0.5)
    functum_color =   color(0  ,0.3  ,0.5,0.5)
    if has_flags(p_type,FUNCTION_PROPERTY_FLAG):
      fill_color = func_color
    elif has_flags(p_type,INPUT_PROPERTY_FLAG):
      fill_color = input_color
    elif has_flags(p_type,INTERNAL_PROPERTY_FLAG):
      fill_color = internal_color
    elif has_flags(p_type,FUNCTUM_PROPERTY_FLAG):
      fill_color = functum_color
    else:
      fill_color = output_color
    if has_flags(p_type, CUSTOM_PROPERTY_FLAG):
      fill_color.alpha = 1.0
    return fill_color
  def create_graph(self):
    gph = Graph()
    #for pline_i, topo in enumerate(self.pline.topologies.values()):
    pline_i=0
    topo = self.pline.get_topology()
    for p_id in topo.properties:
      prop = self.pline.all_properties[p_id]
      if len(self.pline.topologies)>1:
        if self.mc != None:
          #TODO: review why is this necessary, seems some escaping mechanism is needed?
          n_label = "123456789-10.0[]a_-.:*+^/()'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -0.544021110889      x*x               "
        else:
          n_label = '%r %r %s'%(p_id,pline_i+1,prop.name)
        n_id = p_id+pline_i*10000
      else:
        if self.mc != None:
          n_label = "123456789-10.0[]a_-.:*+^/()'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -0.544021110889      x*x               "
        else:
          n_label = '%r %s'%(p_id,prop.name)          
        n_id = p_id
      label = Text(unicode(n_label), width= 85, fill= color(0,0,0,1), fontsize= 9)  
      gph.add_node( id=n_id
                   ,radius=5
                   ,text = label
                   ,fill = self.get_node_color(prop.type))
    #add dependencies directions
    dpdencies_iterator = topo.connections.dpdencies.get_ss_iterator()
    id1,id2 = dpdencies_iterator.next()
    while id1 != NULL_UID:
      gph.add_edge(id1+pline_i*10000, id2+pline_i*10000)
      id1,id2 = dpdencies_iterator.next()
    #add dependents directions
    dpdents_iterator = topo.connections.dpdents.get_ss_iterator()        
    id_1,id_2 = dpdents_iterator.next()
    while id_1 != NULL_UID:
      gph.add_edge(id_1+pline_i*10000, id_2+pline_i*10000)
      id_1,id_2 = dpdents_iterator.next()        
    return gph
  def create_dtypes_dict(self,mc):
    dtypes_dict = {}
    if mc == None:
      return dtypes_dict

    append = True
    for d_id, dtype in mc.context.get_config('context_lo').data_types.iteritems():
      if dtype.name == 'double':
        function = mc.vm.get_doubles
      elif dtype.name == 'charp':
        function = mc.vm.get_charps
      elif dtype.name == 'int':
        function = mc.vm.get_ints
      else:
        append = False
      if append:
        dtypes_dict[d_id] = function
      append = True
    return dtypes_dict
  def recreate_labels(self):
    self.labels_recreated = True
    mc = self.mc
    for p_id, node in self.graph.iteritems():
      prop = mc.pline.all_properties[p_id]
      node.text._label.text = unicode("%r %s"%(p_id,prop.name))
   
  def update(self, canvas, *a, **ad):
    #TODO: add the properties value to the text
    #n.text._label.text
    mc = self.mc
    dtypes_dict = self.dtypes_dict
    if mc != None and mc.updated: #We can set values
      if not hasattr(self, "labels_recreated"):
        self.recreate_labels()
      for p_id, node in self.graph.iteritems():
        prop = mc.pline.all_properties[p_id]
        dtype_id = prop.dtype_id
        if dtype_id in dtypes_dict:
          value = dtypes_dict[dtype_id](mc.pline,[p_id])[0]
          text_r= "%d %s %r"%(p_id,prop.name,value)
          node.text._label.text = unicode(text_r)

    self.graph.draw(weighted=0.5, directed=True)
    self.graph.update(iterations=10)

    # Make it interactive!
    # When the mouse is pressed, remember on which node.
    # Drag this node around when the mouse is moved.
    dx = canvas.mouse.x - self.canvas_x//2 # Undo translate().
    dy = canvas.mouse.y - self.canvas_y//2
    if canvas.mouse.pressed and not self.dragged:
        self.dragged = self.graph.node_at(dx, dy)
    if not canvas.mouse.pressed:
        self.dragged = None
    if self.dragged:
        self.dragged.x = dx
        self.dragged.y = dy
  def run(self):
    canvas.size = self.canvas_x,self.canvas_y
    def draw(canvas):
      canvas.clear()
      background(1)
      translate(self.canvas_x//2,self.canvas_y//2)
      self.update(canvas)
    canvas.run(draw)

if __name__ == '__main__':
  pass
#  def test(argv):
#    from tests.integrated_tests.geom2d_plugins import test
#    pipeline_output = NodeBoxSimplePipelineOutput(test(None).pline,1000,700)
#    pipeline_output.run()  
#  test(None)
