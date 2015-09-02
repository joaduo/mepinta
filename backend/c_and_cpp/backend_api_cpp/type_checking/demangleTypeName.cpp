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

#include "demangleTypeName.h"

#include <stdlib.h>
#include <string.h>

#include <cxxabi.h>

#ifdef MEPINTA_USE_CXA_DEMANGLE

  char* MP_demangleTypeName(const char* mangled_name){
    int status=0;
    char* demangled_name_temp = abi::__cxa_demangle(mangled_name,NULL,NULL,&status);
    if(status==-2){
      log_debug("Could not demangle %s.\n",mangled_name);
      return (char*)mangled_name;
    }
    else if(status != 0){
      log_debug("Could not demangle %s. Status: %d\n",mangled_name,status);
      free(demangled_name_temp);
      return (char*)mangled_name;
    }
    else{
      char* demangled_name = (char*)MP_malloc_wrap(strlen(demangled_name_temp));
      strcpy(demangled_name, demangled_name_temp);
      free(demangled_name_temp);
      return demangled_name;
    }
  }

#else //MEPINTA_USE_CXA_DEMANGLE

  const char* MP_demangleTypeName(const char* mangled_name){
    return mangled_name;
  }

#endif //MEPINTA_USE_CXA_DEMANGLE


