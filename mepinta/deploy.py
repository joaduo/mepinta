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


class DeploymentCommand(object):

    '''
    This class creates a new deployment of a Mepinta software.
    This way code and installation are split to simplify maintenance.
    '''

    def __fake_post_init__(self, debug):
        from mepinta_devtools.deployment.DeploymentManager import DeploymentManager
        from pipeline_backend.logging.logging import LOG_INFO, LOG_DEBUG
        from getDefaultContext import getDefaultContext
        if debug:
            self.context = getDefaultContext(LOG_DEBUG)
        else:
            self.context = getDefaultContext(LOG_INFO)
        self.log = self.context.log
        self.deployment_manager = DeploymentManager(self.context,
                                                    mepinta_source_path=self._getMepintaSrcPath())

    def run(self, argv=None):
        # get the parser and parse the sys.argv arguments
        parser = self._getArgsParser()
        args = parser.parse_args(argv)

        # Add mepinta python paths to python
        self._configurePythonPaths(self._getMepintaSrcPath())
        self.__fake_post_init__(args.debug)
        self.log.debug('Successfully configured python paths.')
        # Do the actual deployment
        self.deployment_manager.deployTo(
            parser, args.deployment_path, args.force)

    def _getArgsParser(self):
        parser = argparse.ArgumentParser(
            description='Mepinta deployment script.')
        help_ = 'Specify the path for a new Mepinta deployment. (will be created ' \
                'if not existent)'
        parser.add_argument('deployment_path', action='store', help=help_)
        help_ = 'Force the deployment to an existing non-empty path.'
        parser.add_argument('--force', action='store_true', help=help_)
        help_ = 'Enable debug output.'
        parser.add_argument('--debug', action='store_true', help=help_)
        return parser

    def _configurePythonPaths(self, mepinta_source_path):
        '''
        Configures sys.path to include all Mepinta's python code necessary for
        the deployment.
        :param mepinta_source_path: Path where Mepinta code's was downloaded/
                                  extracted
        '''
        sys.path.append(mepinta_source_path + '/developer_tools/python_tools')
        from mepinta_devtools.deployment.PythonPathManager import PythonPathManager
        PythonPathManager().appendInitial(mepinta_source_path)

    def _getMepintaSrcPath(self):
        mepinta_source_path = os.path.dirname(os.path.realpath(__file__))
        return mepinta_source_path


def main(argv):
    DeploymentCommand().run(argv)

if __name__ == '__main__':
    main(None)
