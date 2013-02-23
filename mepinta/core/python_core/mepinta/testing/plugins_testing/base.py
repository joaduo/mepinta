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

class ForkInotifyUtilsBase(FrameworkBase):
  def _reloadModule(self, module):
    #if it's the main module, do a hack. (reload it as a different module from the filename)
    if module.__name__ == '__main__':
      self.log.debug('Reloading %r. (it\'s the main module)'%module)
      module = imp.load_source('__main__reloaded', module.__file__)
    else: #if it's other module, then simply reload it with imp
      self.log.debug('Reloading %r.'%module)
      imp.reload(module)
    #since the module won't be the same in the case of __main__ we need to redefine it on the caller
    return module

  def _getTestInstance(self, test_module):
    if hasattr(test_module, 'test') and issubclass(test_module.test, ProcessorPluginTestBase):
      test_module = self._reloadModule(test_module)
      return test_module.test(self.context)
    else:
      raise RuntimeError('There is no a test class in module: %s'%test_module)
  
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
    self.log.debug("Forking function %r."%function)
    child_pid = os.fork()
    if child_pid == 0:
      try:
        function(*args, **kwargs)
        self.log.debug('Exiting fork process normally.')
      except Exception as exception:
        self.log.last_exception(level='error')
        self.log.error('Exiting unnormally with following exception: %s'%exception)
      sys.exit(0)
    else:
      self.log.debug("Child pid %s"%child_pid)
    if wait_child:
      pid, status = os.waitpid(child_pid, 0)
      if status != 0:
        self.log.error("Children exited unnormally with pid:%s status %s"%(pid,status))
      else:
        self.log.debug("Children normal exit status.")
      return None
    else:
      return child_pid

  def _callFunctionOnForkDummy(self, function, wait_child=True, *args, **kwargs):
    '''
    '''
    self.log.debug("Forking function %r."%function)
    function(*args, **kwargs)
    return 0

class ModuleAutoTesterBase(FrameworkBase):
  def _getClassModule(self, class_):
    if class_.__module__ == '__main__':
      import __main__
      return __main__
    else:
      raise NotImplementedError()

  def _getPackageAndMinorVersion(self, plugin_manifest):
    if plugin_manifest.__class__.__module__ == '__main__':
      import __main__
      import os
      dir_list = __main__.__file__.split(os.sep)
      start_index = dir_list.index('plugins')
      package_str = '.'.join(dir_list[start_index:-1])
      manifest_file = dir_list[-1]
    else:
      package_str = '.'.join(plugin_manifest.__class__.__module__.split('.')[:-1])
      manifest_file = plugin_manifest.__class__.__module__.split('.')[-1]
    plugin_package = __import__( package_str, fromlist="dummy")
    minor_version = self.__getMinorVersion(manifest_file)
    return plugin_package, minor_version

  def __getMinorVersion(self, manifest_file):
    if len(manifest_file.split('__')) != 2:
      self.log.error('The Plugin Manifest file %r should obey the format: PluginName__$version$.py (MorphPoints_001.py for example)'%manifest_file)
    else:
      minor_version_str = manifest_file.split('__')[1]
      minor_version_str = minor_version_str.split('.')[0]
      try:
        minor_version = int(minor_version_str)
        self.log.debug('Plugin minor versino is %s'%minor_version)
      except ValueError as value_error:
        raise MepintaError('Couldn\'t convert the minor version to number from file %r. (exception %s).'%(manifest_file,value_error))
      return minor_version

if __name__ == "__main__":
  pass