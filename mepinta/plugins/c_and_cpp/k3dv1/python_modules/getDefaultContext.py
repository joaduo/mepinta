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
from pipeline_backend.logging.logging import LOG_INFO, LOG_DEBUG
from k3d.load_libs import load_k3d_libs
from mepinta.context.getMepintaContext import getMepintaContext

called_once = False
def getDefaultContext(log_level=LOG_INFO):
  '''Creates a default context to reduce verbosity on start.'''
  global called_once
  if called_once:
    raise RuntimeError('You should call the default context only once. (in the main script)')
  else:
    called_once = True
  load_k3d_libs()
  context = getMepintaContext('python')
  context.log.set_level(log_level)
  return context

if __name__ == "__main__":
  debugPrint(getDefaultContext(LOG_DEBUG))
  try:
    debugPrint(getDefaultContext(LOG_INFO))
  except MepintaError as me:
    debugPrint(me)
