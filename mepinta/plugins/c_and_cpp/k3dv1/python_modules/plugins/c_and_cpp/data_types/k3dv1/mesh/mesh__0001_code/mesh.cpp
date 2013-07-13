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

#include <mepintasdk/sdk.h>
#include <mepintasdk/log.h>
#include <mepintasdk/cpp/type_checking/demangleTypeName.h>
#include "mesh.h"

//DECLARE_MEMORY_MNGMNT_FUNCTIONS();

char* data_type_name=NULL;

//This function is never published in the header, although it needs to be exported
extern "C" EXPORTED_SYMBOL
const char * MP_get_data_type_name(void){
  if(data_type_name == NULL)
    data_type_name = MP_demangleTypeName(typeid(k3d::mesh*).name());
  return data_type_name;
}

extern "C" EXPORTED_SYMBOL
const char * MP_get_data_type_namespace(void){
  return _STR(k3dv1_mesh);
}

void * MP_k3dv1_mesh_new(void){
  k3d::mesh* mesh = new k3d::mesh();
  //TODO: review this hack (to avoid unset pipeline_data)
  mesh->points.create();
  mesh->point_selection.create();
  return mesh;
}

void * MP_k3dv1_mesh_delete(void* mesh_v){
  if(mesh_v != NULL){
    delete (k3d::mesh*)mesh_v;
  }
  return NULL; //Return NULL on success
}

void * MP_k3dv1_mesh_copy(void* mesh_v){
  k3d::mesh* new_mesh = new k3d::mesh();
  *new_mesh = *(k3d::mesh*)mesh_v;
  return (void*)new_mesh;
}

//Unnecessary, since k3d uses shared pointer caching system
//void * MP_k3dv1_mesh_copy_to(void* into_mesh,void* from_mesh){
//  *(k3d::mesh*)into_mesh = *(k3d::mesh*)from_mesh;
//  return NULL;
//}

size_t MP_k3dv1_mesh_data_type_size(void){
  return sizeof(k3d::mesh);
}

size_t MP_k3dv1_mesh_mem_size(void* mesh_v){
  return 0;  //Don't know yet
}

passing_t MP_k3dv1_mesh_variable_passing(void){
  return by_reference;
}
