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
from mepinta.context.MepintaContext import MepintaContext
from pipeline_backend.logging.logging import LOG_INFO, LOG_DEBUG
from k3d.load_libs import load_k3d_libs
from common.config.ContextWrapper import ContextWrapper
from mepinta.abstract.MepintaError import MepintaError

called_once = False
def getDefaultContext(log_level=LOG_DEBUG):
  '''Creates a default context to reduce verbosity on start.'''
  global called_once
  if called_once:
    raise MepintaError('You should call the default context only once. Then you should pass it in the constructors for FrameworkBase child classes.')
  else:
    called_once = True
  load_k3d_libs()
  context = MepintaContext('c_and_cpp')
  context = ContextWrapper(context)
  context.log.set_level(log_level)
  return context

if __name__ == "__main__":
  print(getDefaultContext(LOG_DEBUG))
  try:
    print(getDefaultContext(LOG_INFO))
  except MepintaError as me:
    print(me)