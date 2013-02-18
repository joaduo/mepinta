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

#include "TypedCollectorManager.h"

void TypedCollectorManager::appendCollector(iTypedPropertiesCollector* collector){
  collectors.push_back(collector);
}

iTypedPropertiesCollector* TypedCollectorManager::popCollector(){
  iTypedPropertiesCollector* return_value = collectors.back();
  collectors.pop_back();
  return return_value;
}

int TypedCollectorManager::collectProperties(){
  int collected_count = 0;
  //We ask for the lib_hanlde in order to filter properties later
  void* lib_handle;

  int cur_index = first_prop_index;
  char* prop_name;
  void** prop;
  //Gather inputs (only charp)
  while((prop = MP_next_prop(args,in_out_id,&lib_handle,&prop_name,&cur_index))
          != NULL){
    for(size_t i=0 ; i < collectors.size(); ++i){
      collected_count += collectors[i]->collectStep(prop,prop_name,lib_handle,cur_index);
    }
    log_debug("TypedCollectorManager prop_name: %s, lib_handle: %p collected_count: %d\n",prop_name,lib_handle,collected_count);
  }

  return collected_count;
}


