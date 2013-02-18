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
 * double.h
 *
 *  Created on: Oct 1, 2011
 *      Author: jduo
 */

#ifndef DOUBLE_H_
#define DOUBLE_H_

#include <mepintasdk/config.h>
#include <mepintasdk/types.h>

#ifdef __cplusplus
extern "C" {
#endif

EXPORTED_SYMBOL void * MP_double_new(void);
EXPORTED_SYMBOL void * MP_double_delete(void* double_v);
EXPORTED_SYMBOL void * MP_double_copy(void* double_v);
EXPORTED_SYMBOL size_t MP_double_data_type_size(void);
EXPORTED_SYMBOL size_t MP_double_mem_size(void* double_v);
EXPORTED_SYMBOL passing_t MP_double_variable_passing(void);

//EXPORTED_SYMBOL char * MP_double_serialize_xml(void* double_v);
//EXPORTED_SYMBOL void * MP_double_deserialize_xml(void* double_v);
//EXPORTED_SYMBOL void * MP_double_serialize_buffer(void* double_v);
//EXPORTED_SYMBOL void * MP_double_deserialize_buffer(void* double_v);

#ifdef __cplusplus
}
#endif

#endif /* DOUBLE_H_ */
