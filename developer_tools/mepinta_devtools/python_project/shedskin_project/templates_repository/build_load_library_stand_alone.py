#!/usr/bin/python
from build_common import ShedskinModuleBuilder


def main(argv):
    ShedskinModuleBuilder().run(python_module='load_library_stand_alone')

if __name__ == '__main__':
    main(None)
