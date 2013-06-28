# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

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
from pipeline_backend.logging.logging import logCritical, logDebug, logError, \
  logInfo, logWarning, logVerbose, setLogLevel

class LogOutput(object):
  def critical(self, msg):
    logCritical(msg)
  def error(self, msg):
    logError(msg)
  def warning(self, msg):
    logWarning(msg)
  def info(self, msg):
    logInfo(msg)
  def debug(self, msg):
    logDebug(msg)
  def verbose(self, msg):
    logVerbose(msg)
  def setLevel(self, level):
    setLogLevel(level)
#  def trace(self, msg):
#    logTrace(msg)

def shedskin_LogOutput():
  lo = LogOutput()
  msg = 'Log message'
  lo.setLevel(0)
  lo.critical(msg)
  lo.debug(msg)
  lo.error(msg)
  lo.info(msg)
  lo.warning(msg)
  lo.verbose(msg)
  lo.setLevel(1)

