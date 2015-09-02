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
 * memmngmt.c
 *
 *  Created on: Oct 10, 2011
 *      Author: jduo
 */

#include <stdlib.h>
#include <gc/gc.h>
#include <errno.h>
#include <string.h>

#include "sdk.h"

//{ Memory Management Wrapping

#ifdef FORCE_MEMORY_GARBAGE_COLLECTOR
//TODO: check if this is possible to avoid in case we want to specifically mix things
//Forcing memory garbage collection because of this
/* from http://www.hpl.hp.com/personal/Hans_Boehm/gc/simple_example.html
 * Interaction with the system malloc
 *   It is usually best not to mix garbage-collected allocation with the system malloc-free.
 *   If you do, you need to be careful not to store pointers to the garbage-collected heap
 *   in memory allocated with the system malloc.
 */

//We create this functions and we don't use macros because in the future we may want to alter memory allocation behavior
void* MP_calloc_wrap(size_t nmemb, size_t size){
  void* mem_addr = GC_MALLOC(nmemb*size);
  return mem_addr;
}

void* MP_malloc_wrap(size_t size){
  void* mem_addr = GC_MALLOC(size);
  return mem_addr;
}

void  MP_free_wrap(void *ptr){
  log_debug_warning("Beware! Using MP_free_wrap_gc means the data will be "
                    "freed even if there another pointer pointing to it."
                    "(freeing doesn't mean decrementing reference count)\n");
  GC_FREE(ptr);
}

void* MP_realloc_wrap(void *ptr, size_t size){
  return GC_REALLOC(ptr, size);
}

#else

#define PRINT_MEMORY_ERROR(function_name)                                                       \
  int errno_cpy = errno;                                                                        \
  if (errno_cpy == ENOMEM){                                                                     \
    log_critical("Error calling '"#function_name"'. Error message: '%s'\n",strerror(errno_cpy));\
    log_funny("Ok, something is really wrong... Tell mom and dad that i love them.\n");         \
  }

//We create this functions and we don't use macros because in the future we may want to alter memory allocation behavior
void* MP_calloc_wrap(size_t nmemb, size_t size){
  void* mem_addr = calloc(nmemb, size);
  PRINT_MEMORY_ERROR(calloc);
  return mem_addr;
}

void* MP_malloc_wrap(size_t size){
  void* mem_addr = malloc(size);
  PRINT_MEMORY_ERROR(malloc);
  return mem_addr;
}

void  MP_free_wrap(void *ptr){
  free(ptr);
  PRINT_MEMORY_ERROR(free);
}

//TODO: check errors?
void* MP_realloc_wrap(void *ptr, size_t size){
  return realloc(ptr, size);
}

#endif

//{ Garbage collection enabled wrappers
//TODO: find if GC_MALLOC has some error checking API? Seems not to have (although it can crash anyway :-D)

void* MP_calloc_wrap_gc(size_t nmemb, size_t size){
  void* mem_addr = GC_MALLOC(nmemb*size);
  return mem_addr;
}

void* MP_malloc_wrap_gc(size_t size){
  return GC_MALLOC(size);
}

void  MP_free_wrap_gc(void *ptr){
  log_debug_warning("Beware! Using MP_free_wrap_gc means the data will be "
                    "freed even if there is another pointer pointing to it."
                    "(freeing doesn't mean decrementing reference count)\n");
  GC_FREE(ptr);
}

void  MP_free_wrap_gc_dummy(void *ptr){
  log_debug("For convenience this functions does not free memory immediately, "
            "but leaves the job for the garbage collector.\n");
}

void* MP_realloc_wrap_gc(void *ptr, size_t size){
  return GC_REALLOC(ptr, size);
}
//} Garbage collection enabled wrappers

void* MP_memcpy_wrap(void *dest, const void *src, size_t n){
  return memcpy(dest,src,n);
}

void* MP_memmove_wrap(void *dest, const void *src, size_t n){
	return memmove(dest,src,n);
}

//} Memory Management Wrapping
