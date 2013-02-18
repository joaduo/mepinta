/*
 * K3DMesh_v1.h
 *
 *  Created on: Nov 18, 2011
 *      Author: jduo
 */

#ifndef K3DV1_MATRIX4_H_
#define K3DV1_MATRIX4_H_

#include <mepintasdk/config.h>
#include <mepintasdk/types.h>

#include <k3dsdk/algebra.h>

CPP_EXTERN_START

EXPORTED_SYMBOL void * MP_k3dv1_matrix4_new(void);
EXPORTED_SYMBOL void * MP_k3dv1_matrix4_delete(void* color_v);
EXPORTED_SYMBOL void * MP_k3dv1_matrix4_copy(void* color_v);
EXPORTED_SYMBOL size_t MP_k3dv1_matrix4_data_type_size(void);
EXPORTED_SYMBOL size_t MP_k3dv1_matrix4_mem_size(void* color_v);
EXPORTED_SYMBOL passing_t MP_k3dv1_matrix4_variable_passing(void);

//EXPORTED_SYMBOL char * MP_k3dv1_matrix4_serialize_xml(void* color_v);
//EXPORTED_SYMBOL void * MP_k3dv1_matrix4_deserialize_xml(void* color_v);
//EXPORTED_SYMBOL void * MP_k3dv1_matrix4_serialize_buffer(void* color_v);
//EXPORTED_SYMBOL void * MP_k3dv1_matrix4_deserialize_buffer(void* color_v);

CPP_EXTERN_END

#endif /* K3DV1_MATRIX4_H_ */
