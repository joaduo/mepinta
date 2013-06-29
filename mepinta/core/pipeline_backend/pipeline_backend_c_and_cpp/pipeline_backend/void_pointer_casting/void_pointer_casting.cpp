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
void *int_to_voidp(__ss_int int_v) {
#ifdef  MEPINTA_DEBUG_POINTERS
  if (sizeof(__ss_int) <= sizeof(void*)){
#endif
    return (void*)int_v;
#ifdef  MEPINTA_DEBUG_POINTERS
  }
  else{
    log_error("Cannot convert int (size=%d) to void* (size=%d) on this platform.\n",
                                                           sizeof(__ss_int), sizeof(void*)    );
    return NULL;
  }
#endif
}

void *double_to_voidp(double float_v) {
#ifdef  MEPINTA_DEBUG_POINTERS
  if (sizeof(double) == sizeof(void*)){
#endif
    return *(void**)&float_v;
#ifdef  MEPINTA_DEBUG_POINTERS
  }
  else{
    log_error("Cannot convert double (size=%d) to void* (size=%d) on this platform.\n",
                                                              sizeof(double), sizeof(void*)    );
    return NULL;
  }
#endif
}

//str is garbage collected by libgc
void *str_to_voidp(str *_str_) {
    return (void*)_str_->unit.c_str();
}

//str is garbage collected by libgc
void *str_charp_to_voidp(str *_str_) {
    return (void*)_str_->unit.c_str();
}

//str is garbage collected by libgc
void *str_string_to_voidp(str *_str_) {
    //return (void*) &_str_->unit; //WRONG HACK! (later will try to free a string allocated with GC Boehm)
    //TODO: create str_boehm_gc_string_to_voidp
    return (void*) new std::string(_str_->unit.c_str());
}

void *any_ptr_to_voidp(void *anything) {
    return anything;
}

//voidp -> Something
__ss_int voidp_to_int(void *voidp) {
#ifdef  MEPINTA_DEBUG_POINTERS
  if (sizeof(__ss_int) <= sizeof(void*)){
#endif
    return (long)voidp;
#ifdef  MEPINTA_DEBUG_POINTERS
  }
  else{
    log_error("Cannot convert int (size=%d) from void* (size=%d) on this platform.\n",
                                                           sizeof(__ss_int), sizeof(void*)    );
    return 0;
  }
#endif
}

double voidp_to_double(void *voidp) {
#ifdef  MEPINTA_DEBUG_POINTERS
  if (sizeof(double) == sizeof(void*)){
#endif
    return *(double*)&voidp;
#ifdef  MEPINTA_DEBUG_POINTERS
  }
  else{
    log_error("Cannot convert double (size=%d) from void* (size=%d) on this platform.\n",
                                                              sizeof(double), sizeof(void*)    );
    return 0.;
  }
#endif
}

//str is garbage collected by libgc
str *voidp_to_str(void *voidp) {
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
str *voidp_charp_to_str(void *voidp) {
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
str *voidp_string_to_str(void *voidp) {
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

list<__ss_int> *voidp_to_list_int(void *voidp) {
    return (list<__ss_int> *) voidp;
}

__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *voidp_to_FunctionPropertyValue(void *voidp) {
    return (__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue*)voidp;
}

__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue *voidp_to_FunctumPropertyValue(void *voidp) {
    return (__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue*)voidp;
}

//voidp -> Functions
lambda0 voidp_to_func_arg_void(void *voidp) {
    //func_arg_void();
    return (lambda0)voidp;
}

lambda1 voidp_to_func_arg_voidp(void *voidp) {
    //func_arg_voidp(NULL);
    return (lambda1)voidp;
}

lambda2 voidp_to_processor_func(void *voidp) {
    return (lambda2)voidp;
}

lambda3 voidp_to_copy_to_func(void *voidp) {
    return (lambda3)voidp;
}

//MANUALLY EDITED: END

void *shedskin_type_generation_voidp() {
//    void *voidp;
//
//    voidp = NULL;
//    voidp_to_func_arg_void(voidp);
//    voidp_to_func_arg_voidp(voidp);
//    voidp_to_processor_func(voidp);
//    voidp_to_int(voidp);
//    voidp_to_str(voidp);
//    voidp_to_double(voidp);
//    voidp_to_list_int(voidp);
//    any_ptr_to_voidp(((***ERROR***)(voidp)));
//    int_to_voidp(1);
//    double_to_voidp(10.0);
//    str_to_voidp(const_0);
    return NULL;
}

void __init() {
    const_0 = new str("");
    const_1 = new str("__main__");

    __name__ = new str("void_pointer_casting");

//    if (__eq(__name__, const_1)) {
//        shedskin_type_generation_voidp();
//    }
}

} // module namespace
} // module namespace
} // module namespace

