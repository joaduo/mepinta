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
 * props_client_release.c
 *
 *  Created on: Nov 10, 2011
 *      Author: jduo
 */

#include <string.h>
#include <stdlib.h>

#include "sdkdef.h"
#include "log.h"
#include "memmngmt.h"
#include "args.h"
#include "props_client.h"
#include "types.h"

////TODO: remove this inlines and publish (EXPORT) this functions
int mepinta_get_hint_index();
//{ Property getting and setting

//Get the value for a declared property.
int MP_declare_prop_release(  int dst_dtyp_size
                                        , void** declared_value
                                        , MP_args_p args
                                        , short in_out_id
                                        , const char* prop_name){
  void** valuepp = MP_prop_byname_release(args,in_out_id,NULL,prop_name);

  if(dst_dtyp_size == sizeof(void*)) {
    log_debug("Passing 'by value' or 'by reference'. Can't distinguish.\n");
    *declared_value = *valuepp;
  }
  else if(dst_dtyp_size < sizeof(void*)){
    log_debug("Passing 'by value' on a small data size.\n");
    MP_memcpy_wrap(declared_value, valuepp,dst_dtyp_size);
  }
  else{
    log_debug("Passing 'by value' on a big data size.\n");
    MP_memcpy_wrap(declared_value,*valuepp,dst_dtyp_size);
  }

  return EXIT_SUCCESS;
}

//Get the property value (void**) and optionally "lib_handle" (if not NULL)
//from args given its name.
//Will make use of global variable "hint_index". This can or cannot be helpful.
//Make sure of re/setting its value using RESET_PROPS_HINT_INDEX macro
//or previous "set_props_hint_index(int index)" function.
void** MP_prop_byname_release(MP_args_p args, short in_out_id, void** lib_handle, const char* prop_name){
  mepinta_props* props = get_props(args,in_out_id);

  int i;
  for(i = mepinta_get_hint_index(); i< props->size ; ++i){
    if(strcmp(props->names[i],prop_name) == 0){
      break;
    }
  }
  if (i < props->size){ //found a value
    log_debug("Found value for '%s' at %p.\n",prop_name,props->values[i]);
    if(lib_handle != NULL){// We asume we have variable properties
      log_debug("Assuming variable properties. Getting data type library handle.\n");
      *lib_handle = props->handles[i];
    }
    MP_set_hint_index(args,i + 1); //We change it for later hints
    return props->values[i];
  }
  else if(mepinta_get_hint_index()){
    log_debug("Current hint index with value %d was not a useful hint. Restarting a full search.\n", mepinta_get_hint_index());
    MP_set_hint_index(args, 0);
    return MP_prop_byname_release(args,in_out_id,lib_handle,prop_name);
  }
  else{ //Could not find the value
    log_debug("Couldn't find '%s' in args at %p. Returning NULL.\n",prop_name,props);
    return NULL;
  }
}

//Similar to "get_next_prop" function, but the index is not increased
void** MP_prop_byindex_release(MP_args_p args, short in_out_id, void** lib_handle, char** prop_name, int index){
  mepinta_props* props = get_props(args,in_out_id);

  if (index < props->size){ //found a value
    log_debug_verbose("Getting value for '%s' at index=%d.\n",props->names[index],index);
    if(lib_handle != NULL){// We asume we have variable properties
      *lib_handle = props->handles[index];
    }
    if(prop_name != NULL){
      *prop_name = props->names[index];
    }
    return props->values[index];
  }
  else{ //Could not find the value
    log_debug("Couldn't find any value. Returning NULL.\n");
    return NULL;
  }
}

//This function is useful for iterating variable amount of properties.
//This function returns the property value (void**) and
//lib_handle: if not NULL
//prop_name: if not NULL
//(although could be used with any type of node)
//An int* cur_index must be provided so that this index is increased.
//In order to speed up searching the user. User can start searching from the get_props_hint_index()
//which is the index of the last searched property.
//If the returned value is NULL, means it couldn't find any more values
void** MP_next_prop_release(MP_args_p args, short in_out_id, void** lib_handle, char** prop_name, int* cur_index){
  mepinta_props* props = get_props(args,in_out_id);

  if (*cur_index < props->size){ //found a value
    log_debug_verbose("Getting value for '%s' at index=%d.\n",props->names[*cur_index],*cur_index);
    if(lib_handle != NULL){// We asume we have variable properties
      *lib_handle = props->handles[*cur_index];
    }
    if(prop_name != NULL){
      *prop_name = props->names[*cur_index];
    }
    //We change it for next property
    return props->values[(*cur_index)++];
  }
  else{ //Could not find the value
    log_debug("Couldn't find any more values. Returning NULL.\n");
    return NULL;
  }
}

//This function iterates over the properties searching for those properties
//with handles[cur_index] == lib_handle.
//(see "get_next_prop" function, for args explanation)
//This way we can search for properties of specific data type.
//cur_index will be increased to the index of the next property found of that type.
void** MP_next_prop_typed_release (MP_args_p args, short in_out_id,  const void* lib_handle, char** prop_name, int* cur_index){
  mepinta_props* props = get_props(args,in_out_id);

  for(;*cur_index< props->size ; ++(*cur_index)){
    if(props->handles[*cur_index] == lib_handle ){
      break;
    }
  }
  if (*cur_index < props->size){ //found a value
    log_debug_verbose("Getting value for '%s' at index=%d.\n",props->names[*cur_index],*cur_index);
    if(prop_name != NULL){
      *prop_name = props->names[*cur_index];
    }
    //We change it for later use
    return props->values[(*cur_index)++];
  }
  else{ //Could not find the value
    log_debug("Couldn't find any more values. Returning NULL.\n");
    return NULL;
  }
}

//TODO:check MP_memcpy_wrap status
//This functions replaces an old property value with a new one.
//It alsos frees previuos memory value.
//In case of using the void* as the data itself (a double fits on a void* on 64bit platforms)
//then there is no need to free memory. So delete_function == NULL
//In the case of providing a new pointer, then delete_function shouldn't be NULL
//and it will be used to delete previous pointer value.
//int MP_replace_prop_value(void** value_pp, void** new_value_p, int size,void* delete_function){
//  //The user knows what s/he is doing, no freeing necessary
//  if(delete_function == NULL){
//    if(size == sizeof(void*)){ //directly copying
//      log_debug_warning("You are using the data's pointer as data itself. No need to free memory.\n");
//      *value_pp = *new_value_p;
//    }
//    else if(size < sizeof(void*)){
//      //You are probably using void* as your data.
//      log_debug_warning("You are using the data's pointer as data itself. No need to free memory.\n");
//      MP_memcpy_wrap(value_pp, new_value_p, size);
//    }
//    else{ //Bigger
//      log_debug_warning("You are not using the data's pointer as data itself.\n"
//          "\tBut you don't want to free memory. So we copy over it. (you must know what you are doing) \n");
//      MP_memcpy_wrap(*value_pp, new_value_p, size);
//    }
//  }
//  else {
//    log_debug("Replacing property at %p with property at %p.\n",*value_pp,*new_value_p);
//    log_debug("Deleting previous value with data at %p\n",*value_pp);
//    MP_delete_t casted_delete_func = (MP_delete_t)delete_function;
//    if( casted_delete_func(*value_pp) == NULL){
//      *value_pp = *new_value_p;
//    }
//    else{
//      log_error("Could not delete previous property\n");
//      return EXIT_FAILURE;
//    }
//  }
//  return EXIT_SUCCESS;
//}

//int MP_replace_prop_release(MP_args_p args,const char* prop_name, void** new_value_p, int new_value_size,void* delete_function){
//  void** value_pp = MP_prop_byname_release(args,OUTPUT_PROPS,NULL,prop_name);
//
//  if(new_value_size > sizeof(void*) || delete_function == NULL){
//    log_debug("Replacing property '%s' passing 'by value'.\n",prop_name);
//    //Do the job
//    if(new_value_size == sizeof(void*)){ //directly passing value
//      *value_pp = *new_value_p;
//    }
//    else if(new_value_size < sizeof(void*) ){ //It's smaller, we don't want to copy garbage
//      //TODO: is this necessary? //Will that garbage ever be a problem?
//      MP_memcpy_wrap(value_pp, new_value_p, new_value_size);
//    }
//    else{ //Means we are copying the value pointed by the void** (dynamically allocated)
//        MP_memcpy_wrap(*value_pp, new_value_p, new_value_size);
//    }
//  }
//  else {
//    log_debug("Replacing property '%s' passing 'by reference'.\n",prop_name);
//    log_debug("Deleting previous value with data at %p\n",*value_pp);
//    MP_delete_t casted_delete_func = (MP_delete_t)delete_function;
//    if( casted_delete_func(*value_pp) == NULL){
//      *value_pp = *new_value_p;
//    }
//    else{
//      log_error("Could not delete previous property. Not replacing values.\n");
//      return EXIT_FAILURE;
//    }
//  }
//  return EXIT_SUCCESS;
//}

int MP_replace_value_release(MP_args_p args,const char* prop_name, void** new_value_p, int new_value_size){
  void** value_pp = MP_prop_byname_debug(args,OUTPUT_PROPS,NULL,prop_name);

  log_debug("Replacing property '%s' passing 'by value'.\n",prop_name);
  //Do the job
  if(new_value_size == sizeof(void*)){ //directly passing value
    *value_pp = *new_value_p;
  }
  else if(new_value_size < sizeof(void*) ){ //It's smaller, we don't want to copy garbage
    //TODO: is this necessary? //Will that garbage ever be a problem?
    MP_memcpy_wrap(value_pp, new_value_p, new_value_size);
  }
  else{ //Means we are copying the value pointed by the void** (dynamically allocated)
    //TODO: check the size of the data type before doing the nasty job
    MP_memcpy_wrap(*value_pp, new_value_p, new_value_size);
  }
  return EXIT_SUCCESS;
}

int MP_replace_reference_release(MP_args_p args,const char* prop_name, void** new_value_p, int new_value_size, void* delete_function){
  void* lib_handle;
  void** value_pp = MP_prop_byname_debug(args,OUTPUT_PROPS,&lib_handle,prop_name);

  log_debug("Replacing property at %p with property at %p.\n",*value_pp,*new_value_p);
  log_debug("Deleting previous value with data at %p\n",*value_pp);
  if(delete_function == NULL){
    delete_function = MP_data_type_function(lib_handle,"delete",NULL,FALSE);
    if(delete_function == NULL){
      log_error("Couldn't solve data type delete function. Not replacing "
                "'%s' property.\n",prop_name);
      log_warning("This could mean a memory leak since new value is not freed.\n");
      return EXIT_FAILURE;
    }
  }
  MP_delete_t casted_delete_func = (MP_delete_t)delete_function;
  if( casted_delete_func(*value_pp) == NULL){
    *value_pp = *new_value_p;
  }
  else{
    log_error("Could not delete previous property. Not replacing values.\n");
    log_warning("This could mean a memory leak since new value is not freed.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

//This version won't delete previous value. That why it is nasty
int MP_nasty_replace_reference_release(MP_args_p args, short in_out_id, const char* prop_name, void** new_value_p, int new_value_size){

  void* lib_handle;
  void** value_pp = MP_prop_byname_debug(args,in_out_id,&lib_handle,prop_name);
  if(value_pp == NULL){
    log_error("Output property '%s' doesn't exist. Not replacing it.\n",prop_name);
    return EXIT_FAILURE;
  }

  log_debug("Nasty replace of property at %p with property at %p.\n",*value_pp,*new_value_p);
  *value_pp = *new_value_p;
  return EXIT_SUCCESS;
}

//Mark a property as changed for filter_propagation nodes.
//This functions is called by the macro MARK_OUTPUT
int MP_set_changed_byname_release (MP_args_p args, short in_out_id, const char* prop_name){
  MP_prop_byname_release(args,in_out_id,NULL,prop_name);
  return MP_set_changed_byindex_release(args,in_out_id, mepinta_get_hint_index()-1);
}

//Mark a property as changed for filter_propagation nodes.
//This is useful when we just know the property index
int MP_set_changed_byindex_release(MP_args_p args, short in_out_id, int index){
  mepinta_props* props = get_props(args,in_out_id);

  if( index < props->size ){
    props->changed[index] = TRUE;
  }
  else{
    log_error("Index (%d) is bigger that output properties size. Doing nothing.\n", index, props->size);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

//Mark a property as changed for filter_propagation nodes.
//This functions is called by the macro MARK_OUTPUT
int MP_set_unchanged_byname_release (MP_args_p args, short in_out_id, const char* prop_name){
  MP_prop_byname_release(args,in_out_id,NULL,prop_name);
  return MP_set_changed_byindex_release(args,in_out_id, mepinta_get_hint_index()-1);
}

//Mark a property as changed for filter_propagation nodes.
//This is useful when we just know the property index
int MP_set_unchanged_byindex_release(MP_args_p args, short in_out_id, int index){
  mepinta_props* props = get_props(args,in_out_id);

  if( index < props->size ){
    props->changed[index] = FALSE;
  }
  else{
    log_error("Index (%d) is bigger that output properties size. Doing nothing.\n", index, props->size);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int MP_has_changed_release(MP_args_p args, short in_out_id, int index){
  mepinta_props* props = get_props(args,in_out_id);

  if( index < props->size ){
    return props->changed[index];
  }
  else{
    log_error("Index (%d) is bigger that output properties size(%d). Doing nothing.\n", index, props->size);
    return FALSE;
  }
}

//}Property getting and setting

//{ Functum
//Get args from a functum to modify values
  MP_args_p MP_get_functum_args_release(functum_st* functum){
    return (MP_args_p)functum->args;
  }

  //Get fuctum function (is this needed?)
  MP_processor_function_t MP_get_functum_function_release(functum_st* functum){
    return functum->function_ptr;
  }

  //Call a functum
  int MP_call_functum_release(functum_st* functum, MP_args* args){
    return functum->function_ptr(args);
  }
//} Functum
