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

/*
 * GC_charp.c
 *
 *  Created on: Oct 31, 2011
 *      Author: jduo
 */

#include <string.h>
#include <mepintasdk/sdk.h>
#include "charp.h"

DECLARE_MEMORY_MNGMNT_FUNCTIONS(GARBAGE_COLLECTED);

//This function is never published in the .h, since it's called solving it's symbol from the handle
EXPORTED_SYMBOL
char * MP_get_data_type_name(void){
  return _STR(char);
}

GC_charp zero_size_charp = NULL;

void * MP_GC_charp_new(void){
	if (zero_size_charp == NULL){
		zero_size_charp = MP_malloc(sizeof(char));
		zero_size_charp[0] = '\0';
	}
	return zero_size_charp;
}

void * MP_GC_charp_delete(void* gc_charp_v){
	if (gc_charp_v != zero_size_charp){
		MP_free(gc_charp_v);
	}
	return NULL;
}

void * MP_GC_charp_copy(void* gc_charp_v){
	if(gc_charp_v != zero_size_charp){
		GC_charp new_charp_v = MP_malloc(strlen(gc_charp_v));
		strcpy(new_charp_v,gc_charp_v);
		return new_charp_v;
	}
	else{
		return zero_size_charp;
	}
}

size_t MP_GC_charp_data_type_size(void){
	return sizeof(GC_charp);
}

size_t MP_GC_charp_mem_size(void* gc_charp_v){
	return strlen(gc_charp_v);
}
