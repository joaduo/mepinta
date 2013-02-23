#!/usr/bin/python
import shedskin
import sys
import subprocess

#===============================================================================
# Parameters
#===============================================================================

backend_path = '##BACKEND_PATH'
python_module = 'pipeline_lo_facade'

if __name__ == '__main__':
  # First generate the CPP code
  sys.argv.append("-e")  # It's an extension module
  sys.argv.append("-L")  # Add the backend library path to the builtin modules
  sys.argv.append(backend_path)

  sys.argv.append(python_module)

  # Now compile calling make
  # compile_module = False
  compile_module = True
  if compile_module:
    subprocess.call("make")
