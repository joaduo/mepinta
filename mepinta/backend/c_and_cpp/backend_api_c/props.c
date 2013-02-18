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

#include "sdkdef.h"
#include "log.h"
#include "memmngmt.h"
#include "props.h"

//TODO: create a health check function to see that all prop_id are in ascendent order

//Create a new properties array structure
//Stores:
//properties' ids, properties names, pointers to properties' values
//properties data type library handles
//size= current amount of property in the array
//capacity= maximum amount of properties able to store (before having to resize)
mepinta_props* mepinta_props_new(int capacity){
  //TODO:print debug messages?
  mepinta_props* props = (mepinta_props*) MP_malloc_wrap(sizeof(mepinta_props));
  props->size = 0;
  if(capacity != 0){
    capacity += MEPINTA_PROPS_MEMORY_CHUNK; //TODO: review the necessity?
  }
  props->ids = (prop_id_t*) MP_malloc_wrap(capacity*sizeof(prop_id_t));
  props->names =(prop_name_t*) MP_malloc_wrap(capacity*sizeof(prop_name_t));
  props->values = (prop_value_t*) MP_malloc_wrap(capacity*sizeof(prop_value_t));
  props->handles = (prop_handle_t*) MP_malloc_wrap(capacity*sizeof(prop_handle_t));
  props->changed = (prop_changed_t*) MP_malloc_wrap(capacity);
  props->capacity = capacity;
  return props;
}

//Set values for a property, whether it existed before or is new.
//Increases the size of the array if the given index
//is equal or bigger than the current size. (means is a new property was added)
//Setting: id,name,value,handle,
int mepinta_props_set(mepinta_props* props, int index, prop_id_t prop_id, prop_name_t name, prop_value_t value, prop_handle_t handle, uint8_t changed){
  log_debug("Setting property with index %d in props at %p.\n",index,props);
  log_debug("prop_id %d, prop_name %s, prop_value %p\n", prop_id, name, value);
  mepinta_props_set_capacity(props, index+1);
  if(index < props->capacity){
    //TODO: fix const
    props->ids[index] = prop_id;
    props->names[index] = name;
    props->values[index] = value;
    props->handles[index] = handle;
    props->changed[index] = changed;
    if(index+1 > (props->size)){
      props->size =index +1;
    }
    return EXIT_SUCCESS;
  }
  else{
    log_error("Couldn't append any more property to the props at %p",props);
    return EXIT_FAILURE;
  }
}

#define RESIZE(type,var_name,capacity)\
    var_name = (type*) MP_realloc_wrap(var_name,capacity*sizeof(type))

//Change capacity of props if it's too small
int mepinta_props_set_capacity(mepinta_props* props, int capacity){
  //TODO: print debug messages?
  if(capacity > props->capacity){
    //We need to grow the memory, and add some extra to avoid too many
    //mallocs in the future
    capacity += MEPINTA_PROPS_MEMORY_CHUNK;
    RESIZE(prop_id_t,props->ids,capacity);
    RESIZE(prop_name_t,props->names,capacity);
    RESIZE(prop_value_t,props->values,capacity);
    RESIZE(prop_handle_t,props->handles,capacity);
    RESIZE(prop_changed_t,props->changed,capacity);
    props->capacity = capacity;
  }
  return EXIT_SUCCESS;
}

int mepinta_props_clear(mepinta_props* props){
  log_debug("Clearing props at %p.\n",props);
  props->size = 0;
  return EXIT_SUCCESS;
}

//TODO: check free status, print debug messages
int mepinta_props_delete(mepinta_props* props){
  if(props != NULL){
    MP_free_wrap(props->ids);
    MP_free_wrap(props->names);
    MP_free_wrap(props->values);
    MP_free_wrap(props->handles);
    MP_free_wrap(props->changed);
    MP_free_wrap(props);
  }
  return EXIT_SUCCESS;
}
