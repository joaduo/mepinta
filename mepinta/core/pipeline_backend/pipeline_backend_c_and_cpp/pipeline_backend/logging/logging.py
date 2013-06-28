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
'''
Created on Sep 15, 2011

@author: jduo
'''
import sys

LOG_CRITICAL=1
LOG_ERROR=10
LOG_WARNING=20
LOG_INFO=30
LOG_VERBOSE=40
LOG_DEBUG=50
LOG_DEBUG_TRACE=60
LOG_ALL_TRACE=70

log_level=LOG_INFO
def set_log_level(level):
  global log_level
  log_level = level

def print_log(level,msg):
  pass

def print_trace(output=''):
  pass

def log_critical(msg):
  print_log(LOG_CRITICAL,msg)

def log_error(msg):
  print_log(LOG_ERROR,msg)
    
def log_warning(msg):
  print_log(LOG_WARNING,msg)

def log_info(msg):
  print_log(LOG_INFO,msg)

def log_verbose(msg):
  print_log(LOG_VERBOSE,msg)

def log_debug(msg):
  print_log(LOG_DEBUG,msg)

def shedskin_type_generation_logging():
  msg = 'Something to log'
  log_critical(msg)
  log_error(msg)
  log_warning(msg)
  log_info(msg)
  log_verbose(msg)
  log_debug(msg)

if __name__ == '__main__':
  set_log_level(LOG_ERROR)
  log_info('Info shouldn\'t be printed')
  set_log_level(LOG_INFO)
  log_info('Info should be printed')
  set_log_level(LOG_ALL_TRACE)
  log_info('REALLY VERBOSE')

