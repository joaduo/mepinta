#!/usr/bin/python
from build_common import generateShedskinCppCode, compileShedskinModuleAndCopy

def build():
  python_module = 'pipeline_lo_facade'
  generateShedskinCppCode(python_module, '../shedskin_builtin_lib')
  compileShedskinModuleAndCopy(python_module)

if __name__ == '__main__':
  build()
