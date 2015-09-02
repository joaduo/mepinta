/*
 * cpp_comon_type.h
 *
 *  Created on: Aug 3, 2012
 *      Author: jduo
 */

#ifndef CPP_COMON_TYPE_H_
#define CPP_COMON_TYPE_H_

#define COMMON_DATA_TYPE_PROTOTYPES(c_namespace) \
  CPP_EXTERN_START \
    EXPORTED_SYMBOL void * MP_##c_namespace##_new(void); \
    EXPORTED_SYMBOL void * MP_##c_namespace##_delete(void* color_v); \
    EXPORTED_SYMBOL void * MP_##c_namespace##_copy(void* color_v); \
    EXPORTED_SYMBOL size_t MP_##c_namespace##_data_type_size(void); \
    EXPORTED_SYMBOL size_t MP_##c_namespace##_mem_size(void* color_v); \
    EXPORTED_SYMBOL passing_t MP_##c_namespace##_variable_passing(void); \
  CPP_EXTERN_END \
  //
//TODO
//EXPORTED_SYMBOL char * MP_##c_namespace##_serialize_xml(void* color_v);
//EXPORTED_SYMBOL void * MP_##c_namespace##_deserialize_xml(void* color_v);
//EXPORTED_SYMBOL void * MP_##c_namespace##_serialize_buffer(void* color_v);
//EXPORTED_SYMBOL void * MP_##c_namespace##_deserialize_buffer(void* color_v);

#define COMMON_DATA_TYPE_API(data_type, c_namespace) \
/* DECLARE_MEMORY_MNGMNT_FUNCTIONS(); */ \
/* This function is never published in the header, although it needs to be exported */ \
  CPP_EXTERN_START \
    EXPORTED_SYMBOL \
    const char * MP_get_data_type_name(void){ \
      return _STR(data_type); \
    } \
     \
    void * MP_##c_namespace##_new(void){ \
      return new data_type; \
    } \
  CPP_EXTERN_END \
   \
  void * MP_##c_namespace##_delete(void* color_v){ \
    if(color_v != NULL){ \
      delete (data_type*)color_v; \
    } \
    return NULL; \
  } \
   \
  void * MP_##c_namespace##_copy(void* color_v){ \
    data_type* new_color = new data_type; \
    *new_color = *(data_type*)color_v; \
    return new_color; \
  } \
   \
  size_t MP_##c_namespace##_data_type_size(void){ \
    return sizeof(data_type); \
  } \
   \
  size_t MP_##c_namespace##_mem_size(void* color_v){ \
    return MP_##c_namespace##_data_type_size(); \
  } \
   \
  passing_t MP_##c_namespace##_variable_passing(void){ \
    return by_reference; \
  } \
  //



#endif /* CPP_COMON_TYPE_H_ */
