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
import os
import sys
import imp
from mepinta.testing.plugins_testing.processor.base import ProcessorPluginTestBase
from mepinta.abstract.MepintaError import MepintaError
from common.path import splitPath
from importlib import import_module

class ForkInotifyUtilsBase(FrameworkBase): #TODO: use composition
  def _reloadModule(self, module):
    #if it's the main module, do a hack. (reload it as a different module from the filename)
    if module.__name__ == '__main__':
      self.log.debug('Reloading %r. (it\'s the main module)' % module)
      module = imp.load_source('__main__reloaded', module.__file__)
    else: #if it's other module, then simply reload it with imp
      self.log.debug('Reloading %r.' % module)
      imp.reload(module)
    #since the module won't be the same in the case of __main__ we need to redefine it on the caller
    return module

  def _getTestInstance(self, testModule):
    for class_ in testModule.__dict__.values():
      if issubclass(class_, ProcessorPluginTestBase):
        return class_(self.context)
    raise RuntimeError('There is no a test class in module: %s' % testModule)
#    if hasattr(testModule, 'test') and issubclass(testModule.test, ProcessorPluginTestBase):
#      testModule = self._reloadModule(testModule)
#      return testModule.test(self.context)
#    else:
#      raise RuntimeError('There is no a test class in module: %s' % testModule)

  def _getModuleFilePath(self, module):
    '''Get the .py file for a given module.

      For a given module the module.__file__ could point to the .py or .pyc
      We are interested always in the .py changes. '''
    file_path = module.__file__
    if file_path.endswith(".pyc"):
      return file_path[:-1]
    else:
      return file_path
  def _callFunctionOnFork(self, function, wait_child=True, *args, **kwargs):
    '''Calls the provided function on a forked process.

      Depending on wait_child argument if this functions waits for the child process to
      die or returns the child pid. (for later use)
    '''
    self.log.debug("Forking function %r." % function)
    child_pid = os.fork()
    if child_pid == 0:
      try:
        function(*args, **kwargs)
        self.log.debug('Exiting fork process normally.')
      except Exception as exception:
        self.log.lastException(level='error')
        self.log.error('Exiting unnormally with following exception: %s' % exception)
      sys.exit(0)
    else:
      self.log.debug("Child pid %s" % child_pid)
    if wait_child:
      pid, status = os.waitpid(child_pid, 0)
      if status != 0:
        self.log.error("Children exited unnormally with pid:%s status %s" % (pid, status))
      else:
        self.log.debug("Children normal exit status.")
      return None
    else:
      return child_pid

  def _callFunctionOnForkDummy(self, function, wait_child=True, *args, **kwargs):
    '''
    '''
    self.log.debug("Forking function %r." % function)
    function(*args, **kwargs)
    return 0

class ModuleAutoTesterBase(FrameworkBase): #TODO remove and use util
  def _getClassModule(self, class_):
    if class_.__module__ == '__main__':
      import __main__
      return __main__
    else:
      return import_module(class_.__module__)#__import__(class_.__module__, fromlist='dummy')

  def _getPackageAndMinorVersion(self, plugin_manifest):
    package_str, manifest_file = plugin_manifest.getPackageStrAndManifestFile()
    plugin_package = import_module(package_str)#__import__(package_str, fromlist="dummy")
    minor_version = self.__getMinorVersion(manifest_file)
    return plugin_package, minor_version

  def __getMinorVersion(self, manifest_file):
    #if len(manifest_file.split('__')) != 2:
    if len(manifest_file.split(self.context.minor_version_separator)) != 2:
      self.log.error('The Plugin Manifest file %r should obey the format: PluginName__$version$.py (MorphPoints_001.py for example)' % manifest_file)
    else:
      minor_version_str = manifest_file.split('__')[1]
      minor_version_str = minor_version_str.split('.')[0]
      try:
        minor_version = int(minor_version_str)
        self.log.debug('Plugin minor version is %s' % minor_version)
      except ValueError as value_error:
        raise MepintaError('Couldn\'t convert the minor version to number from file %r. (exception %s).' % (manifest_file, value_error))
      return minor_version

if __name__ == "__main__":
  pass
