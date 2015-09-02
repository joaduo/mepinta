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
 * solve_symbol.h
 *
 *  Created on: Sep 30, 2011
 *      Author: jduo
 */

#ifndef SOLVE_SYMBOL_H_
#define SOLVE_SYMBOL_H_

#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORTED_SYMBOL void * mepinta_solve_symbol(const void* handle, const char* symbol);
EXPORTED_SYMBOL void * mepinta_solve_symbol_quiet(const void* handle, const char* symbol);

#ifdef __cplusplus
}
#endif

//TODO: move this out of here
//Shedskin pipeline_abslayer macro
#define SHEDSKIN_SOLVE_SYMBOL \
	return mepinta_solve_symbol(handle,complete_symbol->unit.c_str())

//TODO: change this!
#define SHEDSKIN_SOLVE_SYMBOL_NEW \
  if(quiet){ \
    return mepinta_solve_symbol(handle,complete_symbol->unit.c_str()) \
  } \
  else { \
    return mepinta_solve_symbol_quiet(handle,complete_symbol->unit.c_str()) \
  }

#endif /* SOLVE_SYMBOL_H_ */
