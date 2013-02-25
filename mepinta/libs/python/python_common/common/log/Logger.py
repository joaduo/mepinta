'''
Created on Mar 14, 2012

@author: jduo
'''
import traceback
import sys

class DefaultOutput(object):
  __levels = { 'critical':1,'error':10, 'warning':20,'info':30,'verbose':40,'debug':50,'debug_trace':60,'all_trace':70}
  def __init__(self):
    self.__log_level = self.__levels['debug']

  def set_level(self, level):
    if level.lower() in self.__levels:
      self.__log_level = self.__levels[level.lower()]
    else:
      sys.stderr.write('Inexistent log level %s \n'%level)

  def critical(self, msg):
    self.__print_log(msg, 'CRITICAL')
  
  def error(self, msg):
    self.__print_log(msg, 'ERROR')
  
  def warning(self, msg):
    self.__print_log(msg, 'WARNING')
      
  def info(self, msg):
    self.__print_log(msg, 'INFO')
  
  def verbose(self, msg):
    self.__print_log(msg, 'VERBOSE')
  
  def debug(self, msg):
    self.__print_log(msg, 'DEBUG')
  
  def trace(self, msg): #In fact this is 
    self.__print_log(msg, 'DEBUG_TRACE')
    
  def __print_log(self, msg,level):
    level = self.__levels[level.lower()]
    if self.__log_level >= self.__levels['debug_trace']:
      if level >= self.__levels['debug'] or self.__log_level >= self.__levels['all_trace']:
        self.print_trace()
    if self.__log_level >= level:
      if level <= self.__levels['error']: 
        self.print_trace('stderr')
        sys.stderr.write(msg+'\n')
      else:
        sys.stdout.write(msg+'\n')

  def print_trace(self, output=''):
    if output== 'stderr':
      sys.stderr.write(''.join(traceback.format_stack())) 
      if self.__log_level >= self.__levels['debug']:
        sys.stderr.flush()
    else:
      sys.stdout.write(''.join(traceback.format_stack()))
      if self.__log_level >= self.__levels['debug']:
        sys.stdout.flush()    

class Logger(object):
  def __init__(self, output=DefaultOutput()):
    self.output = output
  def get_output(self):
    return self.__output
  def set_output(self, value):
    self.__output = value
  def critical(self,msg):
    self.output.critical(str(msg))
  def error(self,msg):
    self.output.error(str(msg))
  def warning(self,msg):
    self.output.warning(str(msg))
  def info(self,msg):
    self.output.info(str(msg))
  def debug(self,msg):
    self.output.debug(str(msg))
  def verbose(self, msg):
    self.output.verbose(str(msg))
  def set_level(self, level):
    self.output.set_level(level)
  def __call__(self,msg):
    self.info(msg)
  def trace(self, output=''):
    if output== 'stderr':
      sys.stderr.write(''.join(traceback.format_stack())) 
      sys.stderr.flush()   
    else:
      sys.stdout.write(''.join(traceback.format_stack()))
      sys.stdout.flush()    
  def last_exception(self, level='debug'):
    tb_list = traceback.extract_tb(sys.exc_info()[2])
    tb_list = traceback.format_list(tb_list)
    msg = ''.join(tb_list)
    if level=='debug':
      self.debug(msg)
    elif level == 'error':
      self.error(msg)
    else:
      self.info(msg)
  output = property(get_output, set_output, None, None)
    
if __name__ == '__main__':
  logger = Logger()
  logger.critical('critical')
  logger.debug('debug')
  logger.error('error')
  logger.info('info')
  logger.warning('warning')
  logger('Call')
