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

try:
  import shedskin
except Exception as e:
  sys.stderr.write('You need Shedskin installed in your Python path. Check http://code.google.com/p/shedskin/.\n')
  raise e

def copyShedskinModule(python_module):
  module_lib = '%s.so' % python_module
  dst_module_lib = 'mepinta/pipeline/lo_cpp/%s' % module_lib
  if os.path.exists(module_lib):
    if os.path.exists(dst_module_lib):
      os.remove(dst_module_lib)
    shutil.copy(module_lib, dst_module_lib)

def generateShedskinCppCode(python_module, makefile, flags_file, cmd_args=[]):
  # First generate the CPP code
  sys.argv.append('-e')
  sys.argv.extend(['-m', makefile])
  sys.argv.extend(['-L', '../shedskin_builtin_lib'])
  sys.argv.extend(['-f', flags_file])
  sys.argv.extend(cmd_args)
  sys.argv.append(python_module)

  #Run type analysis
  shedskin.main()

def compileShedskinModuleAndCopy(python_module, makefile):
  # Now compile calling make
  compile_module = True
  #compile_module = False
  if compile_module:
    make = subprocess.Popen(['make', '--makefile=%s' % makefile])
    make.wait()
    #make.stdout
  copy_module = True
  #copy_module = False
  if copy_module:
    copyShedskinModule(python_module)

def testModule():
  pass

if __name__ == "__main__":
  testModule()
