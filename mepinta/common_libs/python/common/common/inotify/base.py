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
import imp

class ModuleReloadBase(FrameworkBase):
  def _reloadModule(self, module):
    #if it's the main module, do a hack. (reload it as a different module from the filename)
    if module.__name__ == '__main__':
      self.log.debug('Reloading %r. (it\'s the main module)'%module)
      module = imp.load_source('__main__reloaded', module.__file__)
    else: #if it's other module, then simply reload it with imp
      self.log.debug('Reloading %r.'%module)
      imp.reload(module)
    #since the module won't be the same in the case of __main__ we need to redefine it on the caller
    return module  
        
if __name__ == "__main__":
  pass