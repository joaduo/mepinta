#!/usr/bin/python
from build_common import ShedskinModuleBuilder

def main(argv):
  ShedskinModuleBuilder().run(python_module='pipeline_lo_facade')

if __name__ == '__main__':
  main(None)
