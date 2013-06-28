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
typedef void * (*lambda3)(void *, void *);

extern str *__name__;


void __init();
void *func_arg_void();
void *func_arg_voidp(void *voidp);
__ss_int processor_func(void *args_voidp);
void *intToVoidp(__ss_int int_v);
void *doubleToVoidp(double float_v);
void *strToVoidp(str *_str_);
void *strCharpToVoidp(str *_str_);
void *strStringToVoidp(str *_str_);
void *anyPtrToVoidp(void *anything);
__ss_int voidpToInt(void *voidp);
double voidpToDouble(void *voidp);
str *voidpToStr(void *voidp);
str *voidpCharpToStr(void *voidp);
str *voidpStringToStr(void *voidp);
list<__ss_int> *voidpToListInt(void *voidp);
__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *voidp_to_FunctionPropertyValue(void *voidp);
__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue *voidp_to_FunctumPropertyValue(void *voidp);
lambda0 voidpToFuncArgVoid(void *voidp);
lambda1 voidpToFuncArgVoidp(void *voidp);
lambda2 voidpToProcessorFunc(void *voidp);
lambda3 voidpToCopyToFunc(void *voidp);
void *shedskin_void_pointer_casting();

} // module namespace
} // module namespace
} // module namespace
#endif
