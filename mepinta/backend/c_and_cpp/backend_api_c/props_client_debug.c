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
 * props_client_debug.c
 *
 *  Created on: Nov 10, 2011
 *      Author: jduo
 */

#include <stdio.h>
#include <string.h>

#include <mepintasdk/cpp/type_checking/demangleTypeName.h>

#include "sdkdef.h"
#include "log.h"
#include "memmngmt.h"
#include "args.h"
#include "solve_symbol.h"
#include "props_client.h"
#include "types.h"

//{ Inline not public functions

  inline passing_t MP_get_variable_passing_type(const void* lib_handle,const char * src_dtype_name);

  inline int mepinta_get_hint_index(MP_args_p args);

  //do the type checking from the data types names
  //Symbol not exported
  inline int mepinta_type_checking(const char* dst,const char* src, passing_t passing){
    if( strcmp(dst,src) == 0 ){
      log_debug("Types match src: %s and dst: %s. Passing %d.\n",src,dst,passing);
      return EXIT_SUCCESS;
    }
    //Check if it is a mangled name
    const char* dst_demangled = MP_demangleTypeName(dst);
    if(strcmp(dst_demangled,src) ==0){
      log_debug("Types match src: %s and dst: %s. Passing %d.\n",src,dst_demangled,passing);
      return EXIT_SUCCESS;
    }
    log_debug("Types don't match src: %s and dst: %s. Passing %d.\n",src,dst,passing);
    return EXIT_FAILURE;
  }

  //Helper function for debugging mode (on release mode there is no checking)
  //Symbol not exported
  inline void* get_lib_handle(void** handles, int index){
    log_debug_verbose("Getting handle at index %d from handles at %p.\n",index,handles);
    if(handles != NULL){
      return handles[index];
    }
    else{
      log_error("Handles are NULL.\n");
      return NULL;
    }
  }

//} Inline not public functions

//Cast args from MP_args_p (a void*) -> mepinta_args (a struct)
//make proper checkings before doing so
mepinta_props* get_props_debug(MP_args_p args, short in_out_id){
  if (args == NULL){
    log_error("args=NULL. Arguments should be provided.\n");
    return NULL;
  }

  return MP_get_props(args,in_out_id);
}

//TODO: should accept file name and line number to make more meaningful the printings
//Get the value for a declared property with type checking to advice the developer.
int MP_declare_prop_debug(  const char* dst_dtype_str
                                    , int dst_dtyp_size
                                    , void** declared_value
                                    , MP_args_p args
                                    , short in_out_id
                                    , const char* prop_name){

  void* lib_handle;
  void** valuepp = MP_prop_byname_debug(args,in_out_id,&lib_handle,prop_name);
  if(valuepp == NULL){
    log_error("Couldn't find property '%s'. Returning.\n", prop_name);
    return EXIT_FAILURE;
  }

  const char* src_dtype_str = MP_data_type_name(lib_handle);
  passing_t variable_passing = MP_get_variable_passing_type(lib_handle,src_dtype_str);
  if (variable_passing == by_unknown){
    log_warning("Couldn't resolve variable passing method preferred by the data type. "
                "Unable to do corresponding checking.\n");
    return EXIT_FAILURE;
  }

  if(src_dtype_str == NULL ){
    log_debug_warning("Couldn't get data type name. Maybe this module is a "
                      "release version but compiled with MEPINTA_DEBUG defined.\n");
    log_error("Couldn't make all the checking in debug mode. Increase debug level for more details.\n");
    return EXIT_FAILURE;
  }
  else {
    if( mepinta_type_checking(dst_dtype_str, src_dtype_str, variable_passing) != EXIT_SUCCESS){
      log_warning("Casting from '%s' to '%s' for property '%s'. \n", src_dtype_str, dst_dtype_str, prop_name);
      //return EXIT_FAILURE; //TODO: need to resolve aliases
    }
  }

  log_debug("Passing variables based on their sizes.\n");
  if(dst_dtyp_size == sizeof(void*)) {
    //by value or by reference depends on the data type size
    log_debug("Passing 'by value' or 'by reference'. Can't distinguish.\n");
    if(variable_passing == by_value){
      log_debug_verbose(
        "'%s' data type expects passing 'by value'. Make sure "
        "'%s' is NOT a pointer.\n", src_dtype_str,dst_dtype_str);
    }
    else if(variable_passing == by_reference){
      log_debug_verbose(
        "'%s' data type expects passing 'by reference'. Make sure "
        "'%s' is a pointer.\n",src_dtype_str,dst_dtype_str);
    }
    *declared_value = *valuepp;
  }
  else if(dst_dtyp_size < sizeof(void*)){
    if(variable_passing == by_reference){
      log_warning("Passing '%s' 'by value' when it's intended to be "
                  "'by reference'.\n",prop_name);
    }
    else if(variable_passing == by_value){
      log_debug("Passing property '%s' 'by value' as expected.\n",prop_name);
    }
    MP_memcpy_wrap(declared_value, valuepp,dst_dtyp_size);
  }
  else{
    if(variable_passing == by_reference){
      log_warning("For property '%s' passing 'by value' when it's intended to be "
                  "'by reference'.\n",prop_name);
    }
    else if(variable_passing == by_value){
      log_debug("Passing property '%s' 'by value' as expected.\n",prop_name);
    }
    MP_memcpy_wrap(declared_value,*valuepp,dst_dtyp_size);
  }

  return EXIT_SUCCESS;
}

//Get the property value (void**) and optionally "lib_handle" (if not NULL)
//from args given its name.
//Will make use of global variable "hint_index". This can or cannot be helpful.
//Make sure of re/setting its value using RESET_PROPS_HINT_INDEX macro
//or previous "set_props_hint_index(int index)" function.
void** MP_prop_byname_debug(MP_args_p args, short in_out_id, void** lib_handle, const char* prop_name){
  ASSERT_RETURN(prop_name!=NULL,NULL);

  mepinta_props* props = get_props_debug(args,in_out_id);
  ASSERT_RETURN(props!=NULL,NULL);

  int i;
  //Search for the prop name
  for(i = mepinta_get_hint_index(args); i< props->size ; ++i){
    log_debug("Props Size: %d prop_name: %s index: %d.\n",props->size,props->names[i],i);
    if(strcmp(props->names[i],prop_name) == 0){
      break;
    }
  }

  if (i < props->size){ //found a value
    log_debug("Found value for '%s' at %p.\n",prop_name,props->values[i]);
    if(lib_handle != NULL){// We need to set lib_handle
      *lib_handle = get_lib_handle(props->handles,i);
    }
    MP_set_hint_index(args,i + 1); //We change it for later hints
    return props->values[i];
  }
  else if(mepinta_get_hint_index(args) != 0){ //Couldn't find the value but didn't start search from the beginning
    log_debug("Current hint index with value %d was not a useful hint. Restarting a full search.\n", mepinta_get_hint_index(args));
    MP_set_hint_index(args,0);
    return MP_prop_byname_debug(args,in_out_id,lib_handle,prop_name);
  }
  else{ //Could not find the value
    log_debug("Couldn't find '%s' in args at %p. Returning NULL.\n",prop_name,props);
    return NULL;
  }
}

//Similar to "get_next_prop" function, but the index is not increased
void** MP_prop_byindex_debug(MP_args_p args, short in_out_id, void** lib_handle, char** prop_name, int index){
  mepinta_props* props = get_props_debug(args,in_out_id);
  ASSERT_RETURN(props != NULL,NULL);

  if (index < props->size){ //found a value
    log_debug_verbose("Getting value for '%s' at index=%d.\n",props->names[index],index);
    if(lib_handle != NULL){// We asume we have variable properties
      log_debug_verbose("Assuming variable properties. Getting data type library handle.\n");
      if(props->handles != NULL){
        *lib_handle = props->handles[index];
      }
      else{
        log_error("Assuming this processor has variable properties. Seems it was not declared so.\n");
        *lib_handle = NULL;
      }
    }
    if(prop_name != NULL){
      *prop_name = props->names[index];
    }
    return props->values[index];
  }
  else{ //Could not find the value
    log_debug("Couldn't find any more values. Returning NULL.\n");
    return NULL;
  }
}

//This function is useful for iterating variable amount of properties.
//This function returns the property value (void**) and
//lib_handle: if not NULL
//prop_name: if not NULL
//An int* must be provided so that this index is increased.
//In order to speed up searching the user. User can start searching from the get_props_hint_index()
//which is the index of the last searched property.
//If the returned value is NULL, means it couldn't find any more values
void** MP_next_prop_debug(MP_args_p args, short in_out_id, void** lib_handle, char** prop_name, int* cur_index){
  mepinta_props* props = get_props_debug(args,in_out_id);
  ASSERT_RETURN(props != NULL,NULL);

  if (*cur_index < props->size){ //found a value
    log_debug_verbose("Getting value for '%s' at index=%d.\n",props->names[*cur_index],*cur_index);
    if(lib_handle != NULL){// We asume we have variable properties
      if(props->handles != NULL){
        *lib_handle = props->handles[*cur_index];
        log_debug("Getting data type library handle at %p.\n",*lib_handle);
      }
      else{
        log_error("No handles for args.\n");
        *lib_handle = NULL;
      }
    }
    if(prop_name != NULL){
      *prop_name = props->names[*cur_index];
    }
    //We change it for next property
    void* value = props->values[*cur_index];
    log_debug("Getting value for %s at %p.\n",props->names[*cur_index], value);
    //increment counter
    ++*cur_index;
    return value;
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
void** MP_next_prop_by_type_debug (MP_args_p args, short in_out_id,  const void* lib_handle, char** prop_name, int* cur_index){
  MP_set_registered_args_debug(args); //TODO: correct this
  mepinta_props* props = get_props_debug(args,in_out_id);
  //ASSERT_RETURN(props!=NULL && prop_name != NULL && lib_handle != NULL && props->handles != NULL ,NULL); //TODO: delete this line? prop_name can be NULL
  ASSERT_RETURN(props!=NULL && lib_handle != NULL && props->handles != NULL ,NULL);

  for(;*cur_index< props->size ; ++(*cur_index)){
    if(props->handles[*cur_index] == lib_handle ){
      break;
    }
  }
  if (*cur_index < props->size){ //found a value
    log_debug_verbose("Getting value for '%s' at index=%d. Pointer value %p.\n",props->names[*cur_index],*cur_index,props->values[*cur_index]);
    if(prop_name != NULL){
      *prop_name = props->names[*cur_index];
    }
    //We change it for later use
    ++(*cur_index);
    return props->values[(*cur_index)-1];
  }
  else{ //Could not find the value
    log_debug("Couldn't find any more values. Returning NULL.\n");
    return NULL;
  }
}

//int MP_replace_prop_debug(MP_args_p args,const char* prop_name, void** new_value_p, int new_value_size,void* delete_function){
//
//  void* lib_handle;
//  void** value_pp = MP_prop_byname_debug(args,OUTPUT_PROPS,&lib_handle,prop_name);
//  if(value_pp == NULL){
//    log_error("Output property '%s' doesn't exist. Not replacing it.\n",prop_name);
//    log_warning("This could mean a memory leak since new value is not freed.(if it had to)\n");
//    return EXIT_FAILURE;
//  }
//
//  //Get the data type name for warning messages
//  const char * src_dtype_name = MP_data_type_name(lib_handle);
//
//  passing_t variable_passing = MP_get_variable_passing_type(lib_handle,src_dtype_name);
//
//  if(new_value_size > sizeof(void*) || delete_function == NULL){
//    //No memory freeing necessary
//    if(variable_passing == by_reference){
//      log_warning("Replacing property '%s' passing 'by value'. When the '%s' data type intends to be passed 'by reference'. "
//                  "(remember this could lead to a 'shallow' copy in some cases)\n",prop_name,src_dtype_name);
//      log_debug_warning("Use 'REPLACE_OUTPUT_REFERENCE' macro to replace this property.\n");
//    }
//    else{
//      log_debug("Replacing property '%s' passing 'by value' as the '%s' data type expects.\n",prop_name,src_dtype_name);
//      log_debug_verbose("Remember freeing any memory you allocated in the function for property '%s'.(if any)\n",prop_name);
//      if(delete_function != NULL){
//        log_debug_warning("There is no need to supply a delete function for property '%s'.\n",prop_name);
//      }
//    }
//    //Do the job
//    if(new_value_size == sizeof(void*)){ //directly passing value
//      *value_pp = *new_value_p;
//    }
//    else if(new_value_size < sizeof(void*) ){ //It's smaller, we don't want to copy garbage
//      //TODO: is this necessary? //Will that garbage ever be a problem?
//      MP_memcpy_wrap(value_pp, new_value_p, new_value_size);
//    }
//    else{ //Means we are copying the value pointed by the void** (dynamically allocated)
//      //TODO: check the size of the data type before doing the nasty job
//        MP_memcpy_wrap(*value_pp, new_value_p, new_value_size);
//    }
//  }
//  else {
//    if(variable_passing == by_value){
//      log_warning("Replacing property '%s' passing 'by reference'. "
//                  "When the '%s' data type intends to be passed 'by value'.\n"
//                  ,prop_name,src_dtype_name);
//      log_warning("Use 'REPLACE_OUTPUT_VALUE' macro to replace this property.\n");
//    }
//    else{
//      log_debug("Replacing property '%s' passing 'by reference' as the '%s' data type expects.\n",prop_name,src_dtype_name);
//      log_debug_verbose("For property '%s' remember creating the new value with "
//                        "the data type API: MP_%s_new().\n",prop_name,src_dtype_name);
//    }
//    log_debug("Replacing property at %p with property at %p.\n",*value_pp,*new_value_p);
//    log_debug("Deleting previous value with data at %p\n",*value_pp);
//    MP_delete_t casted_delete_func = (MP_delete_t)delete_function;
//    if( casted_delete_func(*value_pp) == NULL){
//      *value_pp = *new_value_p;
//    }
//    else{
//      log_error("Could not delete previous property. Not replacing values.\n");
//      log_warning("This could mean a memory leak since new value is not freed.\n");
//      return EXIT_FAILURE;
//    }
//  }
//  return EXIT_SUCCESS;
//}

int MP_replace_value_debug(MP_args_p args,const char* prop_name, void** new_value_p, int new_value_size){
  void* lib_handle;
  void** value_pp = MP_prop_byname_debug(args,OUTPUT_PROPS,&lib_handle,prop_name);
  if(value_pp == NULL){
    log_error("Output property '%s' doesn't exist. Not replacing it.\n",prop_name);
    log_warning("This could mean a memory leak since new value is not freed.(if it had to)\n");
    return EXIT_FAILURE;
  }

  //Get the data type name for warning messages
  const char * src_dtype_name = MP_data_type_name(lib_handle);

  passing_t variable_passing = MP_get_variable_passing_type(lib_handle,src_dtype_name);

  if(variable_passing == by_reference){
    log_warning("Trying to replace property '%s' passing 'by value'. When the '%s' data type intends to be passed 'by reference'. "
                "Not replacing property.\n",prop_name,src_dtype_name);
    log_debug_warning("Use 'REPLACE_OUTPUT_REFERENCE' macro to replace this property.\n");
    return EXIT_FAILURE;
  }
  else if (variable_passing == by_value){
    log_debug("Replacing property '%s' passing 'by value' as the '%s' data type expects.\n",prop_name,src_dtype_name);
    log_debug_verbose("Remember freeing any memory you allocated in the function for property '%s'.(if any)\n",prop_name);
  }
  else{
    log_warning("Replacing property '%s' passing 'by value'. Although '%s' passing type is unknown.\n",prop_name,src_dtype_name);
  }

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

int MP_replace_reference_debug(MP_args_p args,const char* prop_name, void** new_value_p, int new_value_size, void* delete_function){

  void* lib_handle;
  void** value_pp = MP_prop_byname_debug(args,OUTPUT_PROPS,&lib_handle,prop_name);
  if(value_pp == NULL){
    log_error("Output property '%s' doesn't exist. Not replacing it.\n",prop_name);
    log_warning("This could mean a memory leak since new value is not freed.(if it had to)\n");
    return EXIT_FAILURE;
  }

  //Get the data type name for warning messages
  const char * src_dtype_name = MP_data_type_name(lib_handle);
  passing_t variable_passing = MP_get_variable_passing_type(lib_handle,src_dtype_name);

  if(variable_passing == by_reference){
    log_debug("Replacing property '%s' passing 'by reference' as the '%s' data type expects.\n",prop_name,src_dtype_name);
    log_debug_verbose("For property '%s' remember creating the new value with "
                      "the data type API: MP_%s_new().\n",prop_name,src_dtype_name);
  }
  else if(variable_passing == by_value){
    log_warning("Replacing property '%s' passing 'by reference'. "
                "When the '%s' data type intends to be passed 'by value'. Not replacing it.\n"
                ,prop_name,src_dtype_name);
    log_debug_warning("Instead use 'REPLACE_OUTPUT_VALUE' macro to replace this property.\n");
    return EXIT_FAILURE;
  }
  else{
    log_warning("Replacing property '%s' passing 'by reference'. Although '%s' passing type is unknown.\n",prop_name,src_dtype_name);
  }

  if(new_value_size > sizeof(void*)){
    log_error("You are trying to pass a value by reference, but the data type "
              "provided is bigger than a pointer. Not replacing it.\n");
    return EXIT_FAILURE;
  }

  log_debug("Replacing property at %p with property at %p.\n",*value_pp,*new_value_p);
  log_debug("Deleting previous value with data at %p\n",*value_pp);

  void* delete_func_solved = MP_data_type_function(lib_handle,"delete",src_dtype_name,FALSE);
  if(delete_function == NULL &&  delete_func_solved == NULL){
    log_error("Couldn't solve data type delete function "
              "and 'delete_function' was not provided either.\n"
              "Not replacing '%s' property.\n",prop_name);
    log_warning("This could mean a memory leak since new value is not freed.\n");
    return EXIT_FAILURE;
  }
  else if(delete_function != NULL && delete_function != delete_func_solved ){
    log_warning("For property '%s' provided 'delete_function' differs from data type delete "
                "function. Continuing but you should fix this.\n",prop_name);
    log_warning("This could lead into a crash or memory leak.\n");
  }
  else if(delete_function == NULL){
    log_debug("For property '%s' 'delete_function' was not provided, "
              "using solved one instead.\n",prop_name);
    delete_function = delete_func_solved;
  }
  else{
    log_debug("For property '%s' using 'delete_function' provided.\n",prop_name);
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
int MP_nasty_replace_reference_debug(MP_args_p args, short in_out_id, const char* prop_name, void** new_value_p, int new_value_size){

  void* lib_handle;
  void** value_pp = MP_prop_byname_debug(args,in_out_id,&lib_handle,prop_name);
  if(value_pp == NULL){
    log_error("Output property '%s' doesn't exist. Not replacing it.\n",prop_name);
    return EXIT_FAILURE;
  }

  //Get the data type name for warning messages
  const char * src_dtype_name = MP_data_type_name(lib_handle);
  passing_t variable_passing = MP_get_variable_passing_type(lib_handle,src_dtype_name);

  if(variable_passing == by_reference){
    log_debug("Replacing property '%s' passing 'by reference' as the '%s' data type expects.\n",prop_name,src_dtype_name);
    log_debug_verbose("For property '%s' remember creating the new value with "
                      "the data type API: MP_%s_new().\n",prop_name,src_dtype_name);
  }
  else if(variable_passing == by_value){
    log_warning("Replacing property '%s' passing 'by reference'. "
                "When the '%s' data type intends to be passed 'by value'. Not replacing it.\n"
                ,prop_name,src_dtype_name);
    log_debug_warning("Instead use 'REPLACE_OUTPUT_VALUE' macro to replace this property.\n");
    return EXIT_FAILURE;
  }
  else{
    log_warning("Replacing property '%s' passing 'by reference'. Although '%s' passing type is unknown.\n",prop_name,src_dtype_name);
  }

  if(new_value_size > sizeof(void*) ){
    log_error("You are trying to pass a value by reference, but the data type "
              "provided is bigger than a pointer. Not replacing it.\n");
    return EXIT_FAILURE;
  }

  log_debug("Nasty replace of property at %p with property at %p.\n",*value_pp,*new_value_p);
  *value_pp = *new_value_p;
  return EXIT_SUCCESS;
}

//{ Change Unchanged Marking

  //Mark a property as changed for filter_propagation nodes.
  //This functions is called by the macro MARK_OUTPUT
  int MP_set_changed_byname_debug (MP_args_p args, short in_out_id, const char* prop_name){
    if(MP_prop_byname_debug(args,in_out_id,NULL,prop_name) != NULL){
      return MP_set_changed_byindex_debug(args,in_out_id,mepinta_get_hint_index(args) - 1);
    }
    else{
      log_error("Property %s doesn't exist.\n",prop_name);
      return EXIT_FAILURE;
    }
  }

  //Mark a property as changed for filter_propagation nodes.
  //This is useful when we already know the property index
  int MP_set_changed_byindex_debug(MP_args_p args, short in_out_id, int index){
    mepinta_props* props = get_props_debug(args,in_out_id);
    ASSERT_RETURN(props!=NULL,EXIT_FAILURE);

    if( index < props->size ){
      props->changed[index] = TRUE;
    }
    else{
      log_error("Index (%d) is bigger that output properties size(%d). Doing nothing.\n", index, props->size);
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }

  //Mark a property as changed for filter_propagation nodes.
  //This functions is called by the macro MARK_OUTPUT
  int MP_set_unchanged_byname_debug (MP_args_p args, short in_out_id, const char* prop_name){
    if(MP_prop_byname_debug(args,in_out_id,NULL,prop_name) != NULL){
      return MP_set_changed_byindex_debug(args,in_out_id,mepinta_get_hint_index(args) - 1);
    }
    else{
      log_error("Property %s doesn't exist.\n",prop_name);
      return EXIT_FAILURE;
    }
  }

  //Mark a property as changed for filter_propagation nodes.
  //This is useful when we already know the property index
  int MP_set_unchanged_byindex_debug(MP_args_p args, short in_out_id, int index){

    mepinta_props* props = get_props_debug(args,in_out_id);
    ASSERT_RETURN(props!=NULL,EXIT_FAILURE);
    log_debug("Setting unchanged value for props at '%p' with index %d.\n",props,index);

    if( index < props->size ){
      props->changed[index] = FALSE;
    }
    else{
      log_error("Index (%d) is bigger that output properties size(%d). Doing nothing.\n", index, props->size);
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }

  //Get if the property has changed for a specific index
  int MP_has_changed_debug(MP_args_p args, short in_out_id, int index){
    mepinta_props* props = get_props_debug(args,in_out_id);
    ASSERT_RETURN(props!=NULL,EXIT_FAILURE);

    if( index < props->size ){
      return props->changed[index];
    }
    else{
      log_error("Index (%d) is bigger that output properties size(%d). Doing nothing.\n", index, props->size);
      return FALSE;
    }
  }

//} Change Unchanged Marking

//{ Value Casting Checking
  int MP_index_from_valuepp(mepinta_props* props,void** valuepp){
    int index;
    for( index= 0; index < props->size; ++index){
      if(props->values[index] == valuepp){
        break;
      }
    }
    return index;
  }

  MP_args_p registered_args = NULL;
  void MP_set_registered_args_debug(MP_args_p args){
    //TODO: register by thread_id
    registered_args = args;
  }

  inline MP_args_p mepinta_get_registered_args_debug(void){
    return registered_args;
  }

  void** MP_check_cast_debug(const char* dst_dtype_str, void** valuepp){
    short in_out_id = INPUT_PROPS;
    MP_args_p args = mepinta_get_registered_args_debug();
    mepinta_props* props = get_props_debug(args,in_out_id);
    ASSERT_RETURN(props!=NULL,valuepp);
    ASSERT_RETURN(args!=NULL,valuepp);
    int index = MP_index_from_valuepp(props,valuepp);
    if (index == props->size){
      in_out_id = OUTPUT_PROPS;
      props = get_props_debug(args,in_out_id);
      ASSERT_RETURN(props!=NULL,valuepp);
      index = MP_index_from_valuepp(props,valuepp);
      if (index == props->size){
        log_error("Couldn't found a property for valuepp at %p. Casting not checked.\n",valuepp);
        return valuepp;
      }
    }
    log_debug("Found index %d for valuepp at %p.\n",index,valuepp);
    char * prop_name;
    void* lib_handle;
    MP_prop_byindex_debug(args,in_out_id,&lib_handle,&prop_name,index);
    const char* src_dtype_str = MP_data_type_name(lib_handle);
    passing_t variable_passing = MP_get_variable_passing_type(lib_handle,src_dtype_str);
    if( mepinta_type_checking(dst_dtype_str, src_dtype_str, variable_passing) != EXIT_SUCCESS){
      log_debug_warning("Casting '%s' to '%s'. ",src_dtype_str,dst_dtype_str);
      log_debug_warning("Property '%s' may be of the incorrect data type.\n",prop_name);
      log_debug_warning("Declare '%s' as '%s' to suppress this warning.",prop_name,src_dtype_str);
      log_debug_warning(" (remember to include '%s' headers if necessary)\n",src_dtype_str);
    }
    else{
      log_debug("Casting correctly '%s' to '%s'.\n",prop_name,dst_dtype_str);
    }
    return valuepp;
  }

//} Value Casting Checking


//{ Functum
  //Get args from a functum to modify values
  MP_args_p MP_get_functum_args_debug(functum_st* functum){
    return (MP_args_p)functum->args;
  }

  //Get fuctum function (is this needed?)
  MP_processor_function_t MP_get_functum_function_debug(functum_st* functum){
    return functum->function_ptr;
  }

  //Call a functum
  int MP_call_functum_debug(functum_st* functum, MP_args* args){
    ASSERT_RETURN( functum->function_ptr != NULL, EXIT_FAILURE);
    if(args == NULL){
      args = functum->args;
    }
    log_debug("Calling functum at %p with args at %p \n",functum->function_ptr,args);
    return functum->function_ptr(functum->args);
  }
//} Functum
