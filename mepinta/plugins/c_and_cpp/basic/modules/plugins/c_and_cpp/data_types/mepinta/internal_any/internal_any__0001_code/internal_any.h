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
 * internal_any.h
 *
 *  Created on: Nov 3, 2011
 *      Author: jduo
 */

#ifndef INTERNAL_ANY_H_
#define INTERNAL_ANY_H_

#include <mepintasdk/config.h>
#include <mepintasdk/types.h>

typedef struct{
  void* data;
  MP_delete_t delete_function;
} internal_any;

typedef internal_any MP_internal_any;

#ifdef __cplusplus
namespace mepinta{
  typedef internal_any internal_any;
}
#endif


CPP_EXTERN_START

EXPORTED_SYMBOL void * MP_internal_any_new(void);
EXPORTED_SYMBOL void * MP_internal_any_delete(void* intern_any);
EXPORTED_SYMBOL void * MP_internal_any_copy(void* intern_any);
EXPORTED_SYMBOL size_t MP_internal_any_data_type_size(void);
EXPORTED_SYMBOL size_t MP_internal_any_mem_size(void* intern_any);
EXPORTED_SYMBOL passing_t MP_intern_anyariable_passing(void);

//EXPORTED_SYMBOL char * MP_internal_any_serialize_xml(void* intern_any);
//EXPORTED_SYMBOL void * MP_internal_any_deserialize_xml(void* intern_any);
//EXPORTED_SYMBOL void * MP_internal_any_serialize_buffer(void* intern_any);
//EXPORTED_SYMBOL void * MP_internal_any_deserialize_buffer(void* intern_any);

CPP_EXTERN_END

#endif /* INTERNAL_ANY_H_ */
