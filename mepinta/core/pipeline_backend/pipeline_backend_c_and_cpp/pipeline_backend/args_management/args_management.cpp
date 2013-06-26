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
#include "pipeline_backend/args_management/args_management.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"

//MANUALLY EDITED:
#include "pipeline_backend/implementation/args_management.h"

namespace __pipeline_backend__ {
namespace __args_management__ {
namespace __args_management__ {

str *__name__;
dict<__ss_int, void *> *args_per_thread;

void *getFunctumStructVoidp(void* func_ptr,void *args){
  //MANUALLY EDITED:
  GET_FUNCTUM_STRUCT;
}

void *getThreadArgs(__ss_int in_size, __ss_int out_size, __ss_int thread_id) {
    void *args;

    logError("Implement getThreadArgs!!\n");
//    if ((!(args_per_thread)->__contains__(thread_id))) {
//      args = createArgs(in_size, out_size);
//      args_per_thread->__setitem__(thread_id, args);
//    }
//    else{
//      args = args_per_thread->__getitem__(thread_id);
//      args_set_capacities(args,in_size,out_size);
//      args_set_capacities(args,in_size,out_size);
//    }
//    argsSetThreadId(args, thread_id);

//    //MANUALLY EDITED:
//    RESET_SIZES;
//    return args;
    return NULL;
}

__ss_int deleteArgs(void *args) {
  //MANUALLY EDITED:
  DELETE_ARGS;
}

void *createArgs(__ss_int in_size, __ss_int out_size) {
  //MANUALLY EDITED:
  CREATE_ARGS;
}

__ss_int argsSetThreadId(void *args, __ss_int thread_id) {
  //MANUALLY EDITED:
  SET_THREAD_ID;
}

__ss_int argsSetCapacity(void *args, __ss_int in_out_id, __ss_int props_size) {
  //MANUALLY EDITED:
  SET_CAPACITY;
}

__ss_int argsAppendProp(void *args, __ss_int in_out_id, __ss_int index, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop_real, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *data_type) {
  //MANUALLY EDITED:
  APPEND_PROP;
}

__ss_int argsSetChanged(void *args, __ss_int in_out_id, __ss_int index) {
  //MANUALLY EDITED:
  SET_PROP_CHANGED;
}

__ss_int argsSetUnchanged(void *args, __ss_int in_out_id, __ss_int index) {
  //MANUALLY EDITED:
  SET_PROP_UNCHANGED;
}

set<__ss_int> *argsBuildChangedSet(void *args, __ss_int in_out_id, set<__ss_int> *changed) {
    //MANUALLY EDITED:
    BUILD_CHANGED_SET;

    return changed;
}

void *shedskin_args_management() {

    return NULL;
}

void __init() {
    __name__ = new str("args_management");

    args_per_thread = (new dict<__ss_int, void *>());
}

} // module namespace
} // module namespace
} // module namespace

