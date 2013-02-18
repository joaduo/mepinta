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

#include <string.h>
#include <stdio.h>
#include "memmngmt.h"
#include "sdkdef.h"
#include "log.h"
#include "solve_symbol.h"
#include "args.h"
#include "props_client.h"

passing_t MP_get_variable_passing_type(const void* lib_handle,const char * src_dtype_name);

//TODO: review if inlining this function is useful
//Cast args from MP_args_p (a void*) -> mepinta_args (a struct)
//make proper checkings before doing so
mepinta_props* MP_get_props(MP_args_p args, short in_out_id){
  if(in_out_id == INPUT_PROPS){
    return ((mepinta_args*)args)->inputs;
  }
  else if (in_out_id == OUTPUT_PROPS){
    return ((mepinta_args*)args)->outputs;
  }
  else if (in_out_id == CUSTOM_INPUT_PROPS){
    return ((mepinta_args*)args)->custom_inputs;
  }
  else if (in_out_id == CUSTOM_OUTPUT_PROPS){
    return ((mepinta_args*)args)->custom_outputs;
  }
  else{
   log_error("Incorrect Input/Output id, returning NULL.\n");
   return NULL;
  }
}

//When searching a property we use the hint_index to accelerates the search
//If the user declares property alphabetically then each variable
//declaration will only require one string comparison
int hint_index = 0;
//To get the hint index for searching through the props
//This function is not published (just used internally)
//mepinta_get_las_prop_index replaces external use
int mepinta_get_hint_index(MP_args_p args){
  return ((mepinta_args*)args)->hint_index;
}

//This is useful for resetting the hint index in case we have just
//entered the processor. Or in case we know what index our property
//should have, and then speed up searching.
inline void MP_set_hint_index(MP_args_p args,int index){
  ((mepinta_args*)args)->hint_index = index;
}

//To get the index for searching certain property
int MP_last_prop_index(MP_args_p args){
  log_error("Don't use MP_last_prop_index it's deprecated. Use MP_previous_prop_index instead.\n");
  return MP_previous_prop_index(args);
}

//To get the index of the latest property declared/consulted/searched
int MP_previous_prop_index(MP_args_p args){
  return mepinta_get_hint_index(args)-1;
}

//Get the data type name for certain library handle
//Data type should have implemented GET_DATA_TYPE_NAME_SYMBOL
const char* MP_data_type_name(const void* lib_handle){
  MP_get_data_type_name_t dtype_name_func_ptr = mepinta_solve_symbol(lib_handle,GET_DATA_TYPE_NAME_SYMBOL);
  ASSERT_RETURN(dtype_name_func_ptr!=NULL,NULL);
  return dtype_name_func_ptr();
}

////Get the data type name for certain library handle
////Data type should have implemented GET_DATA_TYPE_NAME_SYMBOL
////Appends a * if is passed by reference
const char* MP_full_data_type_name(const void* lib_handle){
  return MP_data_type_name(lib_handle);
}

//const char* MP_full_data_type_name(const void* lib_handle){
//  MP_get_data_type_name_t dtype_name_func_ptr = mepinta_solve_symbol(lib_handle,GET_DATA_TYPE_NAME_SYMBOL);
//  ASSERT_RETURN(dtype_name_func_ptr!=NULL,NULL);
//  const char* dtype_name = dtype_name_func_ptr();
//  if(MP_get_variable_passing_type(lib_handle,dtype_name) == by_reference){
//    const char * fmt_str = "%s*";
//    char * dtype_name_ptr = MP_malloc_wrap_gc(strlen(fmt_str)+strlen(dtype_name));
//    sprintf(dtype_name_ptr,fmt_str,dtype_name);
//    return dtype_name_ptr;
//  }
//  else{
//    return dtype_name;
//  }
//}

//Get variable passing enum for a data_type library_handle
passing_t MP_get_variable_passing_type(const void* lib_handle,const char * src_dtype_name){
  ASSERT_RETURN(lib_handle != NULL && src_dtype_name != NULL, by_unknown);

  MP_variable_passing_t MP_variable_passing = MP_data_type_function(lib_handle,"variable_passing",src_dtype_name,TRUE);

  if(MP_variable_passing != NULL){
    log_debug("Getting data type passing from library.\n");
    return MP_variable_passing();
  }
  else{
    log_debug("No variable passing function found for data types '%s'. "
                      "Assuming the data type is passed 'by reference'.\n",src_dtype_name);
    return by_reference;
  }
}

//Get the function pointer for a data type lib
//If the dtype_name != NULL, then the name is not solved again
//If quiet == TRUE, then it won't print any error when solving the symbol
void* MP_data_type_function(const void* lib_handle, const char* func_name, const char* dtype_name, short quiet ){
  ASSERT_RETURN(func_name != NULL, NULL);
  //It not provided, get the data type name
  if(dtype_name == NULL){
    dtype_name = MP_data_type_name(lib_handle);
    if(dtype_name == NULL){
      log_error("Couldn't find data type name for lib handle at %p.\n",lib_handle);
      return NULL;
    }
  }
  void* func_ptr;
  const char * fmt_str = "MP_%s_%s";
  char * lib_symbol = MP_malloc_wrap_gc(strlen(fmt_str)+strlen(dtype_name)+strlen(func_name));
  sprintf(lib_symbol,fmt_str,dtype_name,func_name);
  if(quiet == TRUE){
    func_ptr = mepinta_solve_symbol_quiet(lib_handle,lib_symbol);
  }
  else{
    func_ptr = mepinta_solve_symbol(lib_handle,lib_symbol);
  }
  return func_ptr;
}

//Get the handle for certain data type.
//If the returned handle is null, means that data type is not on the
//properties. Or that the GET_DATA_TYPE_NAME_SYMBOL function was not implemented
void* MP_data_type_handle(MP_args_p args, short in_out_id, char* data_type_name){
  void* handle = NULL;
  if(in_out_id == INPUT_OUTPUT_PROPS){//We are checking on inputs and outputs
    handle = MP_data_type_handle(args,INPUT_PROPS,data_type_name); //First on inputs
    if(handle == NULL){ //If we were not successful we check on outputs
      handle = MP_data_type_handle(args,OUTPUT_PROPS,data_type_name);
    }
  }
  else{
    mepinta_props* props = get_props(args,in_out_id);
    ASSERT_RETURN(props!=NULL,NULL);
    int i;
    for(i=0; i < props->size; ++i){
      if(strcmp(data_type_name,MP_data_type_name(props->handles[i])) == 0){
        handle = props->handles[i];
        break;
      }
    }
  }
  return handle;
}

//Get the amount of properties
int  MP_props_size   (MP_args_p args, short in_out_id){
  mepinta_props* props = get_props(args,in_out_id);
  ASSERT_RETURN(props!=NULL,0);
  return props->size;
}

//Get the array of property names
char**  MP_props_names  (MP_args_p args, short in_out_id){
  mepinta_props* props = get_props(args,in_out_id);
  ASSERT_RETURN(props!=NULL,NULL);
  return props->names;
}

//Get the array of property values (void**)
void*** MP_props_values   (MP_args_p args, short in_out_id){
  mepinta_props* props = get_props(args,in_out_id);
  ASSERT_RETURN(props!=NULL,NULL);
  return props->values;
}

//Get the array of properties lib handles
void**  MP_props_handles(MP_args_p args, short in_out_id){
  mepinta_props* props = get_props(args,in_out_id);
  ASSERT_RETURN(props!=NULL,NULL);
  return props->handles;
}
