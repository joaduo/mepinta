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
 * charp.h
 *
 *  Created on: Oct 31, 2011
 *      Author: jduo
 */

#ifndef CHARP_H_
#define CHARP_H_

#include <mepintasdk/config.h>

#define charp char*

CPP_EXTERN_START

EXPORTED_SYMBOL void * MP_charp_new(void);
EXPORTED_SYMBOL void * MP_charp_delete(void* charp_v);
EXPORTED_SYMBOL void * MP_charp_copy(void* charp_v);
EXPORTED_SYMBOL size_t MP_charp_data_type_size(void);
EXPORTED_SYMBOL size_t MP_charp_mem_size(void* charp_v);

//EXPORTED_SYMBOL char * MP_charp_v_serialize_xml(void* charp_v);
//EXPORTED_SYMBOL void * MP_charp_v_deserialize_xml(void* charp_v);
//EXPORTED_SYMBOL void * MP_charp_v_serialize_buffer(void* charp_v);
//EXPORTED_SYMBOL void * MP_charp_v_deserialize_buffer(void* charp_v);

CPP_EXTERN_END

#endif /* charp_v_H_ */
