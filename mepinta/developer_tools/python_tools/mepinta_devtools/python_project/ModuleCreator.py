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

class ModuleCreator(FrameworkBase):
  def getContents(self, template, translation_dict):
    if template != None:
      return DictionaryBasedTranslator(self.context).getContent(template, translation_dict)
    else:
      return ''
  def create(self, path, template=None, translation_dict={}):
    if not path.lower().endswith('.py'):
      path = '%s.py' % path
    self.context.log.verbose('Creating module at %r' % (path))
    file_contents = self.getContents(template, translation_dict)
    f = open(path, "w")
    if file_contents != "":
      f.write(file_contents)
    f.close()

if __name__ == "__main__":
  pass
