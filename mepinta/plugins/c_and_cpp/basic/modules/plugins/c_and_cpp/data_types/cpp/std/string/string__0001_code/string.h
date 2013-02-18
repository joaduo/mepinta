#ifndef K3DV1_COLOR_H_
#define K3DV1_COLOR_H_

#include <mepintasdk/config.h>
#include <mepintasdk/types.h>

#include <string>

CPP_EXTERN_START

EXPORTED_SYMBOL void * MP_cpp_std_string_new(void);
EXPORTED_SYMBOL void * MP_cpp_std_string_delete(void* color_v);
EXPORTED_SYMBOL void * MP_cpp_std_string_copy(void* color_v);
EXPORTED_SYMBOL size_t MP_cpp_std_string_data_type_size(void);
EXPORTED_SYMBOL size_t MP_cpp_std_string_mem_size(void* color_v);
EXPORTED_SYMBOL passing_t MP_cpp_std_string_variable_passing(void);

//EXPORTED_SYMBOL char * MP_cpp_std_string_serialize_xml(void* color_v);
//EXPORTED_SYMBOL void * MP_cpp_std_string_deserialize_xml(void* color_v);
//EXPORTED_SYMBOL void * MP_cpp_std_string_serialize_buffer(void* color_v);
//EXPORTED_SYMBOL void * MP_cpp_std_string_deserialize_buffer(void* color_v);

CPP_EXTERN_END

#endif /* K3DV1_COLOR_H_ */
