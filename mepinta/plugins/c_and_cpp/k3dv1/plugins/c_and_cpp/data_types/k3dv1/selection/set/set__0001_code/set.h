/*
 * K3DMesh_v1.h
 *
 *  Created on: Nov 18, 2011
 *      Author: jduo
 */

#ifndef K3DV1_MESHSELECTION_H_
#define K3DV1_MESHSELECTION_H_

#include <mepintasdk/config.h>
#include <mepintasdk/types.h>
#include <k3dsdk/selection.h>

CPP_EXTERN_START

EXPORTED_SYMBOL void * MP_k3dv1_selection_set_new(void);
EXPORTED_SYMBOL void * MP_k3dv1_selection_set_delete(void* mesh_selection_v);
EXPORTED_SYMBOL void * MP_k3dv1_selection_set_copy(void* mesh_selection_v);
EXPORTED_SYMBOL size_t MP_k3dv1_selection_set_data_type_size(void);
EXPORTED_SYMBOL size_t MP_k3dv1_selection_set_mem_size(void* mesh_selection_v);
EXPORTED_SYMBOL passing_t MP_k3dv1_selection_set_variable_passing(void);

//EXPORTED_SYMBOL char * MP_k3dv1_selection_set_serialize_xml(void* mesh_selection_v);
//EXPORTED_SYMBOL void * MP_k3dv1_selection_set_deserialize_xml(void* mesh_selection_v);
//EXPORTED_SYMBOL void * MP_k3dv1_selection_set_serialize_buffer(void* mesh_selection_v);
//EXPORTED_SYMBOL void * MP_k3dv1_selection_set_deserialize_buffer(void* mesh_selection_v);

CPP_EXTERN_END

#endif /* K3DV1_MESHSELECTION_H_ */
