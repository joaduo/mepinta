# -*- coding: utf-8 -*-
'''
Mepinta
'''
import subprocess
import shlex

def buildLibrary():
  for cmd in ('qmake ${TARGET}.pro', 'make'):
    cmd = shlex.split(cmd)
    subprocess.call(cmd)

if __name__ == "__main__":
  buildLibrary()
