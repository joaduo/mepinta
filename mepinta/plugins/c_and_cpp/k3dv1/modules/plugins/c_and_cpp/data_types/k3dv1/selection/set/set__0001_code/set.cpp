/*
 * K3DMesh_v1.c
 *
 *  Created on: Nov 18, 2011
 *      Author: jduo
 */

#include <mepintasdk/sdk.h>
#include <mepintasdk/log.h>
#include "set.h"

//DECLARE_MEMORY_MNGMNT_FUNCTIONS();

//This function is never published in the header, although it needs to be exported
extern "C" EXPORTED_SYMBOL
const char * MP_get_data_type_name(void){
  return _STR(k3d::selection::set);
}

void * MP_k3dv1_selection_set_new(void){
    return new k3d::selection::set();
}

void * MP_k3dv1_selection_set_delete(void* mesh_selection_v){
  if(mesh_selection_v != NULL){
    delete (k3d::selection::set*)mesh_selection_v;
  }
  return NULL; //Return NULL on success
}

void * MP_k3dv1_selection_set_copy(void* mesh_selection_v){
  k3d::selection::set* new_mesh_selection = new k3d::selection::set();
  *new_mesh_selection = *(k3d::selection::set*)mesh_selection_v;
  return new_mesh_selection;
}

size_t MP_k3dv1_selection_set_data_type_size(void){
  return sizeof(k3d::selection::set);
}

size_t MP_k3dv1_selection_set_mem_size(void* mesh_selection_v){
  return 0;  //Don't know yet
}

passing_t MP_k3dv1_selection_set_variable_passing(void){
  return by_reference;
}
