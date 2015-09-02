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
from common.path import joinPath
from mepinta_devtools.ide_projects.FileManager import FileManager
from string import Template
import os


class TemplateManager(FrameworkBase):

    def __post_init__(self, path_ref):
        self.__path_ref = path_ref
        self.file_manager = FileManager(self.context)

    def getTemplate(self, template_name, **kwargs):
        template_path = joinPath(self.getRepoPath(), template_name)
        template = self.file_manager.loadTextFile(template_path)
        if len(kwargs):
            return Template(template).safe_substitute(kwargs)
        else:
            return template

    def getRepoPath(self):
        return joinPath(os.path.dirname(self.__path_ref), 'templates_repository')

    def copyScripts(self, repo_subpath, deployment_path, scripts_names):
        path = joinPath(self.getRepoPath(), repo_subpath)
        self.file_manager.copyFiles(path, deployment_path, scripts_names)
