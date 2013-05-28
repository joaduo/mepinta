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
import random

class Base2D(object):
  pass

class Point2D(Base2D):
  def __init__(self, x=0., y=0.):
    self.x = 0.
    self.y = 0.
  def __getitem__(self, index): #TODO set item, etc
    if index == 0:
      return self.x
    elif index == 1:
      return self.y

class Path2D(list):
  pass
#  def __init__(self):
#    self.points_indexes = []

class Geometry2D(Base2D):
  def __init__(self):
    self.points = []
    self.bezier_paths = []


def create_demo_data():
  geom2d = Geometry2D()
  for i in xrange(50):
    #geom2d.points.append((float(i*100),float(i*100)))
    geom2d.points.append([random.random() * 100 - 50, random.random() * 100 - 50])
  geom2d.bezier_paths.append([random.randint(0, len(geom2d.points) - 1) for i in xrange(30)])
  return geom2d

