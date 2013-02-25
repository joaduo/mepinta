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
 * uint.h
 *
 *  Created on: Nov 4, 2011
 *      Author: jduo
 */

#ifndef UINT_H_
#define UINT_H_

#include <mepintasdk/config.h>
#include <mepintasdk/types.h>

typedef unsigned int uint;

#ifdef __cplusplus
extern "C" {
#endif

EXPORTED_SYMBOL void * MP_uint_new(void);
EXPORTED_SYMBOL void * MP_uint_delete(void* uint_v);
EXPORTED_SYMBOL void * MP_uint_copy(void* uint_v);
EXPORTED_SYMBOL size_t MP_uint_data_type_size(void);
EXPORTED_SYMBOL size_t MP_uint_mem_size(void* uint_v);
EXPORTED_SYMBOL passing_t MP_uint_variable_passing(void);

//EXPORTED_SYMBOL char * MP_uint_serialize_xml(void* uint_v);
//EXPORTED_SYMBOL void * MP_uint_deserialize_xml(void* uint_v);
//EXPORTED_SYMBOL void * MP_uint_serialize_buffer(void* uint_v);
//EXPORTED_SYMBOL void * MP_uint_deserialize_buffer(void* uint_v);

#ifdef __cplusplus
}
#endif

#endif /* UINT_H_ */
