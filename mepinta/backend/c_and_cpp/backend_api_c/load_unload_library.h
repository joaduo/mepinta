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
 * load_unload_library.h
 *
 *  Created on: Sep 30, 2011
 *      Author: jduo
 */

#ifndef LOAD_UNLOAD_LIBRARY_H_
#define LOAD_UNLOAD_LIBRARY_H_

#include "config.h"

#ifndef STAND_ALONE_LOAD_UNLOAD
//Export symbols in case of the libmepintacore.so use
#ifdef __cplusplus
extern "C" {
#endif

EXPORTED_SYMBOL void* mepinta_load_library(const char* path, const char* symbol );
EXPORTED_SYMBOL int mepinta_unload_library(void* handle);

#ifdef __cplusplus
}
#endif

#else
//Include the implementation in the stand alone mode
//(for loading libmepintacore.so)
#include "load_unload_library.c"

#endif

//TODO: move this out of here
//Shedskin pipeline_abslayer macro
#define LOAD_LIBRARY\
    return mepinta_load_library(path->unit.c_str(),symbol->unit.c_str())

//Shedskin pipeline_abslayer macro
#define UNLOAD_LIBRARY\
    return mepinta_unload_library(handle)

#endif /* LOAD_UNLOAD_LIBRARY_H_ */
