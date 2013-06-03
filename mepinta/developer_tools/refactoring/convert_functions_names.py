from functions_names import functions_names

functions_names2 = '''set_level
__print_log
print_trace
get_output
set_output
set_level
last_exception
test_module
get_fd
get_path
get_mask
on_python_3
get_current_contexts
get_log
get_config_store
has_config
get_config
set_config
__get_config_key
__config_key_str
_create_properties_safe
create_properties
_create_func_properties_safe
create_func_properties
_create_functum_properties_safe
create_functum_properties
'''

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
  old_names = set(old_names.splitlines())
  for name in old_names:
    new_name = getNewName(name)
    print name, new_name

if __name__ == '__main__':
  convert(functions_names)
