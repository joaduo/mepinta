#!/usr/bin/python
import os
import sys
import re

def findFiles(directory, comp_re):
  for root, _, files in os.walk(directory, followlinks=True):
    for basename in files:
      if comp_re.match(basename):
        filename = os.path.join(root, basename)
        yield filename

def debugPrint(msg):
  sys.stdout.write(msg + '\n')

def cleanShedskinCode():
  comp_re = re.compile(r'.*\.(ss\.py|hpp|cpp)$')
  debugPrint('Deleting *.hpp, *.cpp, *.ss.py ...')
  for path in findFiles(os.path.dirname(__file__), comp_re):
    os.remove(path)
  base_path = os.path.dirname(__file__)
  for basename in os.listdir(base_path):
    if basename.endswith('_Makefile'):
      debugPrint('Deleting %r' % basename)
      os.remove(basename)
  debugPrint('Done')

if __name__ == '__main__':
  cleanShedskinCode()
