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

#TODO: get values from the header or from shedskin
LOG_CRITICAL=1
LOG_ERROR=10
LOG_WARNING=20
LOG_INFO=30
LOG_VERBOSE=40
LOG_DEBUG=50
LOG_DEBUG_TRACE=60
LOG_ALL_TRACE=70

log_level=LOG_INFO #By default we print Infos and below
def set_log_level(level):
  global log_level
  log_level = level

def log_critical(msg):
  if log_level >= LOG_CRITICAL:
    print_trace('stderr')
    sys.stderr.write(msg+'\n')

def log_error(msg):
  if log_level >= LOG_ERROR:
    print_trace('stderr')
    sys.stderr.write(msg+'\n')

def log_warning(msg):
  if log_level >= LOG_WARNING:
    print_log(msg)
    
def log_info(msg):
  if log_level >= LOG_INFO:
    print_log(msg)

def log_verbose(msg):
  if log_level >= LOG_VERBOSE:
    print_log(msg)

def log_trace(msg): #In fact this is 
  if log_level >= LOG_DEBUG:
    print_trace()
    print_log(msg)

def log_debug(msg):
  if log_level >= LOG_DEBUG:
    print_log(msg)
  elif log_level >= LOG_DEBUG_TRACE:
    log_trace(msg)

def print_log(msg):
  if log_level >= LOG_ALL_TRACE:
    print_trace()
  print (msg)

#SHEDSKIN:OFF
import traceback
def print_trace(output=''):
  if output== 'stderr':
    #SHEDSKIN:OFF
    sys.stderr.write(''.join(traceback.format_stack())) 
    #SHEDSKIN:ON
    #sys.stderr.write('On python prints the call stack. I swear.')
    if log_level >= LOG_DEBUG:
      sys.stderr.flush()   
  else:
    #SHEDSKIN:OFF
    print(''.join(traceback.format_stack()))
    #SHEDSKIN:ON
    #print('On python prints the call stack. I swear.')
    if log_level >= LOG_DEBUG:
      sys.stdout.flush()    

def shedskin_type_generation_logging():
  msg = 'Something to log'
  log_critical(msg)
  log_error(msg)
  log_warning(msg)
  log_info(msg)
  log_verbose(msg)
  log_debug(msg)
  log_trace(msg)

if __name__ == '__main__':
  log_info('Info shouldn\'t be printed')
  #log_level_dict = { 'critical':1,'error':10, 'warning':20,'info':30,'verbose':40,'debug':50,'debug_trace':60,'all_trace':70}
  set_log_level(LOG_INFO)
  log_info('Info should be printed')
  set_log_level(LOG_ALL_TRACE)
  log_info('REALLY VERBOSE')

