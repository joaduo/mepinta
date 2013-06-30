#!/usr/bin/python
from build_common import generateShedskinCppCode, compileShedskinModuleAndCopy

def build():
  python_module = 'load_library_stand_alone'
  generateShedskinCppCode(python_module)
  compileShedskinModuleAndCopy(python_module)

if __name__ == '__main__':
  build()
