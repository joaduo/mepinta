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
 * charp.c
 *
 *  Created on: Oct 31, 2011
 *      Author: jduo
 */

#include <string.h>
#include <mepintasdk/sdk.h>
#include "charp.h"

DECLARE_MEMORY_MNGMNT_FUNCTIONS(GARBAGE_COLLECTED);

//This function is never published in the .h, since it's called solving it's symbol from the handle
EXPORTED_SYMBOL char * MP_get_data_type_name(void){
  return _STR(char*);
}

EXPORTED_SYMBOL
const char * MP_get_data_type_namespace(void){
  return _STR(charp);
}

charp empty_string = "";

void * MP_charp_new(void){
	return empty_string;
}

void * MP_charp_delete(void* charp_v){
	if (charp_v != empty_string){
		MP_free(charp_v);
	}
	return NULL;
}

void * MP_charp_copy(void* charp_v){
	if(charp_v != empty_string){
		charp new_charp_v = MP_malloc(strlen(charp_v));
		strcpy(new_charp_v,charp_v);
		return new_charp_v;
	}
	else{
		return empty_string;
	}
}

size_t MP_charp_data_type_size(void){
	return sizeof(charp);
}

size_t MP_charp_mem_size(void* charp_v){
	return strlen(charp_v);
}

