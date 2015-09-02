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
#include "memmngmt.h"
#include "config.h"
#include "args.h"
#include "props.h"

//{ mepinta_args
//TODO: better printing. Check malloc
mepinta_args* mepinta_args_new(int in_size, int out_size){
  mepinta_args* args = (mepinta_args*)MP_malloc_wrap(sizeof(mepinta_args));
  args->hint_index= 0;
  args->thread_id = 0;
  args->inputs  = mepinta_props_new(in_size);
  args->outputs = mepinta_props_new(out_size);
  //Variable properties (may vary name, type and order)
  args->custom_inputs  = mepinta_props_new(0);
  args->custom_outputs = mepinta_props_new(0);
  return args;
}

//TODO:delete
//Set the capacity a priori to avoid resizing memory too often
int mepinta_args_set_capacities(mepinta_args* args, int in_size, int out_size){
  mepinta_props_set_capacity(args->inputs, in_size);
  mepinta_props_set_capacity(args->outputs, out_size);
  return EXIT_SUCCESS;
}

int mepinta_args_set_context(mepinta_args* args, void* processor_context){
  args->processor_context = processor_context;
  return EXIT_SUCCESS;
}

//Set the capacity a priori to avoid resizing memory too often
int mepinta_args_set_variable_props_capacities(mepinta_args* args, int in_size, int out_size){
  mepinta_props_set_capacity(args->custom_inputs, in_size);
  mepinta_props_set_capacity(args->custom_outputs, out_size);
  return EXIT_SUCCESS;
}

//TODO: better printing. Check free
int mepinta_args_delete(mepinta_args* args){
  if(args != NULL){
    mepinta_props_delete(args->inputs);
    mepinta_props_delete(args->outputs);
    mepinta_props_delete(args->custom_inputs);
    mepinta_props_delete(args->custom_outputs);
    MP_free_wrap(args);
  }
  return EXIT_SUCCESS;
}

//Set the thread ID for when it's registered
int mepinta_args_set_thread_id(mepinta_args* args, int thread_id){
  args->thread_id = thread_id;
  return EXIT_SUCCESS;
}

//reset the size of args //TODO: delete this? Seems not useful
int mepinta_args_reset_sizes(mepinta_args* args){
  mepinta_props_clear(args->inputs);
  mepinta_props_clear(args->outputs);
  mepinta_props_clear(args->custom_inputs);
  mepinta_props_clear(args->custom_outputs);
  return EXIT_SUCCESS;
}
//} mepinta_args

//{ functum
//Allocate a new functum. The caller is responsible o the lifetime of the structure.
functum_st* functum_new(void* function_ptr, mepinta_args* args){
  functum_st* functum = (functum_st*)MP_malloc_wrap(sizeof(functum_st));
  functum->function_ptr = (MP_processor_function_t)function_ptr;
  functum->args = args;
  return functum;
}

//Delete a previously allocated functum structure
//args and function_ptr inside the functum should be deleted somewhere else
int functum_delete(functum_st* functum){
  MP_free_wrap(functum);
  return EXIT_SUCCESS;
}
//} functum
