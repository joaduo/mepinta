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
from common.abstract.FrameworkBase import FrameworkBase
from mepinta_devtools.ide_projects.FileManager import FileManager
from common.path import joinPath
from mepinta_devtools.templates.TemplateManager import TemplateManager
import os


class DeploymentCreator(FrameworkBase):

    '''
    Auxiliary class to help DeploymentManager
      -Creates deployment scripts
      -translate template and save them in the deployment
    '''

    def __post_init__(self):
        self.__templates = TemplateManager(self.context, path_ref=__file__)
        self.file_manager = FileManager(self.context)

    def createConfig(self, deployment_path, translation_dict,
                     template_name='deployment_config.py', overwrite=False):
        file_path = joinPath(deployment_path, 'deployment_config.py')
        content = self.__templates.getTemplate(
            template_name, **translation_dict)
        self.file_manager.saveTextFile(file_path, content, overwrite)

    def copyScripts(self, deployment_path):
        scripts_names = [
            'mepinta_demo.py', 'mepinta_tests.py', 'mepinta_dev.py']
        self.__templates.copyScripts('', deployment_path, scripts_names)


class DeploymentManager(FrameworkBase):

    '''
    This class creates a new deployment of a Mepinta software.
    Is responsible of checking integrity of the deployment conditions.
    This way code and installation are split to simplify maintenance.
    '''

    def __post_init__(self, mepinta_src):
        self.file_manager = FileManager(self.context)
        self.deployment_creator = DeploymentCreator(self.context)
        self.mepinta_src = mepinta_src

    def _getSrcPath(self):
        return self.mepinta_src

    def deployTo(self, args_parser, deployment_path, force=False):
        # Check if the path specified is outside mepinta source path
        # TODO: add it to .ignore
        # if not self._outOfSourcePath(deployment_path):
        #  msg = 'Deployment path %r is inside Mepinta source path %r. (deployment' \
        #    ' path must reside outside Mepinta source path)' % (deployment_path,
        #                                                        self._getSrcPath())
        #  self.log.warning(msg)
        #  return
        # Check if the deployment already exists
        if self._emptyDeploy(deployment_path) or force:
            if not self.file_manager.pathExists(deployment_path):
                self.log.debug('Creating deployment path %r' % deployment_path)
                os.makedirs(deployment_path)
            self.log('Deploying mepinta to %r.' % deployment_path)
            self.deployment_creator.createConfig(deployment_path,
                                                 self._getTranslationDict(),
                                                 overwrite=force)
            self.deployment_creator.copyScripts(deployment_path)
        else:
            msg = 'Deployment is not empty use the --force flag to overwrite it.'
            self.log.w(msg)
            args_parser.print_help()

    def _getTranslationDict(self):
        translation_dict = {'mepinta_src': self._getSrcPath(),
                            }
        return translation_dict

    def _outOfSourcePath(self, deployment_path):
        common_prefix = os.path.commonprefix([self._getSrcPath(),
                                              os.path.realpath(deployment_path)])
        return common_prefix != self._getSrcPath()

    def _emptyDeploy(self, deployment_path):
        return not self.file_manager.pathExists(deployment_path) or \
            self.file_manager.listDir(deployment_path) == []
