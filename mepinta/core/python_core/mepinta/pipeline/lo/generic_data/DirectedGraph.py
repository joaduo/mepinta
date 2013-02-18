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

from mepinta.pipeline.lo.constants import NULL_UID

#Rename: DirectedGraphIterator
class DirectedGraphShedSkinIterator(object):
  def __init__(self, keys, values):
    self.current = 0
    self.keys = keys
    self.values = values
  def next(self):
    #TODO: rename next
    if self.current < len(self.keys):
      ids = (self.keys[self.current], self.values[self.current])
      self.current +=1
      return ids
    else:
      return (NULL_UID,0)

class DirectedGraph(object):
  def __init__(self):
    self.keys = []
    self.values = []
  def __delitem__(self, item_id):
    '''  Deletes Values for a specific id  '''
    index_lo, index_hi = self.bisect_left_right(self.keys,item_id)
    if index_lo != index_hi: #Ok, we do have the item, and is not an empty list
      del self.keys[index_lo:index_hi] #TODO: Fix for shedkin?
      del self.values[index_lo:index_hi]
  def __delslice__(self,id_1,id_2):
    if id_1 > id_2:
      return
    index_lo = self.bisect_left(self.keys,id_1)
    index_hi = self.bisect_right(self.keys,id_2)
    if index_lo != index_hi: #Ok is not an empty list
      if self.keys[index_lo] == id_1 and self.keys[index_hi-1] == id_2:
        del self.keys[index_lo:index_hi]
        del self.values[index_lo:index_hi]      
  def __getitem__(self,item_id): #TODO
    index_lo, index_hi = self.bisect_left_right(self.keys,item_id)
    if index_lo != index_hi:
      return self.values[index_lo:index_hi]
    else:
      return []
  def get_first(self, item_id): 
    #DEBUG, should check if items exist first? I guess this is not needed
    index = self.bisect_left(self.keys, item_id)
    return self.values[index]
  def __getslice__(self,id_1,id_2): #TODO
    if id_1 > id_2:
      return []
    index_lo = self.bisect_left(self.keys,id_1)
    index_hi = self.bisect_right(self.keys,id_2)
    if index_lo != index_hi: #Ok is not an empty list
      if self.keys[index_lo] == id_1 and self.keys[index_hi-1] == id_2:
        return self.values[index_lo:index_hi] 
      else:
        return []
  def __slice__(self, id_1, id_2):
    return self.__getslice__(id_1, id_2)
  def __len__(self):
    return len(self.keys)
  def __setitem__(self, item_id, value):
    lo,hi = self.bisect_left_right(self.keys,item_id)
    index = self.bisect_left(self.values, value, lo, hi)
    self.keys.insert(index,item_id)
    self.values.insert(index,value)
  def add(self, item_id, value):
    #TODO: should it check that it already has it?
    #When is it not convenient?
    return self.__setitem__(item_id, value)
  def remove(self, item_id, value):
    #TODO: here we are not checking boundaries correctly?
    lo,hi = self.bisect_left_right(self.keys,item_id)
    if lo != hi: #Ok is not an empty list
      index = self.bisect_left(self.values, value, lo, hi)
      if self.keys[index] == item_id and self.values[index] == value:
        self.keys.__delitem__(index)
        self.values.__delitem__(index)
  def count(self, item_id):
    index_lo, index_hi = self.bisect_left_right(self.keys,item_id)
    return index_hi - index_lo 
#  def extend(self, id_indexed_table): #TODO
#    raise RuntimeError('Not Implemented Yet!')
#  def __iter__(self):
#    raise RuntimeError('Not Supported by ShedSkin (as of 20110929) Use get_ss_iterator')
  def get_ss_iterator(self):
    #BEWARE this method supposes you will never get a 0 in the table
    #So you should stop when you get such a value NULL_UID (0)
    return DirectedGraphShedSkinIterator(self.keys,self.values)  
  def __contains__(self, item_id):
    index = self.bisect_left(self.keys,item_id)
    if len(self.keys) == index:
      return False
    elif self.keys[index] == item_id:
      return True
    else:
      return False
  def has(self, item_id, value):
    #TODO: here we are not checking boundaries correctly?
    lo,hi = self.bisect_left_right(self.keys,item_id)
    index = self.bisect_left(self.values, value, lo, hi)
    if lo != hi and len(self.keys) != index: #Ok is not an empty list
      if self.keys[index] == item_id and self.values[index] == value:
        return True
    return False
  def index(self, item_id):
    index = self.bisect_left(self.keys,item_id)
    if self.keys[index] == item_id:
      return index
    else:
      raise ValueError('%.index(x): x not in table'%self.__class__.__name__)
  def bisect_left_right(self, a, x, lo=0, hi=-1):
      """Return the index where to insert item x in list a, assuming a is sorted.
  
      The return value i is such that all e in a[:i] have e < x, and all e in
      a[i:] have e >= x.  So if x already appears in the list, a.insert(x) will
      insert just before the leftmost x already there.
  
      Optional args lo (default 0) and hi (default len(a)) bound the
      slice of a to be searched.

      Replaced def bisect_left(self,a, x, lo=0, hi=None): to hi=-1
        So that there is no type warnings on ShedSkin      
      """
  
      if lo < 0:
          raise ValueError('lo must be non-negative')
      if hi == -1:
          hi = len(a)
      
      if hi == 0:
        return lo,hi
      
      while lo < hi:
          mid = (lo+hi)//2
          value = a[mid]
          #On python 3 if you try to get an slice your code will crash here
          #use tbl.__getslice__(id1,id2) instead, so that it keeps copatibility with
          #shedskin
          if value < x: lo = mid+1
          elif value > x: hi = mid
          else: break #value == x
          
      if value == x: #We found the value, let's get its lo an hi indexes
        if a[hi-1] != x:
          hi = self.bisect_right(a, x, mid+1, hi)
        if a[lo] != x:
          lo = self.bisect_left(a, x, lo, mid)
      return lo,hi
  def bisect_right(self, a, x, lo=0, hi=-1):
      """Return the index where to insert item x in list a, assuming a is sorted.
  
      The return value i is such that all e in a[:i] have e <= x, and all e in
      a[i:] have e > x.  So if x already appears in the list, a.insert(x) will
      insert just after the rightmost x already there.
  
      Optional args lo (default 0) and hi (default len(a)) bound the
      slice of a to be searched.

      Replaced def bisect_left(self,a, x, lo=0, hi=None): to hi=-1
        So that there is no type warnings on ShedSkin      
      """
  
      if lo < 0:
          raise ValueError('lo must be non-negative')
      if hi == -1:
          hi = len(a)
      while lo < hi:
          mid = (lo+hi)//2
          if x < a[mid]: hi = mid
          else: lo = mid+1
      return lo
  def bisect_left(self,a, x, lo=0, hi=-1):
      """
      Return the index where to insert item x in list a, assuming a is sorted.
  
      The return value i is such that all e in a[:i] have e < x, and all e in
      a[i:] have e >= x.  So if x already appears in the list, a.insert(x) will
      insert just before the leftmost x already there.
  
      Optional args lo (default 0) and hi (default len(a)) bound the
      slice of a to be searched.
      
      Replaced def bisect_left(self,a, x, lo=0, hi=None): to hi=-1
        So that there is no type warnings on ShedSkin
      """
  
      if lo < 0:
          raise ValueError('lo must be non-negative')
      if hi == -1:
          hi = len(a)
      while lo < hi:
          mid = (lo+hi)//2
          if a[mid] < x:
            lo = mid+1
          else:
            hi = mid
      return lo    

#  def __delete__(self):
#    pass
  def __str__(self):
    str_ = ''
    for index,k in enumerate(self.keys):
      str_ += '%s:%s '%(k,self.values[index])
    return str_
#    return str(self.keys)+str(self.values)

def shedskin_DirectedGraph():
  a = [1,2,4,5,6,6,6,8,100,3221]
  b = [1,2,4,5,6,5,9,8,100,3221]
  tbl = DirectedGraph()
  tbl.keys = a
  tbl.values = b

  del tbl[1]
  #doesnt work! #TODO report shedskin
  #del tbl[2:5]
  tbl.__delslice__(2, 5)
  tbl[5]
  tbl.get_first(6)
  tbl.__getslice__(6, 100)
  tbl.__slice__(6, 100)
  #Unsupported on python 3, it tries to get an item passing a slice
  #tbl[6:100]
  len(tbl)
  tbl[1] = 10
  tbl.add(1, 11)
  tbl.remove(1, 10)
  tbl.count(6)
  iterator = tbl.get_ss_iterator()
  e = iterator.next()
  while e[0]!=0:
    e = iterator.next()
  6 in tbl #should return True
  tbl.has(1, 10) #should have it we already removed it
  tbl.index(6)
  str(tbl)

def shedskin_test():
  id_indexed_table = DirectedGraph()
  id_indexed_table.add(4, 543)
  id_indexed_table.add(4, 45)
  
  a = [1,2,4,5,6,6,6,8,100,3221]
  b = [1,2,4,5,6,5,9,8,100,3221]
  id_indexed_table = DirectedGraph()
  id_indexed_table.keys = a
  id_indexed_table.values = b
  print(id_indexed_table[1])
  print(id_indexed_table[6])
  id_indexed_table[1] = 20
  print(id_indexed_table[1])
  print(id_indexed_table)
  del id_indexed_table[1]
  id_indexed_table.__delslice__(2, 6) #TODO: why [:] doesnt work?
  print(id_indexed_table)
  print( id_indexed_table.__getslice__(8,3221)) #TODO: why [:] doesnt work?
  print( id_indexed_table.__slice__(8,3221))  #TODO: why [:] doesnt work?
  print(len(id_indexed_table))
  id_indexed_table.add(4, 543)
  id_indexed_table.add(4, 45)
  print(id_indexed_table.count(4))
  print(id_indexed_table.index(4))
  id_indexed_table.add(8, 8)
  id_indexed_table.add(8, 20)
  id_indexed_table.remove(8, 8)
  id_indexed_table.remove(8, 20)
  id_indexed_table.add(203, 423123)
  print(id_indexed_table)
    
if __name__ == '__main__':
  #import sys
#  test(sys.argv)
#  test(None)
  shedskin_DirectedGraph()
  shedskin_test()

