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
from nodebox.graphics.context import canvas,background,translate

def on_mouse_enter(self,mouse):
  if self.fps == "pause":
    if hasattr(self,"prior_fps"):
      self.fps = self.prior_fps
    else:
      self.fps = None 
def on_mouse_leave(self,mouse):
  self.prior_fps = self.fps
  self.fps = "pause"
def on_mouse_motion(self, mouse):
  self.moving = True
  if self.fps == "pause": 
    self.fps = 10
def on_mouse_press(self, mouse):
  self.moving = True
  if self.fps == "pause": 
    self.fps = 10   

canvas.moving = False

#canvas.on_mouse_motion = on_mouse_motion
canvas.on_mouse_press = on_mouse_press   
canvas.on_mouse_enter = on_mouse_enter
canvas.on_mouse_leave = on_mouse_leave

class NodeboxBase(object):
  pass

class NodeboxContext(NodeboxBase):
  def __init__(self, canvas):
    self.canvas = canvas

wrapped_method = None
def draw(canvas):
  wrapped_method(canvas)

class NodeboxUiRunner(NodeboxBase):
  #initialize nodebox
  #call the processor for update
  def __init__(self, canvas_x, canvas_y):
    self.size = canvas_x,canvas_y
    self.canvas = canvas
    self.nodebox_context = NodeboxContext(self.canvas)
    self.setup_context()
    self.ui_function = None
    self.inputs = None
    self.outputs = None
    self.inputs_func =None

  def setup_context(self):
    self.canvas.size = self.size

  def run(self, inputs_func):
    canvas.run(self.getDrawMethod(inputs_func))

  def getDrawMethod(self, inputs_func):
    self.inputs_func = inputs_func
    global wrapped_method
    wrapped_method = self.draw
    return draw
  
  def draw(self,canvas):
    #canvas.fps = 4
    canvas.clear()
    background(1)
    translate(self.size[0]/2., self.size[1]/2.)
    nbcntx = NodeboxContext(canvas)
    if self.inputs_func:
      self.inputs =  self.inputs_func()
    if self.ui_function:
      self.ui_function(nbcntx, self.inputs, self.outputs)
    

if __name__ == '__main__':
  from nodebox.graphics import rect
  def func(context,inputs,outputs):
    canvas = context.canvas
    rect(x=-100, y=-100, width=300, height=max(100, canvas.mouse.y))

  nbuift = NodeboxUiRunner(400,400)
  nbuift.test_loop(func, None, None)

  
