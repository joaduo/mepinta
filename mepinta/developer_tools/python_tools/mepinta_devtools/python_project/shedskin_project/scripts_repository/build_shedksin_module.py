#!/usr/bin/python
import sys
import subprocess
import os

try:
  import shedskin
except Exception as e:
  sys.stderr.write('You need Shedskin installed in your Python path. Check http://code.google.com/p/shedskin/.\n')
  raise e

def generateCodeAndBuild():
  #===============================================================================
  # Parameters
  #===============================================================================

  backend_path = '../shedskin_builtin_lib'
  python_module = 'pipeline_lo_facade'

  # First generate the CPP code
  sys.argv.append("-e")  # It's an extension module
  sys.argv.append("-L")  # Add the backend library path to the builtin modules
  sys.argv.append(backend_path)
  sys.argv.append(python_module)

  #Run type analysis
  shedskin.main()

  # Now compile calling make
  compile_module = True
  #compile_module = False
  if compile_module:
    subprocess.call("make")

if __name__ == '__main__':
  generateCodeAndBuild()
