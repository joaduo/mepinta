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
from common.abstract.decorators.context_singleton import context_singleton
from mepinta.pipeline.lo.pipeline_data.data_model import Topology

@context_singleton
class LibraryGraph(FrameworkObject):
  def __init__(self, backend_name):
    self.backend_name = backend_name
    self.topology = Topology()
    self.all_libraries = dict() #id:library
    self.__library_id_count = 0

  def __getNewLibraryId(self):
    self.__library_id_count += 1
    return self.__library_id_count

  def addLibray(self, library):
    library_id = self.__getNewLibraryId()
    self.all_libraries[library_id] = library

class LibraryMetadata(FrameworkObject):
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

class PluginLibrary(LibraryMetadata):
  pass
