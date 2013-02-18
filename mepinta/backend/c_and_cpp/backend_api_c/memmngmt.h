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

#ifndef MEMMNGMT_H_
#define MEMMNGMT_H_

#include <stddef.h>
#include "config.h"
#include "commondef.h"
#include "types.h"

CPP_EXTERN_START
  //Wrappers for memory management functions. Used to replace memory management functions in plugins
  EXPORTED_SYMBOL void* MP_calloc_wrap(size_t nmemb, size_t size);
  EXPORTED_SYMBOL void* MP_malloc_wrap(size_t size);
  EXPORTED_SYMBOL void  MP_free_wrap(void *ptr);
  EXPORTED_SYMBOL void* MP_realloc_wrap(void *ptr, size_t size);

  EXPORTED_SYMBOL void* MP_calloc_wrap_gc(size_t nmemb, size_t size);
  EXPORTED_SYMBOL void* MP_malloc_wrap_gc(size_t size);
  EXPORTED_SYMBOL void  MP_free_wrap_gc(void *ptr);
  EXPORTED_SYMBOL void  MP_free_wrap_gc_dummy(void *ptr);
  EXPORTED_SYMBOL void* MP_realloc_wrap_gc(void *ptr, size_t size);

  EXPORTED_SYMBOL void* MP_memcpy_wrap(void *dest, const void *src, size_t n);
  EXPORTED_SYMBOL void* MP_memmove_wrap(void *dest, const void *src, size_t n);
CPP_EXTERN_END

//{ Data types Macros

//TODO: should take in count CPP
//Option on the declaration
#define GARBAGE_COLLECTED
#define STAND_ALONE_MEM_MNGMNT
#define STAND_ALONE_MEM_GC

//TODO: hide symbols like in http://www.gnu.org/s/hello/manual/gnulib/Exported-Symbols-of-Shared-Libraries.html
#define MEMORY_MNGMNT_FUNCTIONS_GARBAGE_COLLECTED \
        malloc_t MP_malloc = MP_malloc_wrap_gc; \
        calloc_t MP_calloc = MP_calloc_wrap_gc; \
        free_t MP_free = MP_free_wrap_gc_dummy; \
        realloc_t MP_realloc = MP_realloc_wrap_gc;\
        memmove_t MP_memmove = MP_memmove_wrap;\
        memcpy_t MP_memcpy = MP_memcpy_wrap;

#define MEMORY_MNGMNT_FUNCTIONS_ \
        malloc_t MP_malloc = MP_malloc_wrap; \
        calloc_t MP_calloc = MP_calloc_wrap; \
        free_t MP_free = MP_free_wrap; \
        realloc_t MP_realloc = MP_realloc_wrap;\
        memmove_t MP_memmove = MP_memmove_wrap;\
        memcpy_t MP_memcpy = MP_memcpy_wrap;

#define MEMORY_MNGMNT_FUNCTIONS_STAND_ALONE_MEM_MNGMNT \
        malloc_t MP_malloc = malloc; \
        calloc_t MP_calloc = calloc; \
        free_t MP_free = free; \
        realloc_t MP_realloc = realloc;\
        memmove_t MP_memmove = memmove;\
        memcpy_t MP_memcpy = memcpy;

#define MEMORY_MNGMNT_FUNCTIONS_STAND_ALONE_MEM_GC \
        malloc_t MP_malloc = GC_malloc; \
        calloc_t MP_calloc = GC_malloc; \
        free_t MP_free = GC_free; \
        realloc_t MP_realloc = GC_realloc;\
        memmove_t MP_memmove = memmove;\
        memcpy_t MP_memcpy = memcpy;

#define DECLARE_MEMORY_MNGMNT_FUNCTIONS(OPTION) \
        MEMORY_MNGMNT_FUNCTIONS_##OPTION

#define INCLUDE_MEMORY_MNGMNT_FUNCTIONS \
  extern malloc_t MP_malloc; \
  extern calloc_t MP_calloc; \
  extern free_t MP_free; \
  extern realloc_t MP_realloc;\
  extern memmove_t MP_memmove;\
  extern memcpy_t MP_memcpy;

//} Data types Macros

#endif /* MEMMNGMT_H_ */
