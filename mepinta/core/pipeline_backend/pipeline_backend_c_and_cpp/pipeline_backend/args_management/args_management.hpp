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

#ifndef __PIPELINE_ABSLAYER_ARGS_MANAGEMENT_HPP
#define __PIPELINE_ABSLAYER_ARGS_MANAGEMENT_HPP

using namespace __shedskin__;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */
class PipelineValuePointer;
class Pipeline;
class DataType;
class CommonData;
class ProcessorFunction;
class Property;
class FunctionPropertyValue;
}
}
}
}
}
namespace __pipeline_backend__ {
namespace __args_management__ {
namespace __args_management__ {



extern str *__name__;
extern dict<__ss_int, void *> *args_per_thread;


void __init();
void *get_functum_struct_voidp(void* func_ptr,void *args);
void *get_thread_args(__ss_int in_size, __ss_int out_size, __ss_int thread_id);
__ss_int delete_args(void *args);
void *create_args(__ss_int in_size, __ss_int out_size);
__ss_int args_set_thread_id(void *args, __ss_int thread_id);
__ss_int args_set_capacity(void *args, __ss_int in_out_id, __ss_int props_size);
__ss_int args_append_prop(void *args, __ss_int in_out_id, __ss_int index, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop_real, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *data_type);
__ss_int args_set_changed(void *args, __ss_int in_out_id, __ss_int index);
__ss_int args_set_unchanged(void *args, __ss_int in_out_id, __ss_int index);
set<__ss_int> *args_build_changed_set(void *args, __ss_int in_out_id, set<__ss_int> *changed);
void *shedskin_type_generation_argsm();

} // module namespace
} // module namespace
} // module namespace
namespace __shedskin__ { /* XXX */

}
#endif
