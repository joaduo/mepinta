from functions_names import functions_names
import os
from subprocess import Popen
import subprocess
import shlex
import re

def getFileNames():
  os.chdir('/home/jduo/001-Mepinta/EclipseProjects_GitRepo/mepinta_test_folders/test')
  args = shlex.split('find ./ -iname "*.py"')
  p = Popen(args, stdout=subprocess.PIPE)
  files = p.stdout.read()
  files = files.splitlines()
  new_files = []
  for f in files:
    if "developer_tools/refactoring" not in f:
      new_files.append(f)
  return new_files

name_re = re.compile(r'from\sdefault_context\simport\sgetDefaultContext')
def replaceFunction(text):
  text = name_re.sub('from getDefaultContext import getDefaultContext', text)

def filePrint(f_name):
  debugPrint '  File "%s", line 1' % f_name

def refactorProject(files_names):

  for f_name in files_names:
    f = open(f_name, 'r')
    text = f.read()
    f.close()
    hash1 = hash(text)
    if hash1 != hash(text):
      filePrint(os.path.realpath(f_name))
      f = open(f_name, 'w')
      f.write(text)
      f.close()



if __name__ == '__main__':
  files_names = getFileNames()
  refactorProject(files_names)

