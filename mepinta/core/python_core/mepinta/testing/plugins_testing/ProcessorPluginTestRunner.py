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
from mepinta.plugins_manager.PluginsManager import PluginsManager
from common.inotify.actions.PathAction import PathAction
from common.inotify.mask import IN_CLOSE_WRITE#, IN_ATTRIB, IN_ALL_EVENTS
from mepinta.testing.plugins_testing.base import ForkInotifyUtilsBase
from common.type_checking.isiterable import isiterable
from mepinta.testing.plugins_testing.test_pipeline.GUIInotifyTestPipeline import GUIInotifyTestPipeline
import os
from mepinta.testing.plugins_testing.test_pipeline.InotifySimpleTestPipeline import InotifySimpleTestPipeline
import signal
import sys

class ProcessorPluginTestRunner(ForkInotifyUtilsBase):
  '''Runs a realtime interactive tests for plugin development.
  The main job of this class is to:
    -start a fork and run the provided test in a forked process
    -watch the plugin's manifest for changes, if it changes, kills the child
     process and re-launches a new child with the new manifest.

  This class processes modules with a class inheriting from:
    mepinta.testing.plugins_testing.processor.base.ProcessorPluginTestBase
  And adding an alias 'test' to the implemented class.
  For example:
  class MyProcessorName(ProcessorPluginTestBase):
    def definePipeline(self, test_pipeline):
      ...
    def stressPipeline(self, test_pipeline, time):
      ...
  test = MyProcessorName
  '''
  def __post_init__(self):
    #inotify manager for watching plugin's manifest
    self._inotify_mngr = InotifyActionManager(self.context)
    #plugin manager for getting paths to the manifests
    self._plugins_mngr = PluginsManager(self.context)
    #process id of the forked childs (where the test_pipeline is runned)
    self._child_pid = None

  def __getManifestInotifyFunction(self, test_modules, test_pline):
    #define the function to be run in the fork process
    def manifestInotifyFunction():
      #create and setup pipeline
      test_pline.registerTestModules(test_modules)
      #evaluate the first time
      test_pline.evalOnTest()
      #listen input events (gui, input files, test module, and processor library)
      test_pline.blockListeningEvents([])
    #return the just created function
    return manifestInotifyFunction

  def blockListeningEvents(self, test_modules, test_pline=None, timeout=None, gui=True):
    if not test_pline: #If no pipeline  is provided, create one
      if gui:
        test_pline = GUIInotifyTestPipeline(self.context)
      else:
        test_pline = InotifySimpleTestPipeline(self.context)
    #Create the first fork (that will be killed when a processor manifest changes)
    manifestInotifyFunction = self.__getManifestInotifyFunction(test_modules, test_pline)
    self._child_pid = self._callFunctionOnFork(manifestInotifyFunction, wait_child=False)

    #register provided module/s
    self.registerTestModules(test_modules, test_pline)

    #set signals handlers before blocking
    self._setSignals()
    #Listen for processors' manifests changes
    self._inotify_mngr.blockListeningEvents(timeout)

  def _setSignals(self):
    #define signal handler
    def exitSignalHandler(received_signal, frame):
      self.log.info("Killing child process.")
      self.log.debug("Killing child process %s with signal %s." % (self._child_pid, signal.SIGTERM))
      #if the child is not killed will remain running after father's dead
      os.kill(self._child_pid, signal.SIGTERM)
      #ok, now we can exit
      sys.exit(0)
    #link handler to the interrupt signal
    signal.signal(signal.SIGINT, exitSignalHandler)
    signal.signal(signal.SIGTERM, exitSignalHandler)

  def registerTestModules(self, test_modules, test_pline):
    #is it one module or a list of modules?
    if not isiterable(test_modules):
      test_modules = [test_modules]
    #regiter each provided module
    for test_module in test_modules:
      self._registerTestModule(test_module, test_pline)

  def _registerTestModule(self, test_module, test_pline):
    #Get the plugin test instance
    plugin_test = self._getTestInstance(test_module)
    #Creates processors manifest files watchers
    for processor in plugin_test.getWatchedProcessors():
      #watch it's processor manifest for changes
      self.__watchProcessorManifest(processor, test_module, test_pline)

  def __watchProcessorManifest(self, processor, test_module, test_pline):
    '''Defines the function to be call when the plugin's manifest changes.'''
    #define the function to call when the processor's manifest (.py) changes
    def manifestInotifyForked(event, action, manager):
      '''Kills previous child process and creates a new one that will recreate
        the whole pipeline.
      '''
      if self._child_pid:#if there were a prior proces, then kill it
        self.log.debug("Killing child process %s with signal %s." % (self._child_pid, signal.SIGTERM))
        #if the child is not killed will remain running after father's dead
        #send the TERM signal 15
        os.kill(self._child_pid, signal.SIGTERM)
        #wait for the children death
        child_pid, status = os.waitpid(self._child_pid, 0)
        self.log.debug("Child process %s ended with status %s." % (child_pid, status))
      #Get the function to call when the manifest changed (means need to reload the whole pipeline)
      manifestInotifyFunction = self.__getManifestInotifyFunction(test_module, test_pline)
      self._child_pid = self._callFunctionOnFork(manifestInotifyFunction, wait_child=False)
    #load the processor to get the manifest's module path
    processor_metadata = self._plugins_mngr.load_processor(processor)
    path = self._getModuleFilePath(processor_metadata.module)
    #unload processor to release libraries (very important, if not the file won't be released when deleted)
    self._plugins_mngr.unload_processor_library(processor_metadata)
    #Create the action for the file
    path_action = PathAction(self.context, path=path, mask=IN_CLOSE_WRITE)
    #append function on notification for the file
    path_action.appendFunction(manifestInotifyForked)
    #register the action for future notifications listening
    self._inotify_mngr.registerAction(path_action)

if __name__ == "__main__":
  from default_context import getDefaultContext
  from pipeline_backend.logging.logging import LOG_INFO#, LOG_DEBUG
  #ptr = ProcessorPluginTestRunner(getDefaultContext(LOG_DEBUG))
  ptr = ProcessorPluginTestRunner(getDefaultContext(LOG_INFO))
  print (ptr)

