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

#ifndef __PIPELINE_ABSLAYER_VOID_POINTER_CASTING_HPP
#define __PIPELINE_ABSLAYER_VOID_POINTER_CASTING_HPP

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
class ProcessorUpdatedProperties;
class ProcessorFunction;
class Property;
}
namespace __hidden_data_types__ { /* XXX */
class FunctionPropertyValue;
class FunctumPropertyValue;
}
}
}
}
}
namespace __pipeline_backend__ {
namespace __void_pointer_casting__ {
namespace __void_pointer_casting__ {

extern str *const_0, *const_1;


typedef void *(*lambda0)();
typedef void *(*lambda1)(void *);
typedef int (*lambda2)(void *);

extern str *__name__;


void __init();
void *func_arg_void();
void *func_arg_voidp(void *voidp);
__ss_int processor_func(void *args_voidp);
void *int_to_voidp(__ss_int int_v);
void *double_to_voidp(double float_v);
void *str_to_voidp(str *_str_);
void *str_charp_to_voidp(str *_str_);
void *str_string_to_voidp(str *_str_);
void *any_ptr_to_voidp(void *anything);
__ss_int voidp_to_int(void *voidp);
double voidp_to_double(void *voidp);
str *voidp_to_str(void *voidp);
str *voidp_charp_to_str(void *voidp);
str *voidp_string_to_str(void *voidp);
list<__ss_int> *voidp_to_list_int(void *voidp);
__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *voidp_to_FunctionPropertyValue(void *voidp);
__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue *voidp_to_FunctumPropertyValue(void *voidp);
lambda0 voidp_to_func_arg_void(void *voidp);
lambda1 voidp_to_func_arg_voidp(void *voidp);
lambda2 voidp_to_processor_func(void *voidp);
void *shedskin_type_generation_voidp();

} // module namespace
} // module namespace
} // module namespace
#endif
