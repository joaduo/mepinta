#!/usr/bin/python
import os
import fnmatch
import sys

def findFiles(directory, pattern):
  for root, _, files in os.walk(directory, followlinks=True):
    for basename in files:
      if fnmatch.fnmatch(basename, pattern):
        filename = os.path.join(root, basename)
        yield filename

def debugPrint(msg):
  sys.stdout.write(msg + '\n')

def cleanShedskinCode():
  for ext in ['cpp', 'hpp', 'ss.py']:
    debugPrint('Deleting *.%s ...' % ext)
    for path in findFiles(os.path.dirname(__file__), '*.%s' % ext):
      os.remove(path)
  try:
    os.remove('Makefile')
  except:
    pass
  debugPrint('Done')

if __name__ == '__main__':
  cleanShedskinCode()