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
from common.abstract.FrameworkObject import FrameworkObject

class TestTime(FrameworkObject):
  '''
  TestTime methods makes it easy to specify the amount of time
  a test should take and the evaluation recurrence.
  All methods returns the same data type, but each one specify it in different
  ways.
  '''
  def framesAndFPS(self, frames=15, fps=20):
    '''Generates almost realtime parameters for the test.'''
    start = 0.
    sleep = 1 / float(fps)
    end = frames * sleep #fixed => reatime is supposed
    step = sleep       #fixed => reatime is supposed
    return start, end, step, sleep
  def framesAndTime(self, frames=15, seconds=1.5):
    '''Generates almost realtime parameters for the test.'''
    return self.framesAndFPS(frames, frames / float(seconds))
  def startEnd(self, start=0., end=1.5):
    '''Generates almost realtime parameters for the test.'''
    sleep = 1 / 20. #fixed => reatime is supposed
    step = sleep  #fixed => reatime is supposed
    return start, end, step, sleep
  def startEndAndFps(self, start=0., end=30., fps=10.):
    '''Generates almost realtime parameters for the test.'''
    sleep = 1 / float(fps)
    step = end - start / 1.5 #always 1.5 seconds (fixed)
    return start, end, step, sleep
  def frames(self, frames):
    return self.framesStepSleep(frames)
  def framesStepSleep(self, frames=15, step=1., sleep=1 / 20.):
    start = 0.
    end = frames * step
    return start, end, step, sleep
  def startDurationAndStep(self, start=0., duration=150., step=10.):
    '''Realtime and Non realtime parameters (depending on the user input).'''
    end = start + duration
    sleep = 1 / 20.
    return start, end, step, sleep
  def startEndStepSleep(self, start=0., end=15., step=1., sleep=1 / 20.):
    '''Realtime and Non realtime parameters (depending on the user input).
    Offers complete control of the time given to the 'stressPipeline' method
    '''
    return start, end, step, sleep


if __name__ == "__main__":
  pass
