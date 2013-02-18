/*
 * K3DMesh_v1.c
 *
 *  Created on: Nov 18, 2011
 *      Author: jduo
 */

#include <mepintasdk/sdk.h>
#include <mepintasdk/log.h>
#include "imaterial.h"

//DECLARE_MEMORY_MNGMNT_FUNCTIONS();

//This function is never published in the header, although it needs to be exported
extern "C" EXPORTED_SYMBOL
const char * MP_get_data_type_name(void){
  return _STR(k3dv1::imaterial*);
}

void * MP_k3dv1_imaterial_new(void){
  return new imaterial_dummy::DummyMaterial;
}

void * MP_k3dv1_imaterial_delete(void* material_v){
  if(material_v != NULL){
    log_error("Deleting a material! Casting it to imaterial_dummy::DummyMaterial.\n");
    log_error("You shouldn't delete a material.\n");
    delete (imaterial_dummy::DummyMaterial*)material_v;
  }
  return NULL; //Return NULL on success
}

//TODO: check memcpy
void * MP_k3dv1_imaterial_copy(void* material_v){
  return MP_k3dv1_imaterial_new();
}

size_t MP_k3dv1_imaterial_data_type_size(void){
  return sizeof(k3d::imaterial);
}

size_t MP_k3dv1_imaterial_mem_size(void* material_v){
  return 0;  //Don't know yet
}

passing_t MP_k3dv1_imaterial_variable_passing(void){
  return by_reference;
}
