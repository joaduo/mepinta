# -*- coding: utf-8 -*-

#http://docs.python.org/2/library/argparse.html#module-argparse

import argparse
from plugins_tests.demo.MepintaSimpleDemos import MepintaSimpleDemos
from common.abstract.FrameworkBase import FrameworkBase

class MepintaDemo(FrameworkBase):
  def run(self):
    parser = self.__getParser()
    args = parser.parse_args()
    demos_dict = self.__getDemosDict()
    if len(args.demo_numbers) == 0:
      parser.print_help()
      self.log('\nAvailable demos:')
      for index, name in enumerate(demos_dict.keys()):
        self.log('    %s:  %r' % (index, name))
    else:
      for number in args.demo_numbers:
        names = demos_dict.keys()
        if number < len(names):
          self.log('Running demo: %r' % names[number])
          demos_dict[names[number]]()

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
    return parser

def test_module():
  from default_context import getDefaultContext
  context = getDefaultContext()
  MepintaDemo(context).run()

if __name__ == "__main__":
  test_module()
