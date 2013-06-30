#!/usr/bin/python
from build_common import generateShedskinCppCode, compileShedskinModuleAndCopy

def build():
  python_module = 'load_library_stand_alone'
  makefile = 'LoadLibraryStandAloneMakefile'
  generateShedskinCppCode(python_module, makefile, 'LOAD_LIBRARY_STAND_ALONE_FLAGS')
  compileShedskinModuleAndCopy(python_module, makefile)

if __name__ == '__main__':
  build()
