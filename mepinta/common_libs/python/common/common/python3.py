'''
Created on Mar 18, 2012

@author: jduo
'''

import sys
import inspect

mayor_version = sys.version[0] 

def on_python_3():
  return mayor_version == '3'


def portable_getargspec(func):
  #TODO: is deprecated!
  return inspect.getargspec(func)


if __name__ == "__main__":
  print(on_python_3())
  