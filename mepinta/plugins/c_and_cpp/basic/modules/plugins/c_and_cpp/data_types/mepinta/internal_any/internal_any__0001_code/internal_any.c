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
 * internal_any.c
 *
 *  Created on: Nov 3, 2011
 *      Author: jduo
 */

#include <mepintasdk/sdk.h>
#include <mepintasdk/log.h>
#include "internal_any.h"

//DECLARE_MEMORY_MNGMNT_FUNCTIONS();
DECLARE_MEMORY_MNGMNT_FUNCTIONS(GARBAGE_COLLECTED);

//This function is never published, since it's called solving it's symbol from the handle
EXPORTED_SYMBOL char * MP_get_data_type_name(void){
  return "internal_any";
}

void * MP_internal_any_new(void){
  return MP_calloc(sizeof(internal_any),1);
}

void * MP_internal_any_delete(void* intern_any){
  ASSERT_RETURN(intern_any!=NULL,"ERROR: Trying to delete NULL internal_any value");
  log_debug("Freeing plugin internal data at %p",intern_any);
  //Free the memory with the given function
  internal_any* internal_any_v_casted = (internal_any*)intern_any;
  if(internal_any_v_casted->delete_function !=NULL && internal_any_v_casted->data != NULL){
    if(internal_any_v_casted->delete_function(internal_any_v_casted->data) != NULL){
      log_error("Couldn't delete data at %p with function at %p, for internal_any at %p"
                ,internal_any_v_casted->data
                ,internal_any_v_casted->delete_function
                ,internal_any_v_casted);
    }
    else{
      log_debug("Successfully deleted internal_any data at %p.",internal_any_v_casted->data);
    }
  }
  else{ //Something was NULL
    if(internal_any_v_casted->data == NULL){
      log_error("You have supplied NULL data for internal_any at %p.",internal_any_v_casted);
    }
    if(internal_any_v_casted->delete_function == NULL){
      log_error("You have supplied NULL delete_function for internal_any at %p.",internal_any_v_casted);
      log_error("Beware! This may mean a memory leak.");
    }
  }
  //Free the memory of the allocated struct
  log_debug("Freeing memory at %p.",intern_any);
  MP_free(intern_any);
  return NULL; //We return NULL on success
}

//TODO: check memcpy
void * MP_internal_any_copy(void* intern_any){
  internal_any* new_intern_any = MP_malloc(sizeof(internal_any));
  log_warning("Beware! Making a shallow copy of a internal_any value. You shouldn't copy an internal_any value anyway.");
  MP_memmove(new_intern_any,intern_any,sizeof(internal_any));
  return new_intern_any;
}

size_t MP_internal_any_data_type_size(void){
  return sizeof(internal_any);
}

size_t MP_internal_any_mem_size(void* intern_any){
  //TODO: fix
  log_debug("Reporting 'shallow' size of internal_any at %p\n",intern_any);
  return sizeof(internal_any);
}

passing_t MP_internal_any_variable_passing(void){
  return by_reference;
}

