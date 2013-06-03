from functions_names import functions_names
import os
from subprocess import Popen
import subprocess
import shlex

def getNewName(name):
  split_name = name.split('_')
  count = 0
  for part in split_name:
    if part != '':
      continue
    count += 1
  name_start = '_' * count
  name_end = split_name[count]
  for part in split_name[count + 1:]:
    name_end += part[0].upper() + part[1:]
  return '%s%s' % (name_start, name_end)

def convert(old_names):
  old_names = list(set(old_names.splitlines()))
  old_names.sort()
  old_names.reverse()
  name_list = []
  for name in old_names[:]:
    if not name.startswith('#'):
      new_name = getNewName(name)
      name_list.append((name, new_name))
  return name_list

def createReplaceDict(name_list):
  replace_dict = {}
  for name, _ in name_list:
    name_re = re.compile(r'%s' % name)
    replace_dict[name] = name_re
  return replace_dict

import re
def replaceNames(name_list, replace_dict, text):
  for name, new_name in name_list:
    text = replace_dict[name].sub(new_name, text)
  return text

def getFileNames():
  os.chdir('/home/jduo/001-Mepinta/git/mepinta/mepinta')
  args = shlex.split('find ./ -iname "*.py"')
  p = Popen(args, stdout=subprocess.PIPE)
  files = p.stdout.read()
  files = files.splitlines()
  new_files = []
  for f in files:
    if "developer_tools/refactoring" not in f:
      new_files.append(f)
  return new_files

def refactorProject(files_names):
  name_list = convert(functions_names)
  replace_dict = createReplaceDict(name_list)
  for f_name in files_names:
    f = open(f_name, 'rw')
    text = f.read()
    text = replaceNames(name_list, replace_dict, text)
    print 'done with %s' % f_name.split('/')[-1]
    #f.write(text)
    f.close()


if __name__ == '__main__':
  name_list = convert(functions_names)
  #name_list = [('unwrap_lo', 'unwrapLo')]
  text = "asldkmasdl unwrap_lo() lkamsdlkamsd "
  #print replaceNames(name_list, createReplaceDict(name_list), text)
  files_names = getFileNames()
  refactorProject(files_names)

