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
 * solve_symbol.c
 *
 *  Created on: Sep 30, 2011
 *      Author: jduo
 */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "log.h"
#include "solve_symbol.h"

//get the pointer of a function inside a shared library.
void * mepinta_solve_symbol(const void* handle, const char* symbol){
  log_debug("Solving symbol '%s' for handle at %p\n",symbol,handle);
  if(handle != NULL && symbol != NULL){
    dlerror();//clean old errors
    void * sym_p = dlsym((void*)handle,symbol);
    char* error_str= dlerror();
    if(error_str != NULL){
      log_error("Failed to find the requested symbol '%s'. Reason: %s.\n",symbol,error_str);
    }
    else{
      log_debug("Successfully found the symbol at %p\n",sym_p);
    }
    return sym_p;
  }
  else{
    if (handle != NULL){
      log_error("Failed to find the requested symbol for handle at %p. Symbol is NULL.\n",handle);
    }
    else if( symbol != NULL){
      log_error("Failed to find the requested symbol '%s'. Handle is NULL.\n",symbol);
    }
    else{
      log_error("Failed to find the requested symbol. Handle and symbol are NULL.\n");
    }
    return NULL;
  }
}

//get the pointer of a function inside a shared library.
//Do not print as error, instead as debug. Useful when checking symbol existance
void* mepinta_solve_symbol_quiet(const void* handle, const char* symbol){
//  log_debug("Solving symbol '%s' for handle at %p\n",symbol,handle);
  if(handle != NULL && symbol != NULL){
    dlerror();//clean old errors
    void * sym_p = dlsym((void*)handle,symbol);
//    char* error_str= dlerror();
//    if(error_str != NULL){
//      log_debug("Failed to find the requested symbol '%s'. Reason: %s.\n",symbol,error_str);
//    }
//    else{
//      log_debug("Successfully found the symbol at %p\n",sym_p);
//    }
    return sym_p;
  }
  else{
    if (handle != NULL){
      log_debug("Failed to find the requested symbol for handle at %p. Symbol is NULL.\n",handle);
    }
    else if( symbol != NULL){
      log_debug("Failed to find the requested symbol '%s'. Handle is NULL.\n",symbol);
    }
    else{
      log_debug("Failed to find the requested symbol. Handle and symbol are NULL.\n");
    }
    return NULL;
  }
}
