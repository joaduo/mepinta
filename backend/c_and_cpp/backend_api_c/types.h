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

#ifndef TYPES_H_
#define TYPES_H_

#include <stddef.h>
#include <stdint.h>
#include "config.h"

//{ Memory Management Functions
typedef void* (*malloc_t)(size_t);
typedef void* (*calloc_t)(size_t,size_t);
typedef void  (*free_t)(void*);
typedef void* (*realloc_t)(void*,size_t);
typedef void* (*memmove_t)(void*,const void*,size_t);
typedef void* (*memcpy_t)(void*,const void*,size_t);

typedef enum {by_value,by_reference,by_unknown} passing_t;

typedef int (*MP_processor_function_t)(void *);
typedef void* (*MP_delete_t)(void *);
typedef char* (*MP_get_data_type_name_t)(void);
typedef size_t (*MP_mem_size_t)(void*);
typedef passing_t (*MP_variable_passing_t)(void);

//{ args aliases for ISOLATION checking
  #ifdef MEPINTA_DEBUG_ARGS_ISOLATION
    //Make sure args data is never directly accessed, but through the data API
    typedef void  mepinta_args;
    typedef void  functum_st;
    //TODO: delete MP_args_p
  #else
    //TODO: fix this mess of consts
    #if 0
      typedef int const prop_id_t;
      typedef char const ** const prop_name_t;
      typedef void ** const prop_value_t;
      typedef void ** const prop_handle_t;
    #else
      typedef int  prop_id_t;
      typedef char * prop_name_t;
      typedef void ** prop_value_t;
      typedef void * prop_handle_t;
      typedef uint8_t prop_changed_t;
    #endif

    //Mepinta processor (in/out) properties struct
    typedef struct mepinta_props{
      int size;        //Amount of properties in this container
      int capacity;    //Capacity of this container
      prop_id_t* ids;
      prop_name_t* names;    //Name of each property
      prop_value_t* values;    //Pointing to the data pointers (which could be data themselves)
      prop_handle_t* handles;  //Pointing to the data type library handles
      prop_changed_t* changed;
    }mepinta_props;

    //Struct passed as argument to any processor function
    typedef struct mepinta_args{
      //int version;     //We use this if we are going to change this structure in the future
      //TODO: later use as thread id?
      int thread_id;   //To get the log_level value from the outside world
      int hint_index;
      //TODO:Change this to structs, since this are not of variable size
      mepinta_props* inputs;           // inputs properties of the processor
      mepinta_props* custom_inputs;  // inputs properties of the processor (may change type, name, order)
      mepinta_props* outputs;          // outputs properties of the processor
      mepinta_props* custom_outputs; // outputs properties of the processor (may change type, name, order)
      //this processor context
      void* processor_context;
    }mepinta_args;

    //TODO: take this out of here? use functum_t?
    //Struct representing a functum
    typedef struct functum_st{
      MP_processor_function_t function_ptr; // function pointer
      mepinta_args* args;
    }functum_st;
  #endif
  typedef mepinta_args* MP_args_p; //TODO: remove
  typedef mepinta_args  MP_args;
//} args aliases for ISOLATION checking


#endif /* TYPES_H_ */
