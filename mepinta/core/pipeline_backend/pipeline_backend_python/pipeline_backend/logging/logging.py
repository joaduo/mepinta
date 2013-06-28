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

log_level_dict = { 'critical':1,'error':10, 'warning':20,'info':30,'verbose':40,'debug':50,'debug_trace':60,'all_trace':70}

LOG_CRITICAL=1
LOG_ERROR=10
LOG_WARNING=20
LOG_INFO=30
LOG_VERBOSE=40
LOG_DEBUG=50
LOG_DEBUG_TRACE=60
LOG_ALL_TRACE=70

log_level=LOG_DEBUG #default log level
def set_log_level(level):
  global log_level
  log_level = level

def log_critical(msg):
  print_log(msg, LOG_CRITICAL)

def log_error(msg):
  print_log(msg, LOG_ERROR)

def log_warning(msg):
  print_log(msg, LOG_WARNING)
    
def log_info(msg):
  print_log(msg, LOG_INFO)

def log_verbose(msg):
  print_log(msg, LOG_VERBOSE)

def log_debug(msg):
  print_log(msg, LOG_DEBUG)

def log_trace(msg): #In fact this is 
  print_log(msg, LOG_DEBUG_TRACE)

def print_log(msg,level):
  if log_level >= LOG_DEBUG_TRACE:
    if level >= LOG_DEBUG or log_level >= LOG_ALL_TRACE:
      print_trace()
  if log_level >= level:
    if level <= LOG_ERROR: #TODO: change back
#    if level <= LOG_WARNING:
      print_trace('stderr')
      sys.stderr.write(msg+'\n')
    else:
      sys.stdout.write(msg+'\n')

import traceback
def print_trace(output=''):
  if output== 'stderr':
    sys.stderr.write(''.join(traceback.format_stack())) 
    if log_level >= LOG_DEBUG:
      sys.stderr.flush()   
  else:
    sys.stdout.write(''.join(traceback.format_stack()))
    if log_level >= LOG_DEBUG:
      sys.stdout.flush()    

def print_file_and_line(output=None):
  sys.stdout.write(''.join(traceback.format_stack()[-2:-1]))
  if output:
    sys.stdout.write(output)  

def shedskin_type_generation_logging():
  msg = 'Something to log'
  set_log_level(0)
  log_critical(msg)
  log_error(msg)
  log_warning(msg)
  log_info(msg)
  log_verbose(msg)
  log_debug(msg)
  set_log_level(LOG_CRITICAL)
#  log_trace(msg)

if __name__ == '__main__':
  shedskin_type_generation_logging()
#  log_info('Info shouldn\'t be printed')
#  #log_level_dict = { 'critical':1,'error':10, 'warning':20,'info':30,'verbose':40,'debug':50,'debug_trace':60,'all_trace':70}
#  set_log_level(LOG_INFO)
#  log_info('Info should be printed')
#  set_log_level(LOG_ALL_TRACE)
#  log_info('REALLY VERBOSE')

