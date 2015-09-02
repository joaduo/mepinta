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
 * int.c
 *
 *  Created on: Nov 3, 2011
 *      Author: jduo
 */

#include <mepintasdk/sdk.h>
#include <mepintasdk/log.h>
#include "int.h"

DECLARE_MEMORY_MNGMNT_FUNCTIONS();
//DECLARE_MEMORY_MNGMNT_FUNCTIONS(GARBAGE_COLLECTED);

//This function is never published, since it's called solving it's symbol from the handle
EXPORTED_SYMBOL char * MP_get_data_type_name(void){
  return "int";
}

void * MP_int_new(void){
  //TODO: this should never happen? //Anyway its optimized
  if(sizeof(int) > sizeof(void*)){ //Needs to allocate memory (ILP32 (i386) architecture for example)
    return MP_calloc(sizeof(int),1);
  }
  else{ //Directly using void* to store the int (LP64 (amd64))
    return NULL;
  }
}

void * MP_int_delete(void* int_v){
  if(sizeof(int) > sizeof(void*)){
    MP_free(int_v);
  }
  return NULL; //Return NULL on success
}

//TODO: check memcpy
void * MP_int_copy(void* int_v){
  if(sizeof(int) > sizeof(void*)){
    int * new_int_v = MP_malloc(sizeof(int));
    *new_int_v = *(int*) int_v;
    return new_int_v;
  }
  else{ //Directly using void* to store the int
    return int_v;
  }
}

size_t MP_int_data_type_size(void){
  return sizeof(int);
}

size_t MP_int_mem_size(void* int_v){
  log_debug("Reporting size of MP_int at %p\n",int_v);
  if(sizeof(int) > sizeof(void*)){
    return sizeof(int);
  }
  else{
    return 0; //0 Because the it's stored in the same void pointer
  }
}

passing_t MP_int_variable_passing(void){
  return by_value;
}
