/*
 * functum.h
 *
 *  Created on: Jun 21, 2012
 *      Author: jduo
 */

#ifndef FUNCTUM_H_
#define FUNCTUM_H_

#include <mepintasdk/sdk.h>

#define functum functum_st

//typedef functum_st functum;
//
//typedef functum_st MP_functum;

#ifdef __cplusplus
namespace mepinta{
  typedef functum_st functum;
}
#endif


CPP_EXTERN_START

//EXPORTED_SYMBOL void * MP_functum_new(void);
//EXPORTED_SYMBOL void * MP_functum_delete(void* functum_v);
//EXPORTED_SYMBOL void * MP_functum_copy(void* functum_v);
EXPORTED_SYMBOL size_t MP_functum_data_type_size(void);
EXPORTED_SYMBOL size_t MP_functum_mem_size(void* functum_v);

//EXPORTED_SYMBOL char * MP_functum_v_serialize_xml(void* functum_v);
//EXPORTED_SYMBOL void * MP_functum_v_deserialize_xml(void* functum_v);
//EXPORTED_SYMBOL void * MP_functum_v_serialize_buffer(void* functum_v);
//EXPORTED_SYMBOL void * MP_functum_v_deserialize_buffer(void* functum_v);

CPP_EXTERN_END

#endif /* FUNCTUM_T_H_ */
