#!/usr/bin/python
# -*- coding: utf-8 -*-
'''
Mepinta
'''
import subprocess
import shlex
import os

def buildLibrary():
  os.chdir(os.path.dirname(__file__))
  for cmd in ('qmake ${TARGET}.pro', 'make'):
    cmd = shlex.split(cmd)
    subprocess.call(cmd)

if __name__ == "__main__":
  buildLibrary()
