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
from pipeline_backend.logging.logging import log_critical, log_debug, log_error, \
  log_info, log_warning, log_verbose, set_log_level

class LogOutput(object):
  def critical(self, msg):
    log_critical(msg)
  def error(self, msg):
    log_error(msg)
  def warning(self, msg):
    log_warning(msg)
  def info(self, msg):
    log_info(msg)
  def debug(self, msg):
    log_debug(msg)
  def verbose(self, msg):
    log_verbose(msg)
  def set_level(self, level):
    set_log_level(level)
#  def trace(self, msg):
#    log_trace(msg)

def shedskin_LogOutput():
  lo = LogOutput()
  msg = 'Log message'
  lo.set_level(0)
  lo.critical(msg)
  lo.debug(msg)
  lo.error(msg)
  lo.info(msg)
  lo.warning(msg)
  lo.verbose(msg)
  lo.set_level(1)

