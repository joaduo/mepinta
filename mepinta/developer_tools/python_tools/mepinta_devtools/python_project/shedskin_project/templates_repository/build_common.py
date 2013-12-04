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
import sys
import subprocess
import os
import shutil
import shlex
import argparse
import re

try:
  import shedskin
except Exception as e:
  msg = 'You need Shedskin installed in your Python path. Check http://code.google.com/p/shedskin/.\n'
  raise ImportError('%s  ImportError:%s' % (msg, e))

class ShedskinModuleBuilder(object):
  '''
  Class responsible of generating shedskin code for a given python module.
  Will also compile it and clean the code (but won't clean the compiled library)
  It will also copy the resulting library
  '''
  def logInfo(self, msg):
    #simple logging
    print(msg)

  def logError(self, msg):
    #simple logging
    sys.stderr.write(msg + '\n')

  def copyShedskinModule(self, python_module):
    #Copy the compiled .so module to the destination directory
    module_lib = '%s.so' % python_module #TODO:Distribution Platform
    dst_module_lib = 'mepinta/pipeline/lo_cpp/%s' % module_lib
    if os.path.exists(module_lib):
      if os.path.exists(dst_module_lib):
        os.remove(dst_module_lib)
      shutil.copy(module_lib, dst_module_lib)

  def getMakefileName(self, python_module):
    #Each module will get its own Makefile (in order to coexist together)
    return '%s_Makefile' % python_module

  def generateShedskinCppCode(self, python_module, cmd_args=[]):
    # First generate the CPP code simulating the program arguments.
    sys.argv.append('-e') #create extension
    sys.argv.append('-n') #silent
    makefile = self.getMakefileName(python_module)
    sys.argv.extend(['-m', makefile]) #output makefile name
    sys.argv.extend(['-L', '../shedskin_builtin_lib']) #other builtin libs
    flags_file = '%s_FLAGS' % python_module #compiler flags file
    if os.path.exists(flags_file): #if the file exist use it
      sys.argv.extend(['-f', flags_file])
    sys.argv.extend(cmd_args) #add other args
    sys.argv.append(python_module) #python module to convert

    self.logInfo('Generating shedskin module %s ...' % python_module)
    #Run type analysis
    shedskin.main()
    self.logInfo('Done generating %s.' % python_module)

  def compileShedskinModule(self, python_module):
    # Now compile calling make
    makefile = self.getMakefileName(python_module)
    self.logInfo('Compiling and building shedskin module %s ...' % python_module)
    cmd = 'make --makefile=%s' % makefile
    cmd_split = shlex.split(cmd)
    p = subprocess.Popen(cmd_split, stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE)
    r_value = p.wait()
    stderr = p.stderr.read()
    stdout = p.stdout.read()
    if r_value != 0:
      self.logError('There was an error building %s.so cmd=%r.' % (python_module, cmd))
      self.logError(stderr)
      self.logError(stdout)
      self.sys.exit(r_value)
    self.logInfo('Done building %s.' % python_module)

  def generateAndBuild(self, python_module, generate, build):
    if generate:
      #generate CPP code from python
      self.generateShedskinCppCode(python_module)
    if build:
      #compile the CPP code
      self.compileShedskinModule(python_module)
      #copy the module to the mepinta code to be used
      self.copyShedskinModule(python_module)

  def _cleanModuleName(self, python_module):
    python_module = os.path.basename(python_module)
    python_module, _ = os.path.splitext(python_module)
    return python_module

  def run(self, argv=None, python_module=None):
    #get the parser and parse the sys.argv arguments
    script_path = os.path.realpath(__file__)
    os.chdir(os.path.dirname(script_path))

    parser = self._getArgsParser(specify_module=not python_module)
    args = parser.parse_args(argv)

    if args.clean:
      self.cleanShedskinCode()
      return
    #reset argv (used to pass arguments to shedksin)
    sys.argv = sys.argv[:1]

    python_module = python_module or args.python_module
    python_module = self._cleanModuleName(python_module)
    generate = not os.path.exists(self.getMakefileName(python_module)) or \
              args.generate
    build = not os.path.exists('%s.so' % python_module) or args.compile
    if generate or build:
      #We need to generate and/or compile.
      self.generateAndBuild(python_module, generate, build)
    else:
      self.logInfo('Nothing to do.')

  def _getArgsParser(self, specify_module=True):
    parser = argparse.ArgumentParser(description='Mepinta Shedskin Generation '
                                     'and Compilation Script.')
    if specify_module:
      help_ = 'Specify the python module name of the module to be translated.'
      parser.add_argument('python_module', action='store', help=help_)
    help_ = 'Force shedskin code generation.'
    parser.add_argument('--generate', action='store_true', help=help_)
    help_ = 'Force shedskin code compilation.'
    parser.add_argument('--compile', action='store_true', help=help_)
    help_ = 'Clean all shedskin generated files.'
    parser.add_argument('--clean', action='store_true', help=help_)
    help_ = 'Enable debug output.'
    parser.add_argument('--debug', action='store_true', help=help_)
    return parser


  def _findFiles(self, directory, comp_re):
    for root, _, files in os.walk(directory, followlinks=True):
      for basename in files:
        if comp_re.match(basename):
          filename = os.path.join(root, basename)
          yield filename

  def cleanShedskinCode(self):
    comp_re = re.compile(r'.*\.(ss\.py|hpp|cpp)$')
    self.logInfo('Deleting *.hpp, *.cpp, *.ss.py ...')
    script_path = os.path.realpath(__file__)
    base_path = os.path.dirname(script_path)
    for path in self._findFiles(base_path, comp_re):
      os.remove(path)
    for basename in os.listdir(os.curdir):
      if basename.endswith('_Makefile'):
        self.logInfo('Deleting %r' % basename)
        os.remove(basename)
    self.logInfo('Done')

def main(argv):
  ShedskinModuleBuilder().run(argv)

if __name__ == '__main__':
  main(None)

