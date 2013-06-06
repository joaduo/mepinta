#!/usr/bin/python
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
  '''
  This class creates a new deployment of a Mepinta software.
  This way code and installation are split to simplify maintenance.
  '''
  def __fake_post_init__(self, debug):
    from mepinta_devtools.deployment.DeploymentScriptsCopier import DeploymentScriptsCopier
    from mepinta_devtools.deployment.DeploymentConfigCreator import DeploymentConfigCreator
    from mepinta_devtools.ide_projects.FileManager import FileManager
    from pipeline_backend.logging.logging import LOG_INFO, LOG_DEBUG
    from default_context import getDefaultContext
    if debug:
      self.context = getDefaultContext(LOG_DEBUG)
    else:
      self.context = getDefaultContext(LOG_INFO)
    self.log = self.log
    self.file_mananger = FileManager(self.context)
    self.deployment_config_creator = DeploymentConfigCreator(self.context)
    self.deployment_scripts_copier = DeploymentScriptsCopier(self.context)

  def run(self):
    parser = self._getArgsParser()
    args = parser.parse_args()

    self._configurePythonPaths(self._getMepintaSrcPath())
    self.__fake_post_init__(args.debug)
    self.log.debug('Successfully configured python paths.')

    self._deployTo(args.deployment_path, args.force)

  def _getArgsParser(self):
    parser = argparse.ArgumentParser(description='Mepinta deployment script.')
    parser.add_argument('deployment_path', action='store', help='Specify the path for a new Mepinta deployment. (will be created if not existent)')
    parser.add_argument('--force', action='store_true', help='Force the deployment to an existing non-empty path.')
    parser.add_argument('--debug', action='store_true', help='Enable debug output.')
    return parser

  def _configurePythonPaths(self, mepinta_source_path):
    '''
    Configures sys.path to include all Mepinta's python code necessary for the deployment.
    :param mepinta_source_path: Path where Mepinta code's was downloaded/extracted
    '''
    sys.path.append(mepinta_source_path + '/developer_tools/python_tools')
    from mepinta_devtools.deployment.PythonPathManager import PythonPathManager
    PythonPathManager().appendAll(mepinta_source_path)

  def _getMepintaSrcPath(self):
    mepinta_source_path = os.path.dirname(os.path.realpath(__file__))
    return mepinta_source_path

  def _deployTo(self, deployment_path, force=False):
    #Check if the path specified is outside mepinta source path
    if not self._outOfSourcePath(deployment_path):
      self.log.warning('Deployment path %r is inside Mepinta source path %r. (deployment path must reside outside Mepinta source path)' % (deployment_path, self._getMepintaSrcPath()))
      return
    #Check if the deployment already exists
    if self._emptyDeploy(deployment_path) or force:
      if not self.file_mananger.pathExists(deployment_path):
        self.log.debug('Creating deployment path %r' % deployment_path)
        os.makedirs(deployment_path)
      self.log('Deploying mepinta to %r.' % deployment_path)
      self.deployment_config_creator.createDeploymentConfig(deployment_path, self._getTranslationDict(), overwrite=force)
      self.deployment_scripts_copier.copyScriptsTo(deployment_path)
    else:
      self.log.warning('Deployment is not empty use the --force flag to overwrite it.')
      self._getArgsParser().print_help()

  def _getTranslationDict(self):
    translation_dict = {'mepinta_source_path':self._getMepintaSrcPath(),
                        }
    return translation_dict

  def _outOfSourcePath(self, deployment_path):
    common_prefix = os.path.commonprefix([self._getMepintaSrcPath(), os.path.realpath(deployment_path)])
    return common_prefix != self._getMepintaSrcPath()

  def _emptyDeploy(self, deployment_path):
    return not self.file_mananger.pathExists(deployment_path) or self.file_mananger.listDir(deployment_path) == []

if __name__ == '__main__':
  Deployment().run()
