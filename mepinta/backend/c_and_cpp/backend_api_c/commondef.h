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

#ifndef MEPINTA_COMMONDEF_H_
#define MEPINTA_COMMONDEF_H_

#include "config.h"

//{ Constants
#define TRUE 1
#define FALSE 0

#ifndef EXIT_FAILURE
  #define EXIT_FAILURE 1
#endif
#ifndef EXIT_SUCCESS
  #define EXIT_SUCCESS 0
#endif
#ifndef NULL
  #define NULL (void*)0
#endif
//}

//{ Utilities
#define TO_STRING(variable) #variable
#define _STR(variable) #variable
//Asserts an expression. If False, then it returns with the specified return value.
#define ASSERT_RETURN(expression,return_value) \
  if(!(expression)) { log_error("Failed assert:'"#expression"'.\n"); return return_value; }

#ifdef MEPINTA_DEBUG
  #define  ASSERT_DEBUG_RETURN(expression,return_value) \
    if(!(expression)) { log_error("Failed assert:'"#expression"'.\n"); return return_value; }
#else
  #define  ASSERT_DEBUG_RETURN(expression,return_value)
#endif
//} Utilities

//{ C++ extern C declaration helpers
#ifdef __cplusplus
  #define CPP_EXTERN_START  extern "C" {
  #define CPP_EXTERN_END  }
#else
  #define CPP_EXTERN_START
  #define CPP_EXTERN_END
#endif
//} C++ extern C declaration helpers

#endif /* MEPINTA_COMMONDEF_H_ */
