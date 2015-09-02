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

#include "builtin.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"

//MANUALLY EDITED:
#include "pipeline_backend_implementation/log.h"
//Aliases //TODO: review why we can/cant logging.logError
#define logError log_error

#include <string>

/**
Created on Sep 28, 2011

@author: jduo
*/

namespace __pipeline_backend__ {
namespace __void_pointer_casting__ {
namespace __void_pointer_casting__ {

str *const_0, *const_1;

using __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue;
using __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue;

str *__name__;



//MANUALLY EDITED: START
//Something -> voidp
void *intToVoidp(__ss_int int_v) {
#ifdef  MEPINTA_DEBUG_POINTERS
  if (sizeof(__ss_int) <= sizeof(void*)){
#endif
    return (void*)int_v;
#ifdef  MEPINTA_DEBUG_POINTERS
  }
  else{
    logError("Cannot convert int (size=%d) to void* (size=%d) on this platform.\n",
                                                           sizeof(__ss_int), sizeof(void*)    );
    return NULL;
  }
#endif
}

void *doubleToVoidp(double float_v) {
#ifdef  MEPINTA_DEBUG_POINTERS
  if (sizeof(double) == sizeof(void*)){
#endif
    return *(void**)&float_v;
#ifdef  MEPINTA_DEBUG_POINTERS
  }
  else{
    logError("Cannot convert double (size=%d) to void* (size=%d) on this platform.\n",
                                                              sizeof(double), sizeof(void*)    );
    return NULL;
  }
#endif
}

//str is garbage collected by libgc
void *strToVoidp(str *_str_) {
    return (void*)_str_->unit.c_str();
}

//str is garbage collected by libgc
void *strCharpToVoidp(str *_str_) {
    return (void*)_str_->unit.c_str();
}

//str is garbage collected by libgc
void *strStringToVoidp(str *_str_) {
    //TODO: create str_boehm_gc_string_to_voidp
    //TODO:BEWARE (only works with Boehm GC) Add some kind of checking we are using Boehm in this Data type
    return (void*) &_str_->unit;
}

void *anyPtrToVoidp(void *anything) {
    return anything;
}

//voidp -> Something
__ss_int voidpToInt(void *voidp) {
#ifdef  MEPINTA_DEBUG_POINTERS
  if (sizeof(__ss_int) <= sizeof(void*)){
#endif
    return (long)voidp;
#ifdef  MEPINTA_DEBUG_POINTERS
  }
  else{
    logError("Cannot convert int (size=%d) from void* (size=%d) on this platform.\n",
                                                           sizeof(__ss_int), sizeof(void*)    );
    return 0;
  }
#endif
}

double voidpToDouble(void *voidp) {
#ifdef  MEPINTA_DEBUG_POINTERS
  if (sizeof(double) == sizeof(void*)){
#endif
    return *(double*)&voidp;
#ifdef  MEPINTA_DEBUG_POINTERS
  }
  else{
    logError("Cannot convert double (size=%d) from void* (size=%d) on this platform.\n",
                                                              sizeof(double), sizeof(void*)    );
    return 0.;
  }
#endif
}

//str is garbage collected by libgc
str *voidpToStr(void *voidp) {
    str * text;
    if(voidp != NULL){
      text = new str((char*)voidp);
    }
    else{
      text = new str();
    }
    return text;
}

//str is garbage collected by libgc
str *voidpCharpToStr(void *voidp) {
    str * text;
    if(voidp != NULL){
      text = new str((char*)voidp);
    }
    else{
      text = new str();
    }
    return text;
}

//str is garbage collected by libgc
str *voidpStringToStr(void *voidp) {
    str * text;
    if(voidp != NULL){
      __GC_STRING * unit = (__GC_STRING*)voidp;
      text = new str(unit->c_str());
    }
    else{
      text = new str();
    }
    return text;
}

list<__ss_int> *voidpToListInt(void *voidp) {
    return (list<__ss_int> *) voidp;
}

__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *voidp_to_FunctionPropertyValue(void *voidp) {
    return (__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue*)voidp;
}

__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue *voidp_to_FunctumPropertyValue(void *voidp) {
    return (__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue*)voidp;
}

//voidp -> Functions
lambda0 voidpToFuncArgVoid(void *voidp) {
    //func_arg_void();
    return (lambda0)voidp;
}

lambda1 voidpToFuncArgVoidp(void *voidp) {
    //func_arg_voidp(NULL);
    return (lambda1)voidp;
}

lambda2 voidpToProcessorFunc(void *voidp) {
    return (lambda2)voidp;
}

lambda3 voidpToCopyToFunc(void *voidp) {
    return (lambda3)voidp;
}

//MANUALLY EDITED: END

void *shedskin_void_pointer_casting() {
//    void *voidp;
//
//    voidp = NULL;
//    voidpToFuncArgVoid(voidp);
//    voidpToFuncArgVoidp(voidp);
//    voidpToProcessorFunc(voidp);
//    voidpToInt(voidp);
//    voidpToStr(voidp);
//    voidpToDouble(voidp);
//    voidpToListInt(voidp);
//    anyPtrToVoidp(((***ERROR***)(voidp)));
//    intToVoidp(1);
//    doubleToVoidp(10.0);
//    strToVoidp(const_0);
    return NULL;
}

void __init() {
    const_0 = new str("");
    const_1 = new str("__main__");

    __name__ = new str("void_pointer_casting");

//    if (__eq(__name__, const_1)) {
//        shedskin_void_pointer_casting();
//    }
}

} // module namespace
} // module namespace
} // module namespace

