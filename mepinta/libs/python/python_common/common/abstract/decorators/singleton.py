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

class singleton_decorator(object):
  '''
    Singleton pattern decorator.
    There will be only one instance of the decorated class.
    Decorator always returns same instance.
  '''
  def __init__(self, class_):
    '''
    :param class_: class to be converted in singleton (means you cannot
    inherit from it anymore)
    '''
    self.class_ = class_
    self.instance = None

  def __call__(self, *a, **ad):
    '''
    Initialize class if not yet initialized. Return instance.
    '''
    if self.instance == None:
      self.instance = self.class_(*a, **ad)
    return self.instance
