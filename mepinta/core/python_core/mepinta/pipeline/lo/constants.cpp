#include "builtin.hpp"
#include "mepinta/pipeline/lo/constants.hpp"

/**
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

This file is part of Mepinta.

Mepinta is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Mepinta is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Mepinta. If not, see <http://www.gnu.org/licenses/>.
*/

namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __constants__ {

str *const_0;


str *MEPINTA_C_NAMESPACE_PREFIX, *__name__;
__ss_int CUSTOM_INPUT_OUTPUT_PROPS, CUSTOM_INPUT_PROPS, CUSTOM_OUTPUT_PROPS, CUSTOM_PROPERTY_FLAG, C_EXIT_FAILURE, C_EXIT_SUCCESS, FUNCTION_PROPERTY_FLAG, FUNCTUM_PROPERTY_FLAG, INPUT_OUTPUT_PROPS, INPUT_PROPERTY_FLAG, INPUT_PROPS, INTERNAL_PROPERTY_FLAG, NULL_UID, OUTPUT_PROPERTY_FLAG, OUTPUT_PROPS, PROCESSOR_EXIT_FAILURE, PROCESSOR_EXIT_NORMAL, PROCESSOR_FUNC_NULL;



__ss_bool hasFlags(__ss_int prop_type, __ss_int flags) {
    
    return ___bool((((prop_type)&(flags))!=0));
}

void __init() {
    const_0 = new str("MP_");

    __name__ = new str("constants");

    NULL_UID = 0;
    INPUT_PROPS = 1;
    OUTPUT_PROPS = 2;
    INPUT_OUTPUT_PROPS = 3;
    CUSTOM_INPUT_PROPS = 101;
    CUSTOM_OUTPUT_PROPS = 102;
    CUSTOM_INPUT_OUTPUT_PROPS = 103;
    C_EXIT_SUCCESS = 0;
    C_EXIT_FAILURE = 1;
    PROCESSOR_EXIT_NORMAL = 0;
    PROCESSOR_EXIT_FAILURE = 1;
    PROCESSOR_FUNC_NULL = 100;
    INPUT_PROPERTY_FLAG = 1;
    INTERNAL_PROPERTY_FLAG = 2;
    OUTPUT_PROPERTY_FLAG = 4;
    FUNCTION_PROPERTY_FLAG = 8;
    FUNCTUM_PROPERTY_FLAG = 16;
    CUSTOM_PROPERTY_FLAG = 256;
    MEPINTA_C_NAMESPACE_PREFIX = const_0;
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "mepinta/pipeline/lo/constants.hpp"
#include <structmember.h>
#include "mepinta/pipeline/lo/constants.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_constants;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __constants__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_constants_hasFlags(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("prop_type", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("flags", 1, 0, 0, args, kwargs);

        return __to_py(__constants__::hasFlags(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_constants_as_number = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

static PyMethodDef Global_mepinta_pipeline_lo_constantsMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"hasFlags", (PyCFunction)Global_mepinta_pipeline_lo_constants_hasFlags, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_constants(void) {

    __ss_mod_mepinta_pipeline_lo_constants = Py_InitModule((char *)"constants", Global_mepinta_pipeline_lo_constantsMethods);
    if(!__ss_mod_mepinta_pipeline_lo_constants)
        return;



}

PyMODINIT_FUNC addmepinta_pipeline_lo_constants(void) {
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"INPUT_OUTPUT_PROPS", __to_py(__constants__::INPUT_OUTPUT_PROPS));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"C_EXIT_FAILURE", __to_py(__constants__::C_EXIT_FAILURE));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"OUTPUT_PROPERTY_FLAG", __to_py(__constants__::OUTPUT_PROPERTY_FLAG));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"INPUT_PROPERTY_FLAG", __to_py(__constants__::INPUT_PROPERTY_FLAG));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"CUSTOM_PROPERTY_FLAG", __to_py(__constants__::CUSTOM_PROPERTY_FLAG));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"C_EXIT_SUCCESS", __to_py(__constants__::C_EXIT_SUCCESS));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"OUTPUT_PROPS", __to_py(__constants__::OUTPUT_PROPS));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"INPUT_PROPS", __to_py(__constants__::INPUT_PROPS));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"PROCESSOR_EXIT_FAILURE", __to_py(__constants__::PROCESSOR_EXIT_FAILURE));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"MEPINTA_C_NAMESPACE_PREFIX", __to_py(__constants__::MEPINTA_C_NAMESPACE_PREFIX));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"PROCESSOR_EXIT_NORMAL", __to_py(__constants__::PROCESSOR_EXIT_NORMAL));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"INTERNAL_PROPERTY_FLAG", __to_py(__constants__::INTERNAL_PROPERTY_FLAG));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"CUSTOM_INPUT_PROPS", __to_py(__constants__::CUSTOM_INPUT_PROPS));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"PROCESSOR_FUNC_NULL", __to_py(__constants__::PROCESSOR_FUNC_NULL));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"FUNCTION_PROPERTY_FLAG", __to_py(__constants__::FUNCTION_PROPERTY_FLAG));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"NULL_UID", __to_py(__constants__::NULL_UID));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"CUSTOM_OUTPUT_PROPS", __to_py(__constants__::CUSTOM_OUTPUT_PROPS));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"FUNCTUM_PROPERTY_FLAG", __to_py(__constants__::FUNCTUM_PROPERTY_FLAG));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_constants, (char *)"CUSTOM_INPUT_OUTPUT_PROPS", __to_py(__constants__::CUSTOM_INPUT_OUTPUT_PROPS));

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __constants__

} // extern "C"
