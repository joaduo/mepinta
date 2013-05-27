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
from common.path import pathExists

class Deployment(object):
  def appendPythonPaths(self):
    relative_paths = {'mepinta':'core/python_core',
                      'mepinta_devtools':'developer_tools/python_tools',
                      'common':'libs/python/python_common',
                      }
  def deployTo(self, deployment_path, force=False):
    if self._emptyDeploy(deployment_path) or \
       self._existingDeploy(deployment_path) and force:
      pass
      # poder correr demo de python por lo menos
      # crear proyecto de python y proyecto plugins de python
        # crear plugin set y su proyecto correspondiente
        # agregarlo a un plugins deployment
      # crear directorio
      # crear configuración
      # crear scripts de demo y tests
        # en python y en cpp
          # requirements for demos pyglet + nodebox
          # que cree un nuevo pipeline
          # que lo visualice y sea animable
      # crear scripts para crear un nuevo plugin set
        # que especifique librerías en c o cpp
  def _emptyDeploy(self, deployment_path):
    pass
  def _existingDeploy(self, deployment_path):
    pass
  def printHelp(self):
    pass

if __name__ == '__main__':
  deployment_path = '/home/jduo/001-Mepinta/EclipseProjects_GitRepo/mepinta_test_folders'
  force = False
  Deployment().deployTo(deployment_path, force)
