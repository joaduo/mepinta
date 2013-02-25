/*
 * K3DMesh_v1.c
 *
 *  Created on: Nov 18, 2011
 *      Author: jduo
 */

#include <mepintasdk/sdk.h>
#include <mepintasdk/log.h>
#include "matrix4.h"

//DECLARE_MEMORY_MNGMNT_FUNCTIONS();

//This function is never published in the header, although it needs to be exported
extern "C" EXPORTED_SYMBOL
const char * MP_get_data_type_name(void){
  return _STR(k3d::matrix4);
}

void * MP_k3dv1_matrix4_new(void){
  return new k3d::matrix4;
}

void * MP_k3dv1_matrix4_delete(void* matrix_v){
  if(matrix_v != NULL){
    delete (k3d::matrix4*)matrix_v;
  }
  return NULL; //Return NULL on success
}

void * MP_k3dv1_matrix4_copy(void* matrix_v){
  k3d::matrix4* new_matrix = new k3d::matrix4();
  *new_matrix = *(k3d::matrix4*)matrix_v;
  return new_matrix;
}

size_t MP_k3dv1_matrix4_data_type_size(void){
  return sizeof(k3d::matrix4);
}

size_t MP_k3dv1_matrix4_mem_size(void* matrix_v){
  return MP_k3dv1_matrix4_data_type_size();  //Don't know yet
}

passing_t MP_k3dv1_matrix4_variable_passing(void){
  return by_reference;
}
