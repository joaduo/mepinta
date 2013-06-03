from functions_names import functions_names

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
  for name in old_names[:10]:
    if not name.startswith('#'):
      new_name = getNewName(name)
      print name, new_name

if __name__ == '__main__':
  convert(functions_names)
