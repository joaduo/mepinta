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

class FunctionPropertyValue(object):
  def __init__(self,func_id):
    self.func_id = func_id
    self.args = None

class FunctumPropertyValue(FunctionPropertyValue):
  def __init__(self, func_id, functum_prop):
    FunctionPropertyValue.__init__(self,func_id)
    self.functum_prop = functum_prop
  def setFunctumProp(self, functum_prop):
    self.functum_prop = functum_prop
  def getFunctumProp(self):
    return self.functum_prop
  
def shedskin_hidden_data_types(prop):
  func_id = 100
  fpv= FunctionPropertyValue(func_id)
  fumpv =FunctumPropertyValue(func_id, prop)
  fumpv.setFunctumProp(functum_prop=prop)
  fumpv.getFunctumProp()
  return fpv

if __name__ == "__main__":
  pass
