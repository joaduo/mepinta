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
 * int.h
 *
 *  Created on: Nov 3, 2011
 *      Author: jduo
 */

#ifndef INT_H_
#define INT_H_

#include <mepintasdk/config.h>
#include <mepintasdk/types.h>

#ifdef __cplusplus
extern "C" {
#endif

EXPORTED_SYMBOL void * MP_int_new(void);
EXPORTED_SYMBOL void * MP_int_delete(void* int_v);
EXPORTED_SYMBOL void * MP_int_copy(void* int_v);
EXPORTED_SYMBOL size_t MP_int_data_type_size(void);
EXPORTED_SYMBOL size_t MP_int_mem_size(void* int_v);
EXPORTED_SYMBOL passing_t MP_int_variable_passing(void);

//EXPORTED_SYMBOL char * MP_int_serialize_xml(void* int_v);
//EXPORTED_SYMBOL void * MP_int_deserialize_xml(void* int_v);
//EXPORTED_SYMBOL void * MP_int_serialize_buffer(void* int_v);
//EXPORTED_SYMBOL void * MP_int_deserialize_buffer(void* int_v);

#ifdef __cplusplus
}
#endif

#endif /* INT_H_ */
