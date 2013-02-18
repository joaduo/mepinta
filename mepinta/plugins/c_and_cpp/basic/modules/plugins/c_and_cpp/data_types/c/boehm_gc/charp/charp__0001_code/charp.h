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
 * GC_charp.h
 *
 *  Created on: Oct 31, 2011
 *      Author: jduo
 */

#ifndef GC_CHARP_H_
#define GC_CHARP_H_

#include <mepintasdk/config.h>

//TODO: rename GC_charp to boehm_gc_charp

typedef char* GC_charp;

CPP_EXTERN_START

EXPORTED_SYMBOL void * MP_GC_charp_new(void);
EXPORTED_SYMBOL void * MP_GC_charp_delete(void* gc_charp_v);
EXPORTED_SYMBOL void * MP_GC_charp_v_copy(void* gc_charp_v);
EXPORTED_SYMBOL size_t MP_GC_charp_v_data_type_size(void);
EXPORTED_SYMBOL size_t MP_GC_charp_v_mem_size(void* gc_charp_v);

//EXPORTED_SYMBOL char * MP_GC_charp_v_serialize_xml(void* gc_charp_v);
//EXPORTED_SYMBOL void * MP_GC_charp_v_deserialize_xml(void* gc_charp_v);
//EXPORTED_SYMBOL void * MP_GC_charp_v_serialize_buffer(void* gc_charp_v);
//EXPORTED_SYMBOL void * MP_GC_charp_v_deserialize_buffer(void* gc_charp_v);

CPP_EXTERN_END


#endif /* GC_CHARP_H_ */
