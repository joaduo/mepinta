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
from mepinta.pipelineview.graph.GraphManager import GraphManager
from mepinta.plugins_manager.PluginsManager import PluginsManager
from mepinta.pipeline.hi.pipeline_evaluator.PipelineEvaluatorFunctum import PipelineEvaluatorFunctum
from mepinta.pipeline.hi.value_manager.AbstractValueManager import AbstractValueManager
from mepinta.pipelineview.graph.data_model import Graph
from mepinta.pipeline.hi.pipeline_data.data_model import Pipeline

class SimpleTestPipeline(FrameworkBase):
  '''This class wraps the mepinta.pipeline.hi.pipeline_data.data_model.Pipeline
  class to make it more suitable to create simple tests.

  Simplifies appending processor and autoconnecting them.
  This way is easy to create a lineal pipeline for a test. It will always auto-
  connect to the latest created node. (if possible)
  You may set the last node with the 'setLastNode' method.
  Also

  You may use 'simpleVisualization' to get an idea of the underlying pipeline.

  For further testing, setup a processor plugin's test and run it with the
  ProcessorPluginTestRunner class. (support inotify and GUI together)
  '''
  def __post_init__(self):
    self._graph_manager = GraphManager(context=self.context)
    self._plugins_manager = PluginsManager(context=self.context)
    self._graph = Graph(Pipeline(context=self.context))
    self._nodes = []
    self._last_node = None
    self._processors_metadata = {}
    self._pline_changed = False
    self._setConfig()
    self.value_manager = AbstractValueManager(context=self.context)
    self.pline_evaluator = PipelineEvaluatorFunctum(context=self.context)

  def getPipeline(self):
    return self._graph.pline

  def getGraph(self):
    return self._graph

  def markChanged(self, prop):
    self.value_manager.markChanged(self._graph.pline, prop)

  def getMetadata(self, processor):
    return self._processors_metadata[processor]

  def _setConfig(self):
    pass

  def append(self, processor, connect=True):
    if processor not in self._processors_metadata:
      self._processors_metadata[processor] = self._plugins_manager.loadProcessor(processor, reload_=True)
    processor = self._processors_metadata[processor]
    node = self._graph_manager.createNode(self._graph, processor)
    if connect:
      self._connectWithLastNode(node)
    self._pline_changed = True
    self._nodes.append(node)
    self._last_node = node
    return node

  def _connectWithLastNode(self, dent_node):
    if self._last_node != None:
      self._graph_manager.autoConnect(self._graph, dent_node, self._last_node)

  def syncNode(self, node):
    self._graph_manager.syncNode(self._graph, node)

  def setLastNode(self, node):
    self._last_node = node

  def getLastNode(self):
    return self._last_node

  def setValue(self, prop, value):
    self.value_manager.setValue(self._graph.pline, prop, value)

  def connect(self, dent_prop, dency_prop):
    self._graph_manager.connect(self._graph, dent_prop, dency_prop)

  def getValue(self, prop):
    return self.value_manager.getValue(self._graph.pline, prop)

  def setPropsDefaultValues(self, nodes=None):
    raise RuntimeError('Implement!')

  def getUIModifiableProps(self, nodes=None):
    if nodes == None:
      nodes = self._nodes
    interative_types = ['int', 'double', 'charp']
    ui_nodes_props = []
    for node in nodes:
      ui_props = []
      ui_nodes_props.append((node, ui_props))
      properties = node.inputs.getProperties()
      for name in node.inputs.declarationOrder:
        prop = properties[name]
        if prop.getDataTypeShortName() in interative_types:
          ui_props.append(prop)
    return ui_nodes_props

  def prepareForAnimation(self):
    '''
    When animating we need to use the changed set specifically from the animation
    changes, so prior secondary changes should be ignored. (thats why we 'grow'
    the pipeline to get a new topology)
    '''
    if self._pline_changed:
      self._graph.pline.grow()
      self._pline_changed = False

  def evaluateProp(self, prop):
    return self.pline_evaluator.evaluateProp(self._graph.pline, prop)

  def simpleVisualization(self, x_width=600, y_height=700): #TODO: remove?
    from mepinta.testing.plugins_testing.nodebox.NodeBoxSimplePipelineOutput import NodeBoxSimplePipelineOutput
    NodeBoxSimplePipelineOutput(self._graph.pline, x_width, y_height).run()

  def getNodesDict(self):
    nodes_dict = {}
    for node in self._nodes:
      nodes_dict[node.name] = node
    return nodes_dict

def testModule():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()
  itp = SimpleTestPipeline(context)
  context.log(itp)

if __name__ == "__main__":
  testModule()

