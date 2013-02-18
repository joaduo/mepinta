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
 * load_unload_library.c
 *
 *  Created on: Sep 30, 2011
 *      Author: jduo
 */

#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "load_unload_library.h"

//Define a lightweight logging funtions for the stand alone version
//(this version is only used to load libmepintacore.so, then the load and
//unload of libraries is done through the libmepintacore.so (who exports
//its symbols))
#ifndef STAND_ALONE_LOAD_UNLOAD
#include "log.h"
#else
#include <stdio.h>
#define log_error(fmt, ...) fprintf(stderr,"ERROR(un/load library): "fmt,##__VA_ARGS__)
#define log_debug(fmt, ...) fprintf(stdout,"DEBUG(un/load library): "fmt,##__VA_ARGS__)
#endif

//TODO: accept an int from upper layers, so there will be more freedom setting the flag
void* mepinta_load_library(const char* path, const char* symbol ){
  int flag = RTLD_LAZY;//RTLD_NOW;
  if(path != NULL || symbol != NULL){
    if(strcmp(symbol,"global") == 0){
      flag = flag | RTLD_GLOBAL;
    }
    else if(strcmp(symbol,"local") == 0){
      flag = flag | RTLD_LOCAL;
    }
    else if(strcmp(symbol,"deep") == 0){
      //Review:RTLD_DEEPBIND (since glibc 2.3.4)
      //      Place the lookup scope of the symbols in this library ahead of the global scope. This means that a self-contained library will use its own symbols in preference to global symbols with the same name contained in libraries that have already been loaded. This flag is not specified in POSIX.1-2001.
      flag = flag | RTLD_GLOBAL | RTLD_DEEPBIND;
    }
    else {
      log_error("Loading symbols in that '%s' way is not supported.\n",symbol);
      return NULL;
    }
    log_debug("Loading %s with %s symbols. flag=0x%x.\n",path,symbol,flag);
    dlerror();//clean old errors
    void* handle = dlopen(path,flag);
    //If dlopen() fails for any reason, it returns NULL.
    if(handle== NULL){
      log_error("Failed to load the requested library. Reason: %s\n",dlerror());
    }
    return handle;
  }
  else{
    log_error("Path or symbol are NULL pointer.\n");
    return NULL;
  }
}

int mepinta_unload_library(void* handle){
  dlerror();//clean old errors
  if(handle != NULL){
    int rtrn_v = dlclose(handle);
    if(rtrn_v != 0){
      log_error("Failed to unload the requested library. Reason: %s\n",dlerror());
    }
    return rtrn_v;
  }
  else{
    log_error("Failed to unload the requested library. Handle is a NULL pointer.\n");
    return EXIT_FAILURE;
  }
}

