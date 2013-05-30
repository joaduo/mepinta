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
from common.inotify.InotifyActionManager import InotifyActionManager
from mepinta.plugins_manifest import InotifyPropertyBase
from mepinta.pipeline.hi.value_manager.ValueManager import ValueManager
from common.inotify.actions.PathAction import PathAction
from common.inotify.mask import IN_DELETE_SELF, IN_CLOSE_WRITE, IN_ATTRIB#, IN_MOVED_TO, IN_CLOSE, IN_CLOSE_NOWRITE, IN_ALL_EVENTS
from common.path import pathExists, realPath
from mepinta.pipeline.hi.plugin_loader.PluginLoader import PluginLoader
from mepinta.testing.plugins_testing.base import ForkInotifyUtilsBase
from mepinta.abstract.MepintaError import MepintaError
from common.type_checking.isiterable import isiterable
from mepinta.testing.plugins_testing.test_pipeline.SimpleTestPipeline import SimpleTestPipeline
import time

#TODO: Split into implementation classes
#(A main wrapper that uses watcher creator)

class InotifySimpleTestPipeline(ForkInotifyUtilsBase):
  '''Wraps and Mimics a SimpleTestPipeline adding capabilities of watching:
    -Input Files properties.
    -Processor library files (.so.implementation).
    -Test modules.

  Providing a test_module to the 'blockListeningEvents'(*) this class will setup
  the InotifyActionManager to watch those files, libraries and modules provided
  by the test module configuration.
  (*or previously registering the test module with 'registerTestModules' method)

  This is the default test pipeline used by the 'ProcessorPluginTestRunner' class
  with gui disabled.
  (When the plugins' developers doesn't want the interactive GUI with the
  'ProcessorPluginTestRunner', they can provide this pipeline to the
  'ProcessorPluginTestRunner.blockListeningEvents' method as a first argument.)
  '''
  @property
  def default_evaluated(self):
    return self.__default_evaluated

  @property
  def default_marked(self):
    return self.__default_marked

  def __post_init__(self):
    self._test_pline = SimpleTestPipeline(self.context)
    self._inotify_mngr = InotifyActionManager(self.context)
    self._inotify_mngr.appendPostEventsFunction(self.evalOnTest)
    self._plugin_loader = PluginLoader(self.context)
    self._value_mngr = ValueManager(self.context)
    self._prop_action = {}
    self._watched_test_modules = []
    self._watched_processors = []
    self.__default_evaluated = []
    self.__default_marked = []
    #self.__mark_default_prop = False #TODO: delete
    #Callable called each time a file/input happens
    self._eval_on_test = self.__evalOnTestDefault

  def getPipeline(self):
    return self._test_pline.getPipeline()

  def append(self, processor, connect=True):
    return self._test_pline.append(processor, connect)

  def getValue(self, prop):
    return self._test_pline.getValue(prop)

  def setLastNode(self, node):
    self._test_pline.setLastNode(node)

  def getLastNode(self):
    return self._test_pline.getLastNode()

  def getNodesDict(self):
    return self._test_pline.getNodesDict()

  def connect(self, dent_prop, dency_prop):
    self._test_pline.connect(dent_prop, dency_prop)

  def syncNode(self, node):
    self._test_pline.syncNode(node)

  def getMetadata(self, processor):
    return self._test_pline.getMetadata(processor)

  def blockListeningEvents(self, test_modules=[], timeout=None):
    self.registerTestModules(test_modules)
    if not (len(self._watched_test_modules) or len(self._watched_processors)):
      raise MepintaError('Should should at least watch one test module or processor.')
    self._inotify_mngr.blockListeningEvents(timeout)

  def registerTestModules(self, test_modules):
    if not isiterable(test_modules):
      test_modules = [test_modules]
    for test_module in test_modules:
      self._registerTestModule(test_module)

  def _registerTestModule(self, test_module):
    plugin_test = self._getTestInstance(test_module)
    #Creates pipeline and creates input file watches
    plugin_test.definePipeline(self)
    #Only c and cpp plugins .so.implentation libraries will be watched
    if self.context.backend_name == 'c_and_cpp':
      #TODO: later this should be improved (watching python implementations)
      for processor in plugin_test.getWatchedProcessors():
        self.watchProcessorLibrary(processor)
    self.__watchTestModule(test_module)

  def evaluateProp(self, prop=None):
    if prop:
      return self._test_pline.evaluateProp(prop)
    else:
      if not len(self.default_evaluated):
        raise RuntimeError('You should be set a default property prior calling this method.')
      for prop in self.default_evaluated:
        return self._test_pline.evaluateProp(prop)

  def setValue(self, prop, value):
    self._test_pline.setValue(prop, value)
    if isinstance(prop, InotifyPropertyBase):
      self.__createPropAction(prop)

  def __createPropAction(self, prop):
    '''Creates a PathAction action for InotifyActionManager
    If the path is the same of the previous action, then nothing is done.
    If not, the previous action is removed and a new action is set.
    '''
    path = prop.getPath(self.getPipeline(), self.context)
    if prop in self._prop_action:
      path_action = self._prop_action[prop]
      if path_action.getRealPath() == path:
        #Its the same path, then nothing changed
        return
      else:
        #remove the action, we are adding a new one
        self._inotify_mngr.removeAction(path_action)
    #create the function to be called when the input file changes
    def inputFileInotifyFunction(event, action, manager):
      self.log.debug("inputFileInotifyFunction event %s. For path: %r." % (event, path))
      if event.mask & IN_CLOSE_WRITE:
        self._value_mngr.markChanged(self.getPipeline(), prop)
        self._inotify_mngr.skip_post_functions = False
    path_action = PathAction(self.context, path=path, mask=IN_CLOSE_WRITE)
    self._prop_action[prop] = path_action
    path_action.appendFunction(inputFileInotifyFunction)
    self._inotify_mngr.registerAction(path_action)

  def evalOnTest(self, mark_default_prop=False, manager=None, *args):
    self._eval_on_test(mark_default_prop, manager)

  def __evalOnTestDefault(self, mark_default_prop=False, manager=None, *args):
    def evaluateProp():
      if mark_default_prop:
        for prop in self.default_marked:
          self._test_pline.markChanged(prop)
      self.evaluateProp()
    self._callFunctionOnFork(evaluateProp)

  def watchProcessorLibrary(self, processor):
    if processor in self._watched_processors:
      self.log.warning('Processor module already watched: %r' % processor)
      return
    self._watched_processors.append(processor)
    processor_metadata = self.getMetadata(processor)
    def processorLoadFunction(manager):
      #self.log.debug("processorLoadFunction event %s."%event)
      #Directly calling the function or not needing it
      if not self._plugin_loader.processorIsLoaded(processor_metadata):
        if pathExists(realPath(processor_metadata.library_path)):
          self.log.debug('Reloading %s.' % processor_metadata)
          self._plugin_loader.load_processor_library(processor_metadata)
    def processorUnloadFunction(event, action, manager):
      self.log.debug("processorUnloadFunction event %s." % event)
      manager.skip_post_functions = True
      self.log.debug('Unloading %s.' % processor_metadata)
      self._plugin_loader.unload_processor_library(processor_metadata)
    path_action = PathAction(self.context, path=processor_metadata.library_path)
    #path_action.appendFunction(processorLoadFunction, mask=IN_CLOSE|IN_MOVED_TO|IN_ATTRIB)#TODO: review this. has too many flags just in case.
    path_action.appendFunction(processorUnloadFunction, mask=IN_DELETE_SELF | IN_ATTRIB)
    self._inotify_mngr.removePostEventsFunction(self.evalOnTest)
    self._inotify_mngr.appendPostEventsFunction(processorLoadFunction)
    self._inotify_mngr.appendPostEventsFunction(self.evalOnTest)
    self._inotify_mngr.registerAction(path_action)

  def __watchTestModule(self, test_module):
    if test_module in self._watched_test_modules:
      self.log.warning('Test module already watched: %r' % test_module)
      return
    self._watched_test_modules.append(test_module)
    def testModuleInotifyFunction():
      module_reloaded = self._reloadModule(test_module)
      plugin_test = module_reloaded.test(self.context)
      #timing values
      start, end, step, sleep = self.__getTimeParameters(plugin_test.getTimeParameters())
      if end - start >= 0.: #ascending time
        frames = range(int((end - start) / step) + 1)
      else:#descending time
        frames = reversed(range(int((start - end) / step) + 1))
      plugin_test.stressStart(self, start)
      for frame in frames:
        plugin_test.stressPipeline(self, frame * step)
        self.evaluateProp()
        time.sleep(sleep) #TODO: improve waiting taking in count the time of evaluation and print fps too
      plugin_test.stressStart(self, end)
    path = self._getModuleFilePath(test_module)
    path_action = PathAction(self.context, path=path, mask=IN_CLOSE_WRITE)
    self._inotify_mngr.registerAction(path_action)
    self.replaceEvalOnTest(testModuleInotifyFunction)

  def __getTimeParameters(self, time_parameters):
    #TODO: later support custom classes FPSxtime, so on...
    start, end, step, sleep = 0., 100., 1., 0.
    if time_parameters:
      if isinstance(time_parameters, tuple): #Ok, tuple, follow the law!
        start, end, step, sleep = time_parameters
      elif isinstance(time_parameters, dict): #We get a dictionary. crappy code below!
        time_parameters_dict = dict(start=0., end=100., step=1., sleep=0.)
        time_parameters_dict.update(time_parameters)
        start = time_parameters_dict['start']
        end = time_parameters_dict['end']
        step = time_parameters_dict['step']
        sleep = time_parameters_dict['sleep']
      else:
        self.log.warning('Unsupported time parameters %r. Using defaults' % time_parameters)
    return start, end, step, sleep

  def replaceEvalOnTest(self, test_function):
    def evalOnTest(mark_default_prop=False, manager=None, *args):
      def evaluateProp():
        if mark_default_prop:
          for prop in self.default_marked:
            self._test_pline.markChanged(prop)
        test_function()
      self._callFunctionOnFork(evaluateProp)
    self._eval_on_test = evalOnTest

if __name__ == "__main__":
  from default_context import getDefaultContext
  from pipeline_backend.logging.logging import LOG_DEBUG
  context = getDefaultContext(LOG_DEBUG)
  istp = InotifySimpleTestPipeline(context)
  context.log(istp)
