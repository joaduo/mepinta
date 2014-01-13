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

from mepinta.pipeline.lo.context_lo.ContextLo import ContextLo, \
  shedskin_ContextLo
from mepinta.pipeline.lo.topology_manager.TopologyManager import TopologyManager, \
  shedskin_TopologyManager
from mepinta.pipeline.lo.pipeline_data.data_model import Pipeline, \
  shedskin_pipeline_data_model, Topology, Property
from mepinta.pipeline.lo.plugin_loader.PluginLoader import PluginLoader, \
  shedskin_PluginLoader
from mepinta.pipeline.lo.FunctionCaller import FunctionCaller
from mepinta.pipeline.lo.value_manager.PropertyValueManager import PropertyValueManager, \
  shedskin_PropertyValueManager
from mepinta.pipeline.lo.value_manager.ValueManager import ValueManager, \
  shedskin_ValueManager
from mepinta.pipeline.lo.property_manager.PropertyManager import PropertyManager, \
  shedskin_PropertyManager
from mepinta.pipeline.lo.LogOutput import LogOutput, shedskin_LogOutput
from pipeline_backend.logging.logging import shedskin_logging
from pipeline_backend.args_management.args_management import shedskin_args_management
from pipeline_backend.void_pointer_casting.void_pointer_casting import shedskin_void_pointer_casting
from mepinta.pipeline.lo.constants import INPUT_PROPERTY_FLAG
from mepinta.pipeline.lo.generic_data.DirectedGraph import shedskin_DirectedGraph
from mepinta.pipeline.lo.generic_data.BiDirectedGraph import shedskin_BiDirectedGraph
from mepinta.pipeline.lo.pipeline_evaluator.base import shedskin_PipelineEvaluatorBase
#from mepinta.pipeline.lo.pipeline_evaluator.PipelineEvaluator import PipelineEvaluator,\
#  shedskin_PipelineEvaluator
from mepinta.pipeline.lo.pipeline_evaluator.PipelineEvaluatorFunctum import PipelineEvaluatorFunctum, \
  shedskin_PipelineEvaluatorFunctum
from mepinta.pipeline.lo.pipeline_evaluator.propagation.SimplePropagationManager import SimplePropagationManager, \
  shedskin_SimplePropagationManager
from mepinta.pipeline.lo.pipeline_data.hidden_data_types import shedskin_hidden_data_types
from mepinta.pipeline.lo.pipeline_evaluator.ProcessorArgsManager import shedskin_ProcessorArgsManager
from mepinta.pipeline.lo.pipeline_data.TopologyConnections import shedskin_TopologyConnections
#from pipeline_backend.reentrant.evaluateProp import shedskin_backend_reentrant_evaluateProp
#from pipeline_backend.reentrant.isDataTypeAlias import shedskin_backend_reentrant_isDataTypeAlias
from mepinta.pipeline.lo.reentrant.data_model import shedskin_reentrant_data_model
from mepinta.pipeline.lo.reentrant.reentrant import shedskin_reentrant
from mepinta.pipeline.lo.exceptions.MepintaLoError import shedskin_MepintaLoError
from mepinta.pipeline.lo.value_manager.DebugPropertyValueManager import shedskin_DebugPropertyValueManager
from pipeline_backend.load_unload_library.load_unload_library import loadLibrary, unloadLibrary
from pipeline_backend.logging.logging import logError, logInfo
#from mepinta.pipeline.lo.generic_data.ConditionalBDGraph import shedskin_ConditionalBDGraph

class FactoryLo(object):
  def __init__(self):
    self._loaded_libraries = {}

  def loadLibrary(self, path, symbol):
    loaded_libraries = self._loaded_libraries
    #Common code in load_library_stand_alone (not easy to share because of shedksin)
    if path in loaded_libraries:
      symbol = loaded_libraries[path][1]
      logInfo("Library at %r already loaded with symbol %r" % (path, symbol))
      return True
    handle = loadLibrary(path, symbol)
    if handle == None:
      logError("Couldn't load the library at %r with symbol %r" % (path, symbol))
      return False
    loaded_libraries[path] = (handle, symbol)
    logInfo("Successfully loaded the library at %r with symbol %r" % (path, symbol))
    return True

  def unloadLibrary(self, path):
    loaded_libraries = self._loaded_libraries
    #Common code in load_library_stand_alone (not easy to share because of shedksin)
    if path not in loaded_libraries:
      logError("Library at %r was never loaded" % (path))
      return -1
    handle, _ = loaded_libraries[path]
    return unloadLibrary(handle)

  def get_TopologyManager(self, context_lo):
    return TopologyManager(context_lo)
  def get_PropertyManager(self, context_lo):
    return PropertyManager(context_lo)
  def get_ContextLo(self):
    return ContextLo()
  def get_Pipeline(self):
    return Pipeline()
#  def get_PropertyValuePointer(self):
#    return PropertyValuePointer()
  def get_PluginLoader(self, context_lo):
    return PluginLoader(context_lo)
#  def get_PipelineEvaluator(self, context_lo):
#    return PipelineEvaluator(context_lo)
  def get_PipelineEvaluatorFunctum(self, context_lo):
    return PipelineEvaluatorFunctum(context_lo)
  def get_SimplePropagationManager(self, pline_evaluator):
    return SimplePropagationManager(pline_evaluator)
#  def get_OneChangeFilterPropagationManager(self, pline_evaluator):
#    return OneChangeFilterPropagationManager(pline_evaluator)
#  def get_ManyChangesFilterPropagationManager(self, pline_evaluator):
#    return ManyChangesFilterPropagationManager(pline_evaluator)
  def get_FunctionCaller(self):#TODO: review where this is used
    return FunctionCaller()
  def get_PropertyValueManager(self, context_lo):
    return PropertyValueManager(context_lo)
  def get_ValueManager(self, context_lo):
    return ValueManager(context_lo)
  def get_LogOutput(self):
    return LogOutput()


def shedskin_facade(pline_evaluator_base):
  flo = FactoryLo()
  context_lo = flo.get_ContextLo()
  flo.get_FunctionCaller()
  flo.get_LogOutput()
  flo.get_Pipeline()
  #flo.get_PropertyValuePointer()
#  flo.get_PipelineEvaluator(context_lo)
  flo.get_PipelineEvaluatorFunctum(context_lo)
  flo.get_SimplePropagationManager(pline_evaluator_base)
#  flo.get_OneChangeFilterPropagationManager(pline_evaluator_base)
#  flo.get_ManyChangesFilterPropagationManager(pline_evaluator_base)
  flo.get_PluginLoader(context_lo)
  flo.get_PropertyManager(context_lo)
  flo.get_PropertyValueManager(context_lo)
  flo.get_TopologyManager(context_lo)
  flo.get_ValueManager(context_lo)
  flo.loadLibrary('/path/to.so', 'global')
#  flo.unloadLibrary('/path/to.so')

def shedskin_generation():
  shedskin_DirectedGraph()
  shedskin_BiDirectedGraph()
  #shedskin_ConditionalBDGraph()
  shedskin_TopologyConnections()

  shedskin_logging()
  shedskin_void_pointer_casting()
  shedskin_args_management()
  shedskin_LogOutput()
  prop = Property(INPUT_PROPERTY_FLAG, 'name', dtype_id=0)
  func_prop_value = shedskin_hidden_data_types(prop)
  pline, prop_id = shedskin_pipeline_data_model()
  context_lo = shedskin_ContextLo()
  shedskin_PropertyManager(context_lo, pline, prop_id)

  pline, prop_id = shedskin_pipeline_data_model()
  topo = Topology()
  shedskin_TopologyManager(context_lo, topo)
  shedskin_PluginLoader(context_lo)
  shedskin_ValueManager(context_lo, pline, prop_id)
  shedskin_PropertyValueManager(context_lo, prop)
  shedskin_DebugPropertyValueManager(context_lo, prop)
#  shedskin_PipelineEvaluator(context_lo, pline, prop)
  args_mngr = shedskin_ProcessorArgsManager(context_lo, func_prop_value, prop)
  shedskin_PipelineEvaluatorFunctum(context_lo, pline, prop, args_mngr)
  pline_evaluator = shedskin_PipelineEvaluatorBase(context_lo, pline, prop)
  shedskin_SimplePropagationManager(pline, pline_evaluator)
  shedskin_facade(pline_evaluator)

  processor_context = shedskin_reentrant_data_model(context_lo, pline, pline_evaluator)
  shedskin_reentrant(processor_context)
#  shedskin_backend_reentrant_evaluateProp(processor_context)
#  shedskin_backend_reentrant_isDataTypeAlias(processor_context)
  shedskin_MepintaLoError()


if __name__ == '__main__':
  log = LogOutput()
  log.setLevel(30)
  log.info('Testing pipeline_lo_facade...')
  log.setLevel(0)
  shedskin_generation()
  log.setLevel(30)
  log.info('Done')

