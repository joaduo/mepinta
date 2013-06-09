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
from common.abstract.FrameworkObject import FrameworkObject
from mepinta.abstract.MepintaError import MepintaError
from mepinta.pipeline.lo.pipeline_data.data_model import Pipeline
from common.abstract.decorators.context_singleton import context_singleton

@context_singleton
class LibraryGraph(FrameworkObject):
  def __init__(self, backend_name):
    self.backend_name = backend_name
    self.graph = Pipeline(name=self.__class__.__name__)
    self.all_libraries = dict() #id:library
    self.__library_id_count = 0

  def __getNewLibraryId(self):
    self.__library_id_count += 1
    return self.__library_id_count

  def addLibray(self, library):
    library_id = self.__getNewLibraryId()
    self.all_libraries[library_id] = library

class Library(FrameworkObject):
  def __init__(self, name, path):
    self.name = name
    self.path = path
    self.dpdencies = []

  def setId(self, library_id):
    def cannotSetId(library_id):
      raise MepintaError('You cannot change a library id once is has been set')
    self.__library_id = library_id
    self.setId = cannotSetId
  @property
  def library_id(self):
    return self.__library_id

class PluginLibrary(Library):
  pass

class PluginMetadata(FrameworkObject):
  def __init__(self):
    #TODO: passing all data in initialization
    pass
    #To be initialized
    #self.name = None
    #self.build_name = None
    #self.version = 0
    #self.library_path = None
    #self.package = None
    #self.info = None
  def __str__(self):
    return self.name
  def __repr__(self):
    return '%r,%r' % (self.name, self.version)

class DataTypeMetadata(PluginMetadata):
  def __init__(self):
    #TODO: passing all data in initialization
    #List of processors dependent on this data type
    self.processors = []
    self.property_id = None
    #To be initialized #TODO: make a decorator to make sure they are initialized
      #self.info = None
  def __wrapped_lo__(self):
    if self.property_id != None:
      return self.property_id
    else:
      raise RuntimeError('Property: %s has no property_id defined' % self.name)
  def getShortName(self):
    return  self.name.split('.')[-1]
  def get_c_namespace(self):
    if self.name.startswith('c.') or self.name.startswith('mepinta.'):
      return self.getShortName()
    return self.name.replace('.', '_')
  c_namespace = property(get_c_namespace, None, None, None)

class ProcessorMetadata(PluginMetadata):
  def __init__(self):
    self.data_types = [] #data types used by this processor
    #We need to keep the functions ids across reloads
    self.functions = None #Leave it like this! Means functions were not loaded! #name:property_id
  def getFollowLibraryPath(self):
    pass
