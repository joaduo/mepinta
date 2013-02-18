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
#include "color.h"

//DECLARE_MEMORY_MNGMNT_FUNCTIONS();

//This function is never published in the header, although it needs to be exported
extern "C" EXPORTED_SYMBOL
const char * MP_get_data_type_name(void){
  return _STR(k3d::color);
}

void * MP_k3dv1_color_new(void){
  return new k3d::color;
}

void * MP_k3dv1_color_delete(void* color_v){
  if(color_v != NULL){
    delete (k3d::color*)color_v;
  }
  return NULL; //Return NULL on success
}

void * MP_k3dv1_color_copy(void* color_v){
  k3d::color* new_color = new k3d::color;
  *new_color = *(k3d::color*)color_v;
  return new_color;
}

size_t MP_k3dv1_color_data_type_size(void){
  return sizeof(k3d::color);
}

size_t MP_k3dv1_color_mem_size(void* color_v){
  return MP_k3dv1_color_data_type_size();  //Don't know yet
}

passing_t MP_k3dv1_color_variable_passing(void){
  return by_reference;
}
