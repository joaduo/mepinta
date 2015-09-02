/*
 * K3DMesh_v1.h
 *
 *  Created on: Nov 18, 2011
 *      Author: jduo
 */

#ifndef K3DV1_MATERIAL_H_
#define K3DV1_MATERIAL_H_

#include <mepintasdk/config.h>
#include <mepintasdk/types.h>
#include <k3dsdk/imaterial.h>

namespace imaterial_dummy {
  class DummyMaterial:
    public k3d::imaterial
  {

  };
}

CPP_EXTERN_START

EXPORTED_SYMBOL void * MP_k3dv1_imaterial_new(void);
EXPORTED_SYMBOL void * MP_k3dv1_imaterial_delete(void* material_v);
EXPORTED_SYMBOL void * MP_k3dv1_imaterial_copy(void* material_v);
EXPORTED_SYMBOL size_t MP_k3dv1_imaterial_data_type_size(void);
EXPORTED_SYMBOL size_t MP_k3dv1_imaterial_mem_size(void* material_v);
EXPORTED_SYMBOL passing_t MP_k3dv1_imaterial_variable_passing(void);

//EXPORTED_SYMBOL char * MP_k3dv1_imaterial_serialize_xml(void* material_v);
//EXPORTED_SYMBOL void * MP_k3dv1_imaterial_deserialize_xml(void* material_v);
//EXPORTED_SYMBOL void * MP_k3dv1_imaterial_serialize_buffer(void* material_v);
//EXPORTED_SYMBOL void * MP_k3dv1_imaterial_deserialize_buffer(void* material_v);

CPP_EXTERN_END

#endif /* K3DV1_MATERIAL_H_ */
