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
from common.abstract.FrameworkBase import FrameworkBase
from mepinta.pipeline.hi.value_manager.ValueManager import ValueManager

class SimpleTestPipelineGui(FrameworkBase):
  '''Creates a Gui from a given TestPipeline (Simple or Inotify).
    -Creates GUI Panel
    -Evaluates Pipeline's values on GUI events
    -Able to coexist with a InotifyActionManager
  
  This class is used by GUIInotifyTestPipeline, in general  you should directly 
  use GUIInotifyTestPipeline. 
  '''
  def __post_init__(self, test_pline):
    self.test_pline = test_pline
    self.value_mngr = ValueManager(self.context)
    self.__widgetid_value = {}
    self.__widgetid_prop = {}
    self.__update_functions = []

  def __createWidgetId(self, node, prop):
    return "%s_%s"%(node.name.replace(" ","_"), prop.name)

  def __createWidget(self, node, prop):
    from nodebox.gui import Field,Slider,Flag#,Label,Row,Knob,Action
    widget_name = "%s:%s"%(node.name, prop.name)
    bool_alias = ['k3d::bool_t']
    if prop.data_type_alias in bool_alias:
      return (widget_name,Flag(default=bool(self.__getPropValue(prop)), id=self.__createWidgetId(node, prop)))
    text_types = ['c.builtin.charp','cpp.std.string']
    if prop.data_type_name in text_types:
      return (widget_name, Field(value=self.__getPropValue(prop), hint="", id=self.__createWidgetId(node, prop)))
    number_types = ['c.builtin.int','c.builtin.double']
    if prop.data_type_name in number_types:
      return (widget_name, Slider(default=self.__getPropValue(prop), min=0.0, max=50.0, steps=100, id=self.__createWidgetId(node, prop)))

  def __getPropValue(self, prop):
    return self.test_pline.getValue(prop)

  def __createPanel(self):
    from nodebox.gui import Panel,Rows
    panel = Panel("Properties", width=200, height=200, fixed=False, modal=False)
    widget_list =[]

    for node in self.test_pline.getNodesDict().values():
      for prop in node.inputs.get_properties().values():
        widget = self.__createWidget(node, prop)
        if widget != None:
          self.__widgetid_value[self.__createWidgetId(node, prop)] = None
          self.__widgetid_prop[self.__createWidgetId(node, prop)] = prop
          widget_list.append(widget)
    panel.append(Rows(widget_list))
    panel.pack()
    return panel
  
  def __createControls(self):
    self.panel = self.__createPanel()
    self.canvas.append(self.panel)
  
  def __setPropsOnChange(self):
    evaluate = False
    for widget_id, value in self.__widgetid_value.items():
      widget = getattr(self.panel, widget_id)
      if value != widget.value:
        evaluate = True
        self.__widgetid_value[widget_id] = widget.value
        prop = self.__widgetid_prop[widget_id]
        self.test_pline.setValue(prop, widget.value)
    return evaluate
  
  def __updateFunction(self):
    for function in self.__update_functions:
      function()
    self.nodebox_pline.update(self.canvas)
    if self.__setPropsOnChange():
      self.test_pline.evaluateProp()

  def appendUpdateFunction(self, function):
    if function not in self.__update_functions:
      self.__update_functions.append(function)
    
  def removeUpdateFunction(self, function):
    if function in self.__update_functions:
      self.__update_functions.remove(function)

  def __setupNodebox(self, canvas_x, canvas_y):
    from mepinta.testing.plugins_testing.nodebox.NodeBoxSimplePipelineOutput import NodeBoxSimplePipelineOutput
    from mepinta.testing.plugins_testing.nodebox.NodeboxUiRunner import NodeboxUiRunner
    from nodebox.graphics import canvas
    self.canvas = canvas    
    self.__createControls()
    self.nodebox_pline = NodeBoxSimplePipelineOutput(self.test_pline.getPipeline(), canvas_x, canvas_y)
    return NodeboxUiRunner(canvas_x,canvas_y)

  def run(self, canvas_x=700, canvas_y=600):
    ui_runner = self.__setupNodebox(canvas_x, canvas_y)
    ui_runner.run(self.__updateFunction)

  def runWithInotify(self, inotify_mngr, canvas_x=700, canvas_y=600):
    from nodebox.graphics import canvas
    from mepinta.testing.plugins_testing.gui.PygletXlibEventLoop import PygletXlibEventLoop
    ui_runner = self.__setupNodebox(canvas_x, canvas_y)
    draw = ui_runner.getDrawMethod(self.__updateFunction)
    canvas.set_method(draw, name='draw')
    canvas._setup()
    canvas.fps = canvas._fps
    PygletXlibEventLoop(inotify_mngr).run()

if __name__ == "__main__":
  pass