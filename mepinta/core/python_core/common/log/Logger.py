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
import traceback
import sys

class DefaultOutput(object):
  __levels = { 'critical':1, 'error':10, 'warning':20, 'info':30, 'verbose':40, 'debug':50, 'debug_trace':60, 'all_trace':70}
  def __init__(self):
    self.__log_level = self.__levels['debug']

  def setLevel(self, level):
    if level.lower() in self.__levels:
      self.__log_level = self.__levels[level.lower()]
    else:
      sys.stderr.write('Inexistent log level %s \n' % level)

  def critical(self, msg):
    self.__printLog(msg, 'CRITICAL')
  def error(self, msg):
    self.__printLog(msg, 'ERROR')
  def warning(self, msg):
    self.__printLog(msg, 'WARNING')
  def info(self, msg):
    self.__printLog(msg, 'INFO')
  def verbose(self, msg):
    self.__printLog(msg, 'VERBOSE')
  def debug(self, msg):
    self.__printLog(msg, 'DEBUG')
  def trace(self, msg):
    self.__printLog(msg, 'DEBUG_TRACE')

  def __printLog(self, msg, level):
    level = self.__levels[level.lower()]
    if self.__log_level >= self.__levels['debug_trace']:
      if level >= self.__levels['debug'] or self.__log_level >= self.__levels['all_trace']:
        self.printTrace()
    if self.__log_level >= level:
      if level <= self.__levels['error']:
        self.printTrace('stderr')
        sys.stderr.write(msg + '\n')
      else:
        sys.stdout.write(msg + '\n')

  def printTrace(self, output=''):
    if output == 'stderr':
      sys.stderr.write(''.join(traceback.format_stack()))
      if self.__log_level >= self.__levels['debug']:
        sys.stderr.flush()
    else:
      sys.stdout.write(''.join(traceback.format_stack()))
      if self.__log_level >= self.__levels['debug']:
        sys.stdout.flush()

class Logger(object):
  def __init__(self, output=None):
    if not output:
      output = DefaultOutput()
    self.output = output
  def getOutput(self):
    return self.__output
  def setOutput(self, value):
    self.__output = value
  def critical(self, msg):
    self.output.critical(str(msg))
  def error(self, msg):
    self.output.error(str(msg))
  def warning(self, msg):
    self.output.warning(str(msg))
  def info(self, msg):
    #self.trace()
    self.output.info(str(msg))
  def debug(self, msg):
    #self.trace()
    self.output.debug(str(msg))
  def verbose(self, msg):
    self.output.verbose(str(msg))

  #Shortcuts
  def c(self, msg):
    self.critical(msg)
  def e(self, msg):
    self.error(msg)
  def w(self, msg):
    self.warning(msg)
  def i(self, msg):
    self.info(msg)
  def d(self, msg):
    self.debug(msg)
  def v(self, msg):
    self.verbose(msg)

  def setLevel(self, level):
    self.output.setLevel(level)
  def __call__(self, msg):
    self.info(msg)
  def trace(self, output=''):
    if output == 'stderr':
      sys.stderr.write(''.join(traceback.format_stack()))
      sys.stderr.flush()
    else:
      sys.stdout.write(''.join(traceback.format_stack()))
      sys.stdout.flush()
  def lastException(self, level='debug'):
    tb_list = traceback.extract_tb(sys.exc_info()[2])
    tb_list = traceback.format_list(tb_list)
    msg = ''.join(tb_list)
    if level == 'debug':
      self.debug(msg)
    elif level == 'error':
      self.error(msg)
    else:
      self.info(msg)
  output = property(getOutput, setOutput, None, None)

if __name__ == '__main__':
  logger = Logger()
  logger.critical('critical')
  logger.debug('debug')
  logger.error('error')
  logger.info('info')
  logger.warning('warning')
  logger('info')
