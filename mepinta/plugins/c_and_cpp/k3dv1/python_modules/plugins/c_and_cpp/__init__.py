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
from mepinta_devtools.dev_manager_cli.DevelopmentManagerCli import DevelopmentManagerCli
from common.path import joinPath

def loadBackendSdkLibs(self, context):
  if self.context.backend_name == 'c_and_cpp':
    from mepinta.pipeline.lo_cpp.load_library_stand_alone import loadLibraryStandAlone
    libs_path = DevelopmentManagerCli(context).getLibsPath(self.context.backend_name)
    libs = [ joinPath(libs_path, 'libbackend_api_%s.so' % api) for api in ['c', 'cpp']]
    for lib in libs:
      loadLibraryStandAlone(lib, symbol="global")

def preLoadPlugin(context, manifest):
  if not context.hasConfig('libs_loaded', __file__):
    loadBackendSdkLibs(context)
    context.setConfig('libs_loaded', True, __file__)
