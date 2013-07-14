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
import sys
import subprocess
import os
import shutil
import shlex

try:
  import shedskin
except Exception as e:
  msg = 'You need Shedskin installed in your Python path. Check http://code.google.com/p/shedskin/.\n'
  raise ImportError('%s  ImportError:%s' % (msg, e))

def logInfo(msg):
  print(msg)

def logError(msg):
  sys.stderr.write(msg + '\n')

def copyShedskinModule(python_module):
  module_lib = '%s.so' % python_module
  dst_module_lib = 'mepinta/pipeline/lo_cpp/%s' % module_lib
  if os.path.exists(module_lib):
    if os.path.exists(dst_module_lib):
      os.remove(dst_module_lib)
    shutil.copy(module_lib, dst_module_lib)

def getMakefileName(python_module):
  return '%s_Makefile' % python_module

def generateShedskinCppCode(python_module, cmd_args=[]):
  # First generate the CPP code
  sys.argv.append('-e') #create extension
  sys.argv.append('-n') #silent
  makefile = getMakefileName(python_module)
  sys.argv.extend(['-m', makefile]) #output makefile name
  sys.argv.extend(['-L', '../shedskin_builtin_lib']) #other builtin libs
  flags_file = '%s_FLAGS' % python_module #compiler flags file
  if os.path.exists(flags_file): #if the file exist use it
    sys.argv.extend(['-f', flags_file])
  sys.argv.extend(cmd_args) #add other args
  sys.argv.append(python_module) #python module to convert

  logInfo('Generating shedskin module %s ...' % python_module)
  #Run type analysis
  shedskin.main()
  logInfo('Done generating %s.' % python_module)

def compileShedskinModule(python_module):
  # Now compile calling make
  makefile = getMakefileName(python_module)
  logInfo('Building shedskin module %s ...' % python_module)
  cmd = 'make --makefile=%s' % makefile
  cmd_split = shlex.split(cmd)
  p = subprocess.Popen(cmd_split, stdout=subprocess.PIPE,
                       stderr=subprocess.PIPE)
  r_value = p.wait()
  stderr = p.stderr.read()
  stdout = p.stdout.read()
  if r_value != 0:
    logError('There was an error building %s.so cmd=%r.' % (python_module, cmd))
    logError(stderr)
    logError(stdout)
    sys.exit(r_value)
  logInfo('Done building %s.' % python_module)

def buildShedskinModule(python_module, generate=True, build=True):
  os.chdir(os.path.dirname(__file__))
  if generate:
    #generate CPP code from python
    generateShedskinCppCode(python_module)
  if build:
    #compile the CPP code
    compileShedskinModule(python_module)
    #copy the module to the mepinta code to be used
    copyShedskinModule(python_module)

