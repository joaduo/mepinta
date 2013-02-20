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
import re
from common.abstract.FrameworkObject import FrameworkObject

class DictionaryBasedTranslator(FrameworkObject):
  ''''''
  def __replace(self, processed_template, name, replacement, start_mark):
    re_replace = re.compile(r'%s%s' % (start_mark, name))
    if not isinstance(replacement, str):
      raise RuntimeError('replacement %r for %r variable should be a string.' % (replacement, name))
    return re_replace.sub(replacement, processed_template)

  def getContent(self, template, translation_dict, start_mark='##'):
    for name, replacement in translation_dict.items():
      processed_template = self.__replace(template, name, replacement, start_mark)
    return processed_template

def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  test_module()
