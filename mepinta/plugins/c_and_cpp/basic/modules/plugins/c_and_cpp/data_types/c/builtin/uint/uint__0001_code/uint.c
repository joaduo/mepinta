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

/*
 * uint.c
 *
 *  Created on: Nov 4, 2011
 *      Author: jduo
 */

#include <mepintasdk/sdk.h>
#include <mepintasdk/log.h>
#include "uint.h"

DECLARE_MEMORY_MNGMNT_FUNCTIONS();
//DECLARE_MEMORY_MNGMNT_FUNCTIONS(GARBAGE_COLLECTED);

//This function is never published, since it's called solving it's symbol from the handle
EXPORTED_SYMBOL char * MP_get_data_type_name(void){
  return "uint";
}

void * MP_uint_new(void){
  if(sizeof(uint) > sizeof(void*)){ //Needs to allocate memory (ILP32 (i386) architecture for example)
    return MP_calloc(sizeof(uint),1);
  }
  else{ //Directly using void* to store the uint (LP64 (amd64))
    return NULL;
  }
}

void * MP_uint_delete(void* uint_v){
  if(sizeof(uint) > sizeof(void*)){
    MP_free(uint_v);
  }
  return NULL; //Return NULL on success
}

//TODO: check memcpy
void * MP_uint_copy(void* uint_v){
  if(sizeof(uint) > sizeof(void*)){
    uint * new_uint_v = MP_malloc(sizeof(uint));
    *new_uint_v = *(uint*) uint_v;
    return new_uint_v;
  }
  else{ //Directly using void* to store the uint
    return uint_v;
  }
}

size_t MP_uint_data_type_size(void){
  return sizeof(uint);
}

size_t MP_uint_mem_size(void* uint_v){
  log_debug("Reporting size of MP_uint at %p\n",uint_v);
  if(sizeof(uint) > sizeof(void*)){
    return sizeof(uint);
  }
  else{
    return 0; //0 Because the it's stored in the same void pointer
  }
}

passing_t MP_uint_variable_passing(void){
  return by_value;
}

