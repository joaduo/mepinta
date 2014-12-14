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
from mepinta_devtools.templates.DictionaryBasedTranslator import DictionaryBasedTranslator
from mepinta_devtools.ide_projects.FileManager import FileManager


class ModuleCreator(FrameworkBase):

    def __post_init__(self):
        self.file_manager = FileManager(self.context)

    def getContent(self, template, translation_dict):
        if template != None:
            return DictionaryBasedTranslator(self.context).getContent(template, translation_dict)
        else:
            return ''

    def create(self, path, template=None, translation_dict={}, overwrite=False):
        if not path.lower().endswith('.py'):
            path = '%s.py' % path
        self.log.d('Creating module at %r' % (path))
        module_content = self.getContent(template, translation_dict)
        self.file_manager.saveTextFile(path, module_content, overwrite)
