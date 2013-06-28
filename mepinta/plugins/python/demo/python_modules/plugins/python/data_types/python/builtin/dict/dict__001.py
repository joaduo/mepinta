# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

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

data_type_description = {
# 'plugin_url':'http://mepinta.joaquinduo.com.ar/plugins/',
# 'future_plugin_url':'http://mepinta.joaquinduo.com.ar/plugins/',
# 'additional_urls':{},
# 'authors':'Joaquín Duo',
# 'description':'''Simple python string data type. In fact there is no real API for this, since it handles consistency easily''',
# 'changes':'First writing',
# 'api':'python', #What kind of api is available for accessing this data
# 'python_module':None,
}

def new():
  return dict()

def copy(dict_):
  return dict(dict_)

def delete(dict_):
  pass

def copyTo(to_dict, from_dict):
  to_dict.clear()
  to_dict.update(from_dict)
  return to_dict
