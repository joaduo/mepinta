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
import os
from common.path import joinPath, splitPath

class PluginStorageConfig(object):
  '''
    Stores a plugin's path and config.
    This data is used to create or import a plugin.
    Plugin wizards should create and populate an instance of this class first 
      and then use the other controller classes for creating or importing.
  '''
  def __init__(self, name, lang_group, type_, package, module_name, minor_version, **config_dict ):
    self.name = name
    self.module_name_prefix = module_name
    self._setConfig(config_dict)
    
    self.minor_version = minor_version
    self.package = package
    self.type_ = type_
    self.lang_group = lang_group
    self.plugin_group = type_

  def __getTypePackage(self):
    if self.type_.startswith('processor'):
      return 'processors'
    else:
      return 'data_types'
  def _setConfig(self, config_dict):
    ''' 
      Iterate the options dict provided.
      If the values are not set, use the default dict.
      Values are stored as the object's attributes.  
    '''
    #TODO: use self.__dict__.update?
    defaults = {  "projects_root" : '/home/jduo/001-Mepinta/tmp',
                  "plugins_root" : "/home/jduo/001-Mepinta/tmp", 
                  "data_types_include_root" : "/home/jduo/001-Mepinta/tmp",
                  "build_names" : ["Debug","Release","TypeSafe"], 
                  "project_name" : None ,
                  "minor_version_format":'%04d',
                  "minor_version_separator":'__'}
    #set the options
    for name, value in config_dict.items():
      setattr(self, name, value)
    #Set the defaults now
    for name, value in defaults.items():
      if name not in config_dict:
        setattr(self, name, value)
  def getModuleName(self):
    '''
      Get the name of the python module for the plugin.
      This module will store the plugin's manifest.
    '''
    name = self.module_name_prefix
    version = self.minor_version
    return self.minor_version_separator.join([name,version])
  def getPath(self, name, split=False):
    ''' 
      Builds the: package, module, code or eclipse path for the plugin.
      If split=True, then it returns the path split in a list. 
      (split by to os.sep)
    '''
    if name == "package":
      path = self.__toOSPath("%s.%s.%s.%s"%(self.lang_group,self.__getTypePackage(),self.package,self.module_name_prefix))
    elif name == "module":
      path = self.getPath("package", split=True)
      path.append(self.getModuleName())
    elif name == "code":
      path = self.getPath("package", split=True)
      path.append("%s_code"%self.getModuleName())
    elif name == "project":
      path = splitPath(self.projects_root) + [self.project_name]
    elif name == "data_types_include":
      path = splitPath(self.data_types_include_root) + self.package.split('.') + [self.name]
    else:
      raise RuntimeError("Unkown path type %r"%name)
    if split:
      return path
    else:
      return joinPath(path)
  def __toOSPath(self, packmod_path):
    ''' Gets the full path for the plugins path. (a list split by os.sep) '''
    split_path = self.plugins_root.split(os.sep) + packmod_path.split(".")
    return split_path
  def implementationLibs(self, split=False):
    '''
      Check for the existence of compiled libs for a c_and_cpp eclipse project.
      Returns a dict of existing paths. (for Debug, Release, etc)
    '''
    build_libs = {}
    for build in self.build_names:
      path = self.getPath("project", split=True)
      path.append(build)
      path.append('lib%s.so'%self.project_name)
      if os.access(os.sep.join(path), os.R_OK):
        if not split:
          path = os.sep.join(path)
        build_libs[build] = path
    return build_libs
  
  #Setters and getter for eclipse name and minor version
  def get_minor_version(self):
    return self.__minor_version
  def set_minor_version(self, value):
    if isinstance(value, int):
      value = self.minor_version_format%value
      self.__minor_version = value
    elif isinstance(value, str):
      self.__minor_version = value
    else:
      #TODO: automatically get the minor version
      raise RuntimeError("You should provide a minor version int or str value.")
  def get_eclipse_name(self):
    if self.__eclipse_name != None:
      return self.__eclipse_name
    else:
      return self.module_name_prefix
  def set_eclipse_name(self, value):
    self.__eclipse_name = value  
  project_name = property(get_eclipse_name, set_eclipse_name, None, None)
  minor_version = property(get_minor_version, set_minor_version, None, None)

if __name__ == "__main__":
  psc = PluginStorageConfig('PolyTorus', 'c_and_cpp', 'processor', 'k3dv1.Mesh.generator', 'PolyTorus', 1, minor_version_separator='##')
  debugPrint(psc.project_name)
  debugPrint(psc.minor_version)
  #debugPrint(psc.getPath('eclipse'))
  debugPrint(psc.getPath('project'))
  debugPrint(psc.getPath('package'))
  debugPrint(psc.getPath('module'))
  debugPrint(psc.getPath('code'))
  debugPrint(psc.module_name_prefix)
  debugPrint(psc.getModuleName())
  debugPrint(psc.implementationLibs())
  debugPrint(psc.implementationLibs(split=True))
  
