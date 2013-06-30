#!/usr/bin/python
from build_common import generateShedskinCppCode, compileShedskinModuleAndCopy

def build():
  python_module = 'pipeline_lo_facade'
  makefile = 'PipelineLoFacadeMakefile'
  generateShedskinCppCode(python_module, makefile, 'PIPELINE_LO_FACADE_FLAGS')
  compileShedskinModuleAndCopy(python_module, makefile)

if __name__ == '__main__':
  build()
