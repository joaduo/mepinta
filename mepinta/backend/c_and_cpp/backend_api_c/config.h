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

#ifndef CONFIG_H_
#define CONFIG_H_

//TODO: define BUILDING_LIB_ARGS_API on windows compilation of the libmepintacore.dll
#if __GNUC__
#define EXPORTED_SYMBOL__ __attribute__((__visibility__("default")))
#elif BUILDING_LIB_ARGS_API && defined _MSC_VER
#define EXPORTED_SYMBOL __declspec(dllexport)
#elif defined _MSC_VER
#define EXPORTED_SYMBOL __declspec(dllimport)
#else
#define EXPORTED_SYMBOL
#endif

//TODO: this should be passed as a parameter to the compiler
//Enable debugging and health checking
#define MEPINTA_DEBUG

#ifdef MEPINTA_DEBUG
  //Check correct casting of pointers to properties values
  #define MEPINTA_DEBUG_POINTERS
  //Check correct casting of properties values, and any other casting.
  #define MEPINTA_DEBUG_TYPES
  //Make sure data is never directly accessed, but through the data API
  //#define MEPINTA_DEBUG_DATA_ISOLATION
  //Make sure args data is never directly accessed, but through the data API
  //#define MEPINTA_DEBUG_ARGS_ISOLATION
#endif

#define MEPINTA_USE_CXA_DEMANGLE

#ifdef __cplusplus
#define EXPORTED_SYMBOL extern "C" EXPORTED_SYMBOL__
#else
#define EXPORTED_SYMBOL EXPORTED_SYMBOL__
#endif

#define OS_PATH_SEP '/'
//When should we try to shrink the file path printed on logging
#define LOGGING_LENGTH_PATH_TRESHOLD 8

//TODO: review below!
//Optional parameters (already have their default)
//#define MEPINTA_PROPS_MEMORY_CHUNK 128
//#define FORCE_MEMORY_GARBAGE_COLLECTOR
//Optimization Config
//#define MEPINTA_OPTIMIZATION_MEMORY

#endif /* CONFIG_H_ */
