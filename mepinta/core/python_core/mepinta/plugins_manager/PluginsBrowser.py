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
from mepinta.context.MepintaContext import MepintaContext
import os

class PluginsBrowser(FrameworkBase):
#  def __post_init__(self):
#    pass
  def plugins_path(self):
    plugins_path = (__file__.split(os.sep))[:-2]+['plugins']
    return plugins_path
  def import_packmod(self, packmod_path):
    packmod_path = 'plugins.%s'%packmod_path
    try:  
      module = __import__( packmod_path, fromlist="dummy")
      return module
    except Exception as e:
      self.context.log.last_exception() #TODO: add a config for this printing
      self.context.log.debug('Couldnt import %r. Exception: %r'%(packmod_path,e))
      return None
        
if __name__ == "__main__":
  context = MepintaContext('python')
  pb = PluginsBrowser(context=context)
