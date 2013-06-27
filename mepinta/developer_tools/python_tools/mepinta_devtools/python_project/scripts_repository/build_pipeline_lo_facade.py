#!/usr/bin/python
import shedskin
import sys
import subprocess
from deployment_config import deployment_config
import os

def generateCodeAndBuild():
  #===============================================================================
  # Parameters
  #===============================================================================

  backend_path = os.path.join(deployment_config().mepinta_source_path, 'core/pipeline_backend/pipeline_backend_c_and_cpp')
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
