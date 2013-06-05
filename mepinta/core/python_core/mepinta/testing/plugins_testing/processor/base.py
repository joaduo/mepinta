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
from common.abstract.FrameworkBase import FrameworkBase
from mepinta.abstract.MepintaError import MepintaError
from mepinta.testing.plugins_testing.time.TestTime import TestTime
from unittest import TestCase

tests_context = None
class ProcessorPluginTestBase(FrameworkBase):
  '''Base class for plugins' test modules.

  Tests inheriting this class should re-implement the defilePipeline and
  stressPipeline method.
  Optionally they also can reimplement getTimeParameters method.

  In general concrete class test won't inherit from this class, but will inherit
  from an intermediate abstract class that prepares the input and output
  automatically

  For an intermediate class example, check:
   mepinta.testing.plugins_testing.processor.K3dMeshPluginTest.K3dMeshPluginTest
  '''
  def __init__(self, context=None):
    #Initialize the class if inheriting from TestCase
    if isinstance(self, TestCase): #If using unittest, then initialize the class
      #Keep signature
      if isinstance(context, str):
        methodName = context
        context = None
        TestCase.__init__(self, methodName)
      else:
        TestCase.__init__(self)

    #Solve context if not provided
    global tests_context
    if context == None:
      if tests_context == None: #To enable context free initialization supporting unittest.TestCase
        from default_context import getDefaultContext
        tests_context = getDefaultContext()
      context = tests_context
    FrameworkBase.__init__(self, context)

  def __post_init__(self):
    #list of tested processors (target of the test class)
    self.__tested_processors = []
    self.__time = TestTime()

  @property
  def time(self): #TODO: rename it to test_time or time_specifier
    '''Time helper instance.'''
    return self.__time

  @property
  def tested_processors(self):
    '''List of processors (modules) target of this test case.'''
    return self.__tested_processors

  def getWatchedProcessors(self):
    '''Returns a list of the processors (modules) to be watched in the interac-
    tive tests. (i.e. when running this test in interactive mode)
    In general the watched processors will be the tested processors, but may or
    may include other processors.
    You probably will not re-implement this method.
    When a processors is being watched means that it's implementation is being
    watched for changes (through Inotify in Linux)
    '''
    if not len(self.tested_processors):
      raise MepintaError('You should set self.tested_processor on test __post_init__ method.')
    return self.tested_processors

  define_once = True
  def definePipeline(self, test_pline):
    '''Defines the pipeline for testing a processor.
    In other words, it defines the inputs for the tested processor.
    Also may define a 'tail' pipeline to process the output to check its
    validity. (visually, in the case of an interactive test)
    '''
    raise NotImplementedError('You should implement %s on children classes' % self.createPipeline)

  def getTimeParameters(self):
    '''
      Returns a dict or a tuple of time start, time end, time step and time sleep
      Example:
        def getTimeParameters(self):
          return dict(start=0., end=100., step=1., sleep=0.05)
      The same as
        def getTimeParameter(self):
          return 0,100,1,0.05
    '''
    return None

  def stressStart(self, test_pline, time):
    '''Called just before the first frame of the stress test.(time=start time)'''
    pass

  def stressEnd(self, test_pline, time):
    '''Called just after the last frame of the stress test. (time= end time)'''
    pass

  def stressPipeline(self, test_pline, time):
    '''This function receives the pipeline previously defined in 'definePipeline'
    method and a time value. With that, the end user can define a pertinent test
    to the target processor/s.

    The time can be manipulated re-implementing the 'getTimeParameters' method.
    '''
    pass

  def runTest(self):
    from mepinta.testing.plugins_testing.test_pipeline.InotifySimpleTestPipeline import InotifySimpleTestPipeline
    test_pline = InotifySimpleTestPipeline(self.context)
    self.definePipeline(test_pline)
    test_pline.evaluateProp()

if __name__ == "__main__":
  pass
