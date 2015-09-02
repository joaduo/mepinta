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
 * props.h
 *
 *  Created on: Nov 2, 2011
 *      Author: jduo
 */

#ifndef PROPS_H_
#define PROPS_H_

#include "config.h"
#include "commondef.h"
#include "types.h"

//TODO: Review the convenient size of this values
#ifndef MEPINTA_PROPS_MEMORY_CHUNK
  #define MEPINTA_PROPS_MEMORY_CHUNK 32
#endif
#ifndef MEPINTA_PROPS_UNFREED_TRESHOLD
  #define MEPINTA_PROPS_UNFREED_TRESHOLD 128
#endif

CPP_EXTERN_START
  EXPORTED_SYMBOL mepinta_props* mepinta_props_new(int capacity);
  EXPORTED_SYMBOL int mepinta_props_set(mepinta_props* props, int index, prop_id_t prop_id, prop_name_t name, prop_value_t value, prop_handle_t handle, uint8_t changed);
  EXPORTED_SYMBOL int mepinta_props_set_capacity(mepinta_props* props, int capacity);
  EXPORTED_SYMBOL int mepinta_props_clear(mepinta_props* props);
  EXPORTED_SYMBOL int mepinta_props_delete(mepinta_props* props);
CPP_EXTERN_END

#endif /* PROPS_H_ */
