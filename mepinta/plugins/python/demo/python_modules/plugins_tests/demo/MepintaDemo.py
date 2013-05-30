# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo

This file is part of Mepinta.

Mepinta is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Mepinta is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Mepinta. If not, see <http://www.gnu.org/licenses/>.
'''
import argparse
from plugins_tests.demo.MepintaSimpleDemos import MepintaSimpleDemos
from common.abstract.FrameworkBase import FrameworkBase

class MepintaDemo(FrameworkBase):
  '''
  Creates the command line interface to run Mepinta Python Demos.
  '''
  def run(self):
    parser = self.__getParser()
    args = parser.parse_args()
    demos_dict = self.__getDemosDict()
    if len(args.demo_numbers) == 0:
      parser.print_help()
      self.__printDemosList(demos_dict)
    else:
      self.__runDemos(args.demo_numbers, demos_dict)

  def __runDemos(self, demo_numbers, demos_dict):
    for number in demo_numbers:
      names = sorted(demos_dict.keys())
      if number < len(names):
        self.log('Running demo: %r' % names[number])
        demos_dict[names[number]]()
      else:
        self.log.warning('Demo %s doesn\'t exist' % number)

  def __printDemosList(self, demos_dict):
      self.log('\nAvailable demos:')
      for index, name in enumerate(sorted(demos_dict.keys())):
        method = demos_dict[name]
        if method.__doc__:
          self.log('    %s:  %r:%s' % (index, name, method.__doc__))
        else:
          self.log('    %s:  %r' % (index, name))

  def __getDemosDict(self):
    demos_dict = {}
    simple_demos = MepintaSimpleDemos(self.context)
    for name in MepintaSimpleDemos.__dict__:
      if not name.startswith('_'):
        demos_dict[name] = getattr(simple_demos, name)
    return demos_dict

  def __getParser(self):
    parser = argparse.ArgumentParser(description='Mepinta demos.')
    parser.add_argument('demo_numbers', type=int, nargs='*', help='Specify the demo number(s) you would like to run.')
    parser.add_argument('--debug', action='store_true', help='Enable debug output.')
    return parser

def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()
  MepintaDemo(context).run()

if __name__ == "__main__":
  test_module()
