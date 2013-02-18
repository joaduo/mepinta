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

#ifndef PROPS_CLIENT_H_
#define PROPS_CLIENT_H_

#include "config.h"
#include "types.h"
#include "commondef.h"

CPP_EXTERN_START

//TODO: rename this file to args_client.h?
//{ Args and properties' API
//TODO: Later add regex support when getting a property

  //{ Release version
    EXPORTED_SYMBOL int MP_declare_prop_release(  int dst_dtyp_size
                                                        , void** declared_value
                                                        , MP_args_p args
                                                        , short in_out_id
                                                        , const char* prop_name);
    EXPORTED_SYMBOL void** MP_prop_byname_release       (MP_args_p args, short in_out_id,       void** lib_handle, const char* prop_name);
    EXPORTED_SYMBOL void** MP_prop_byindex_release      (MP_args_p args, short in_out_id,       void** lib_handle,      char** prop_name, int  index);
    EXPORTED_SYMBOL void** MP_next_prop_release         (MP_args_p args, short in_out_id,       void** lib_handle,      char** prop_name, int* cur_index);
    EXPORTED_SYMBOL void** MP_next_prop_typed_release   (MP_args_p args, short in_out_id,  const void* lib_handle,      char** prop_name, int* cur_index);

    //EXPORTED_SYMBOL int MP_replace_prop_release(MP_args_p args,const char* prop_name, void** new_value_p, int new_value_size,void* delete_function);
    EXPORTED_SYMBOL int MP_replace_value_release          (MP_args_p args,const char* prop_name, void** new_value_p, int new_value_size);
    EXPORTED_SYMBOL int MP_replace_reference_release      (MP_args_p args,const char* prop_name, void** new_value_p, int new_value_size, void* delete_function);
    EXPORTED_SYMBOL int MP_nasty_replace_reference_release(MP_args_p args, short in_out_id, const char* prop_name, void** new_value_p, int new_value_size);

    EXPORTED_SYMBOL int MP_set_changed_byname_release (MP_args_p args, short in_out_id, const char* prop_name);
    EXPORTED_SYMBOL int MP_set_changed_byindex_release(MP_args_p args, short in_out_id, int index);
    EXPORTED_SYMBOL int MP_set_unchanged_byname_release (MP_args_p args, short in_out_id, const char* prop_name);
    EXPORTED_SYMBOL int MP_set_unchanged_byindex_release(MP_args_p args, short in_out_id, int index);
    EXPORTED_SYMBOL int MP_has_changed_release(MP_args_p args, short in_out_id, int index);

    EXPORTED_SYMBOL MP_args_p MP_get_functum_args_release(functum_st* functum);
    EXPORTED_SYMBOL MP_processor_function_t MP_get_functum_function_release(functum_st* functum);
    EXPORTED_SYMBOL int MP_call_functum_release(functum_st* functum, MP_args* args);
  //} Release version

  //{ Debug version
  //Get the value for a property with type checking to advice the developer.
    EXPORTED_SYMBOL int MP_declare_prop_debug( const char* dst_dtype_str
                                                        , int dst_dtyp_size
                                                        , void** declared_value
                                                        , MP_args_p args
                                                        , short in_out_id
                                                        , const char* prop_name);
    EXPORTED_SYMBOL void** MP_prop_byname_debug        (MP_args_p args, short in_out_id,       void** lib_handle, const char* prop_name);
    EXPORTED_SYMBOL void** MP_prop_byindex_debug       (MP_args_p args, short in_out_id,       void** lib_handle,      char** prop_name, int  index);
    EXPORTED_SYMBOL void** MP_next_prop_debug          (MP_args_p args, short in_out_id,       void** lib_handle,      char** prop_name, int* cur_index);
    EXPORTED_SYMBOL void** MP_next_prop_by_type_debug  (MP_args_p args, short in_out_id,  const void* lib_handle,      char** prop_name, int* cur_index);

    //EXPORTED_SYMBOL int MP_replace_prop_debug(MP_args_p args,const char* prop_name, void** new_value_p, int new_value_size,void* delete_function);
    EXPORTED_SYMBOL int MP_replace_value_debug          (MP_args_p args,const char* prop_name, void** new_value_p, int new_value_size);
    EXPORTED_SYMBOL int MP_replace_reference_debug      (MP_args_p args,const char* prop_name, void** new_value_p, int new_value_size, void* delete_function);
    EXPORTED_SYMBOL int MP_nasty_replace_reference_debug(MP_args_p args, short in_out_id, const char* prop_name, void** new_value_p, int new_value_size);

    EXPORTED_SYMBOL int MP_set_changed_byname_debug (MP_args_p args, short in_out_id, const char* prop_name);
    EXPORTED_SYMBOL int MP_set_changed_byindex_debug(MP_args_p args, short in_out_id, int index);
    EXPORTED_SYMBOL int MP_set_unchanged_byname_debug (MP_args_p args, short in_out_id, const char* prop_name);
    EXPORTED_SYMBOL int MP_set_unchanged_byindex_debug(MP_args_p args, short in_out_id, int index);
    EXPORTED_SYMBOL int MP_has_changed_debug(MP_args_p args, short in_out_id, int index);

    EXPORTED_SYMBOL void** MP_check_cast_debug(const char* dst_dtype_str, void** valuepp);
    EXPORTED_SYMBOL void MP_set_registered_args_debug(MP_args_p args);

    EXPORTED_SYMBOL MP_args_p MP_get_functum_args_debug(functum_st* functum);
    EXPORTED_SYMBOL MP_processor_function_t MP_get_functum_function_debug(functum_st* functum);
    EXPORTED_SYMBOL int MP_call_functum_debug(functum_st* functum, MP_args* args);
  //} Debug version

  //{ Common
    EXPORTED_SYMBOL mepinta_props* MP_get_props(MP_args_p args, short in_out_id);
    //EXPORTED_SYMBOL mepinta_props* get_props(MP_args_p args, short in_out_id);
    #define get_props(args,in_out_id) MP_get_props(args,in_out_id)
    EXPORTED_SYMBOL int MP_previous_prop_index(MP_args_p args);
    EXPORTED_SYMBOL int MP_last_prop_index(MP_args_p args);
    EXPORTED_SYMBOL void MP_set_hint_index(MP_args_p args,int index);

    EXPORTED_SYMBOL int  MP_props_size   (MP_args_p args, short in_out_id);
    EXPORTED_SYMBOL char**  MP_props_names  (MP_args_p args, short in_out_id);
    EXPORTED_SYMBOL void*** MP_props_values   (MP_args_p args, short in_out_id);
    EXPORTED_SYMBOL void**  MP_props_handles(MP_args_p args, short in_out_id);

    EXPORTED_SYMBOL const char* MP_data_type_name(const void* lib_handle);
    EXPORTED_SYMBOL const char* MP_full_data_type_name(const void* lib_handle);
    EXPORTED_SYMBOL void* MP_data_type_function(const void* lib_handle, const char* func_name, const char* dtype_name, short quiet );
    EXPORTED_SYMBOL void* MP_data_type_handle(MP_args_p args, short in_out_id, char* data_type_name);
  //}Common

//} Properties' API

CPP_EXTERN_END

//Aliases depending on the Build mode
#ifndef MEPINTA_DEBUG
  #define MP_declare_prop(args, in_out_id, prop_name) \
  MP_prop_byname_release (args, in_out_id, NULL, prop_name)
  #define MP_prop_byname(args,in_out_id,lib_handle,prop_name) \
  MP_prop_byname_release(args,in_out_id,lib_handle,prop_name)
  #define MP_prop_byindex(args,in_out_id,lib_handle,prop_name,index) \
  MP_prop_byindex_release(args,in_out_id,lib_handle,prop_name,index)
  #define MP_next_prop(args,in_out_id,lib_handle,prop_name,cur_index) \
  MP_next_prop_release(args,in_out_id,lib_handle,prop_name,cur_index)
  #define MP_next_prop_by_type(args,in_out_id,lib_handle,prop_name,cur_index)  \
  MP_next_prop_typed_release(args,in_out_id,lib_handle,prop_name,cur_index)
  #define MP_replace_prop(args,prop_name,new_value_p,new_value_size,delete_function)\
  MP_replace_prop_release(args,prop_name,new_value_p,new_value_size,delete_function)
  #define MP_set_changed_byname(args,in_out_id,prop_name)\
  MP_set_changed_byname_release(args,in_out_id,prop_name)
  #define MP_set_changed_byindex(args,in_out_id,index)\
  MP_set_changed_byindex_release(args,in_out_id,index)
  #define MP_set_unchanged_byname(args,in_out_id,prop_name)\
  MP_set_unchanged_byname_release(args,in_out_id,prop_name)
  #define MP_set_unchanged_byindex(args,in_out_id,index)\
  MP_set_unchanged_byindex_release(args,in_out_id,index)
  #define MP_has_changed(args,in_out_id,index)\
  MP_has_changed_release(args,in_out_id,index)
  #define MP_get_functum_args(functum) \
  MP_get_functum_args_debug(functum)
  #define MP_get_functum_function(functum)\
  MP_get_functum_function_debug(functum)
  #define MP_call_functum(functum,args)\
  MP_call_functum_debug(functum,args)
#else
  #define MP_declare_prop(dst_dtype_str, args, in_out_id, prop_name) \
    MP_declare_prop_debug(dst_dtype_str, args, in_out_id, prop_name)
  #define MP_prop_byname(args,in_out_id,lib_handle,prop_name) \
    MP_prop_byname_debug(args,in_out_id,lib_handle,prop_name)
  #define MP_prop_byindex(args,in_out_id,lib_handle,prop_name,index) \
    MP_prop_byindex_debug(args,in_out_id,lib_handle,prop_name,index)
  #define MP_next_prop(args,in_out_id,lib_handle,prop_name,cur_index) \
    MP_next_prop_debug(args,in_out_id,lib_handle,prop_name,cur_index)
  #define MP_next_prop_by_type(args,in_out_id,lib_handle,prop_name,cur_index)  \
    MP_next_prop_by_type_debug(args,in_out_id,lib_handle,prop_name,cur_index)
  #define MP_replace_prop(args,prop_name,new_value_p,new_value_size,delete_function)\
    MP_replace_prop_debug(args,prop_name,new_value_p,new_value_size,delete_function)
  #define MP_set_changed_byname(args,in_out_id,prop_name)\
    MP_set_changed_byname_debug(args,in_out_id,prop_name)
  #define MP_set_changed_byindex(args,in_out_id,index)\
    MP_set_changed_byindex_debug(args,in_out_id,index)
  #define MP_set_unchanged_byname(args,in_out_id,prop_name)\
    MP_set_unchanged_byname_debug(args,in_out_id,prop_name)
  #define MP_set_unchanged_byindex(args,in_out_id,index)\
    MP_set_unchanged_byindex_debug(args,in_out_id,index)
  #define MP_has_changed(args,in_out_id,index)\
    MP_has_changed_debug(args,in_out_id,index)
  #define MP_get_functum_args(functum) \
  MP_get_functum_args_debug(functum)
  #define MP_get_functum_function(functum)\
  MP_get_functum_function_debug(functum)
  #define MP_call_functum(functum,args)\
  MP_call_functum_debug(functum,args)
#endif

#endif /* PROPS_CLIENT_H_ */
