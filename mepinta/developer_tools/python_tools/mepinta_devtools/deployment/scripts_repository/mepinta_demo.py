# -*- coding: utf-8 -*-

#http://docs.python.org/2/library/argparse.html#module-argparse

import argparse

parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('integers', metavar='N', type=int, nargs='+',
                   help='an integer for the accumulator')
parser.add_argument('--sum', dest='accumulate', action='store_const',
                   const=sum, default=max,
                   help='sum the integers (default: find the max)')

args = parser.parse_args()
print args.accumulate(args.integers)

#crear el deployment_config.py

#correr el comando solo lista los demos
# por ahora sería un solo demo del núcleo (solo ver el output)
# luego un demo del núcleo con nodebox
# por último un demo de nodebox con k3d
