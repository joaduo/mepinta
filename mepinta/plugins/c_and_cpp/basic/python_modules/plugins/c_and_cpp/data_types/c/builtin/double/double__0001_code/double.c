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
 * double.c
 *
 *  Created on: Sep 29, 2011
 *      Author: jduo
 */

#include <mepintasdk/sdk.h>
#include <mepintasdk/log.h>
#include "double.h"

DECLARE_MEMORY_MNGMNT_FUNCTIONS();
//DECLARE_MEMORY_MNGMNT_FUNCTIONS(GARBAGE_COLLECTED);

//This function is never published, since it's called solving it's symbol from the handle
EXPORTED_SYMBOL char * MP_get_data_type_name(void){
  return "double";
}

void * MP_double_new(void){
  if(sizeof(double) > sizeof(void*)){ //Needs to allocate memory (ILP32 (i386) architecture for example)
    return MP_calloc(sizeof(double),1);
  }
  else{ //Directly using void* to store the double (LP64 (amd64))
    return NULL;
  }
}

void * MP_double_delete(void* double_v){
  if(sizeof(double) > sizeof(void*)){
    MP_free(double_v);
  }
  return NULL; //Return NULL on success
}

//TODO: check memcpy
void * MP_double_copy(void* double_v){
  if(sizeof(double) > sizeof(void*)){
    double * new_double_v = MP_malloc(sizeof(double));
    *new_double_v = *(double*) double_v;
    return new_double_v;
  }
  else{ //Directly using void* to store the double
    return double_v;
  }
}

size_t MP_double_data_type_size(void){
  return sizeof(double);
}

size_t MP_double_mem_size(void* double_v){
  log_debug("Reporting size of MP_double at %p\n",double_v);
  if(sizeof(double) > sizeof(void*)){
    return sizeof(double);
  }
  else{
    return 0; //0 Because the it's stored in the same void pointer
  }
}

passing_t MP_double_variable_passing(void){
  return by_value;
}
