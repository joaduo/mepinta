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

#ifndef K3DV1_MESH_H_
#define K3DV1_MESH_H_

#include <mepintasdk/config.h>
#include <mepintasdk/types.h>
#include <k3dsdk/mesh.h>

CPP_EXTERN_START
  EXPORTED_SYMBOL void * MP_k3dv1_mesh_new(void);
  EXPORTED_SYMBOL void * MP_k3dv1_mesh_delete(void* mesh_v);
  EXPORTED_SYMBOL void * MP_k3dv1_mesh_copy(void* mesh_v);
  //EXPORTED_SYMBOL void * MP_k3dv1_mesh_copy_to(void* into_mesh,void* from_mesh);
  EXPORTED_SYMBOL size_t MP_k3dv1_mesh_data_type_size(void);
  EXPORTED_SYMBOL size_t MP_k3dv1_mesh_mem_size(void* mesh_v);
  EXPORTED_SYMBOL passing_t MP_k3dv1_mesh_variable_passing(void);

  //EXPORTED_SYMBOL char * MP_k3dv1_mesh_serialize_xml(void* mesh_v);
  //EXPORTED_SYMBOL void * MP_k3dv1_mesh_deserialize_xml(void* mesh_v);
  //EXPORTED_SYMBOL void * MP_k3dv1_mesh_serialize_buffer(void* mesh_v);
  //EXPORTED_SYMBOL void * MP_k3dv1_mesh_deserialize_buffer(void* mesh_v);
CPP_EXTERN_END

#endif /* K3DV1_MESH_H_ */
