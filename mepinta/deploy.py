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
import sys
import os
import argparse

class Deployment(object):
  def run(self):
    self._configurePythonPaths(self._getMepintaSrcPath())
    parser = self._getArgsParser()
    args = parser.parse_args()
    self._deployTo(args.deployment_path, args.force)

  def _getArgsParser(self):
    parser = argparse.ArgumentParser(description='Mepinta deployment script.')
    parser.add_argument('deployment_path', type=str, nargs=1, help='Specify the path for a new Mepinta deployment.')
    parser.add_argument('--force', action='store_true', help='Force the deployment to the existing path.')
    return parser

  def _configurePythonPaths(self, mepinta_source_path):
    sys.path.append(mepinta_source_path + '/developer_tools/python_tools')
    from mepinta_devtools.deployment.PythonPathManager import PythonPathManager
    PythonPathManager().appendAll(mepinta_source_path)

  def _getMepintaSrcPath(self):
    f = os.path.realpath(__file__)
    mepinta_source_path = f[:f.rindex(os.sep)]
    return mepinta_source_path

  def _deployTo(self, deployment_path, force=False):
    if self._emptyDeploy(deployment_path) or \
       self._existingDeploy(deployment_path) and force:
      pass

  def _emptyDeploy(self, deployment_path):
    pass

  def _existingDeploy(self, deployment_path):
    pass

  def printHelp(self):
    pass

if __name__ == '__main__':
  Deployment().run()
#  deployment_path = '/home/jduo/001-Mepinta/EclipseProjects_GitRepo/mepinta_test_folders'
#  force = False
#  d = Deployment()
#  d.run()
  #d._deployTo(deployment_path, force)

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
