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

#include <mepintasdk/sdk.h>
#include "functum.h"

DECLARE_MEMORY_MNGMNT_FUNCTIONS(GARBAGE_COLLECTED)

//This function is never published in the .h, since it's called solving it's symbol from the handle
EXPORTED_SYMBOL char * MP_get_data_type_name(void){
  return TO_STRING(functum_st*);
}

//void * MP_functum_new(void){
//  return empty_string;
//}

//void * MP_functum_delete(void* functum_v){
//  if (functum_v != empty_string){
//    MP_free(functum_v);
//  }
//  return NULL;
//}

//void * MP_functum_copy(void* functum_v){
//  if(functum_v != empty_string){
//    functum new_functum_v = MP_malloc(strlen(functum_v));
//    strcpy(new_functum_v,functum_v);
//    return new_functum_v;
//  }
//  else{
//    return empty_string;
//  }
//}

size_t MP_functum_data_type_size(void){
  return sizeof(functum);
}

size_t MP_functum_mem_size(void* functum_v){
  return sizeof(functum);
}

