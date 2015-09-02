//Mepinta
//Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar
//
//This file is part of Mepinta.
//
//Mepinta is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//Mepinta is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Mepinta. If not, see <http://www.gnu.org/licenses/>.

#ifndef ITYPEDPROPERTIESCOLLECTOR_H_
#define ITYPEDPROPERTIESCOLLECTOR_H_

//TODO: rename to iPropertiesCollector, since the criteria could be anything
class iTypedPropertiesCollector{
public:
  //iTypedPropertiesCollector() {}
  virtual int collectStep(void** prop, const char* prop_name,const void* lib_handle, const int cur_index) = 0;
  virtual ~iTypedPropertiesCollector() {}
};

#endif /* ITYPEDPROPERTIESCOLLECTOR_H_ */
