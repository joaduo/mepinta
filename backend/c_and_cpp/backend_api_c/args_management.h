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

#ifndef ARGS_MANAGEMENT_H_
#define ARGS_MANAGEMENT_H_

#include "log.h"
#include "sdkdef.h"
#include "props_client.h"
#include "props.h"
#include "args.h"

#define GET_FUNCTUM_STRUCT \
    return functum_new(func_ptr, (mepinta_args*) args)

#define RESET_SIZES \
    mepinta_args_reset_sizes((mepinta_args*)args)

#define DELETE_ARGS \
    return mepinta_args_delete((mepinta_args*)args)

#define SET_THREAD_ID \
    return mepinta_args_set_thread_id((mepinta_args*)args, thread_id)

#ifdef MEPINTA_DEBUG
  #define SET_CAPACITY\
    mepinta_props* props= MP_get_props((mepinta_args*)args,in_out_id); \
    return mepinta_props_set_capacity(props, props_size);

  #define CREATE_ARGS \
    mepinta_args* args = (mepinta_args*)mepinta_args_new(in_size,out_size); \
    return (void*)args

  #define APPEND_PROP \
    mepinta_props* props= MP_get_props((mepinta_args*)args,in_out_id); \
    ASSERT_DEBUG_RETURN(props!=NULL,EXIT_FAILURE); \
    return mepinta_props_set(props,index,prop_id,(prop_name_t)prop->name->unit.c_str(),&prop_real->getValuePtr()->value,data_type->lib_handle,0)

  #define SET_PROP_CHANGED \
    return MP_set_changed_byindex((mepinta_args*)args,in_out_id,index)

  #define SET_PROP_UNCHANGED \
    return MP_set_unchanged_byindex((mepinta_args*)args,in_out_id,index)


  #define BUILD_CHANGED_SET \
    mepinta_props* props = get_props((mepinta_args*)args,in_out_id); \
    for(int index = 0; index < props->size; ++index){ \
      if(props->changed[index]){ \
        changed->add(props->ids[index]); \
      } \
    }

  //TODO: make it data independent using API?
  //  int size = MP_props_size((mepinta_args*)args, OUTPUT_PROPS); \
  //  for(int index = 0; index < size; ++index){ \
  //    if(MP_has_changed(args,OUTPUT_PROPS,index)){ \
  //      //TODO: sill access props->ids \
  //      changed->add(props->ids[index]); \
  //    } \
  //  }


#else
//TODO: do not register args (review)
  #define SET_CAPACITY\
    return mepinta_args_set_capacities((mepinta_args*) args,in_size,out_size)

  #define CREATE_ARGS \
      return (void*)mepinta_args_new(in_size,out_size)

  #define APPEND_PROP \
    return mepinta_props_set(MP_get_props(args,in_out_id),index,prop_id,(prop_name_t)prop->name->unit.c_str(),&prop_real->getValuePtr()->value,data_type->lib_handle,0)

  #define SET_PROP_CHANGED \
    get_props(args,in_out_id)->changed[index] = TRUE; \
    return EXIT_SUCCESS

  #define SET_PROP_UNCHANGED \
    get_props(args,in_out_id)->changed[index] = FALSE; \
    return EXIT_SUCCESS

  //TODO: make it data independent using API
  #define BUILD_CHANGED_SET \
    mepinta_props* props = get_props(args,OUTPUT_PROPS); \
    for(int index = 0; index < props->size; ++index){ \
      if(props->changed[index]){ \
        changed->add(props->ids[index]); \
      } \
    }

#endif


#endif /* ARGS_MANAGEMENT_H_ */
