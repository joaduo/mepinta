#include "builtin.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"

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
namespace __FunctionCaller__ {

str *const_0, *const_1, *const_2, *const_3, *const_4, *const_5, *const_6;

using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::voidpToFuncArgVoid;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::voidpToFuncArgVoidp;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::voidpToProcessorFunc;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::voidpToCopyToFunc;
using __pipeline_backend__::__logging__::__logging__::logError;
using __pipeline_backend__::__logging__::__logging__::logWarning;
using __mepinta__::__pipeline__::__lo__::__exceptions__::__MepintaLoError__::MepintaLoError;

str *__name__;
__ss_int PROCESSOR_FUNC_NULL;



/**
class FunctionCaller
*/

class_ *cl_FunctionCaller;

void *FunctionCaller::callCopyToFunc(void *func_ptr, void *to_ptr, void *from_ptr) {
    /**
    Calls a "copyTo" function with the prototype "void* func_name(void*,void*)" 
    */
    __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::lambda3 casted_func_ptr;
    str *msg;
    __ss_bool __3, __4, __5;

    if (((func_ptr!=NULL) and (to_ptr!=NULL) and (from_ptr!=NULL))) {
        casted_func_ptr = voidpToCopyToFunc(func_ptr);
        to_ptr = casted_func_ptr(to_ptr, from_ptr);
        if ((to_ptr==NULL)) {
            msg = const_0;
            logError(msg);
            throw ((new __mepinta__::__pipeline__::__lo__::__exceptions__::__MepintaLoError__::MepintaLoError(msg)));
        }
        return to_ptr;
    }
    else {
        msg = const_1;
        logError(msg);
        throw ((new __mepinta__::__pipeline__::__lo__::__exceptions__::__MepintaLoError__::MepintaLoError(msg)));
    }
    return 0;
}

void *FunctionCaller::callFuncNoArgs(void *func_ptr) {
    /**
    Calls a function with the prototype "void* func_name(void)" 
    */
    str *msg;
    __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::lambda0 casted_func_ptr;

    if ((func_ptr!=NULL)) {
        casted_func_ptr = voidpToFuncArgVoid(func_ptr);
        return casted_func_ptr();
    }
    else {
        msg = const_2;
        logError(msg);
        throw ((new __mepinta__::__pipeline__::__lo__::__exceptions__::__MepintaLoError__::MepintaLoError(msg)));
    }
    return 0;
}

__ss_int FunctionCaller::callIntFuncVoidp(void *func_ptr, void *voidp) {
    /**
    Calls a function with the prototype "int func_name(void*)"
    Since self.callProcessorFunc does the same it's reused
    */
    str *msg;

    if ((func_ptr!=NULL)) {
        return this->callProcessorFunc(func_ptr, voidp);
    }
    else {
        msg = const_3;
        logError(msg);
        throw ((new __mepinta__::__pipeline__::__lo__::__exceptions__::__MepintaLoError__::MepintaLoError(msg)));
    }
    return 0;
}

void *FunctionCaller::callFunc(void *func_ptr, void *func_args) {
    /**
    Calls a function with the prototype "void* func_name(void*)" 
    */
    str *msg;
    __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::lambda1 casted_func_ptr;

    if ((func_ptr!=NULL)) {
        casted_func_ptr = voidpToFuncArgVoidp(func_ptr);
        return casted_func_ptr(func_args);
    }
    else {
        msg = const_4;
        logError(msg);
        throw ((new __mepinta__::__pipeline__::__lo__::__exceptions__::__MepintaLoError__::MepintaLoError(msg)));
    }
    return 0;
}

__ss_int FunctionCaller::callProcessorFunc(void *func_ptr, void *args) {
    /**
    Calls a processor function with the prototype "int func_name(void*)" 
    */
    __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::lambda2 casted_func_ptr;

    if ((func_ptr!=NULL)) {
        casted_func_ptr = voidpToProcessorFunc(func_ptr);
        return casted_func_ptr(args);
    }
    else {
        logWarning(const_5);
        return PROCESSOR_FUNC_NULL;
    }
    return 0;
}

void *shedskin_FunctionCaller() {
    FunctionCaller *fc;

    fc = (new FunctionCaller());
    fc->callFuncNoArgs(NULL);
    fc->callFunc(NULL, NULL);
    fc->callProcessorFunc(NULL, NULL);
    return NULL;
}

void __init() {
    const_0 = new str("copyTo function failed to copy values.");
    const_1 = new str("func_ptr, to_ptr o from_ptr is NULL. Couldn't call copyTo function with prototype \"void* func_name(void*)\".");
    const_2 = new str("func_ptr is NULL. Couldn't call function with prototype \"void* func_name(void)\".");
    const_3 = new str("func_ptr is NULL. Couldn't call function with prototype \"int func_name(void*)\".");
    const_4 = new str("func_ptr is NULL. Couldn't call function with prototype \"void* func_name(void*)\".");
    const_5 = new str("func_ptr is NULL. Couldn't call processor function.");
    const_6 = new str("__main__");

    __name__ = new str("FunctionCaller");

    PROCESSOR_FUNC_NULL = __mepinta__::__pipeline__::__lo__::__constants__::PROCESSOR_FUNC_NULL;
    cl_FunctionCaller = new class_("FunctionCaller");
    if (__eq(__name__, const_6)) {
        shedskin_FunctionCaller();
    }
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include <structmember.h>
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_FunctionCaller;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __FunctionCaller__ { /* XXX */

/* class FunctionCaller */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *__ss_object;
} __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObject;

static PyMemberDef __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller_callCopyToFunc(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        void *arg_0 = __ss_arg<void *>("func_ptr", 0, 0, 0, args, kwargs);
        void *arg_1 = __ss_arg<void *>("to_ptr", 1, 0, 0, args, kwargs);
        void *arg_2 = __ss_arg<void *>("from_ptr", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObject *)self)->__ss_object->callCopyToFunc(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller_callFuncNoArgs(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        void *arg_0 = __ss_arg<void *>("func_ptr", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObject *)self)->__ss_object->callFuncNoArgs(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller_callIntFuncVoidp(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        void *arg_0 = __ss_arg<void *>("func_ptr", 0, 0, 0, args, kwargs);
        void *arg_1 = __ss_arg<void *>("voidp", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObject *)self)->__ss_object->callIntFuncVoidp(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller_callFunc(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        void *arg_0 = __ss_arg<void *>("func_ptr", 0, 0, 0, args, kwargs);
        void *arg_1 = __ss_arg<void *>("func_args", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObject *)self)->__ss_object->callFunc(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller_callProcessorFunc(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        void *arg_0 = __ss_arg<void *>("func_ptr", 0, 0, 0, args, kwargs);
        void *arg_1 = __ss_arg<void *>("args", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObject *)self)->__ss_object->callProcessorFunc(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"callCopyToFunc", (PyCFunction)__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller_callCopyToFunc, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"callFuncNoArgs", (PyCFunction)__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller_callFuncNoArgs, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"callIntFuncVoidp", (PyCFunction)__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller_callIntFuncVoidp, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"callFunc", (PyCFunction)__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller_callFunc, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"callProcessorFunc", (PyCFunction)__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller_callProcessorFunc, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObject *self = (__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__FunctionCaller__::cl_FunctionCaller;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerDealloc(__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyGetSetDef __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerGetSet[] = {
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "FunctionCaller.FunctionCaller",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller_as_number,  /* tp_as_number      */
    0,              /* tp_as_sequence    */
    0,              /* tp_as_mapping     */
    0,              /* tp_hash           */
    0,              /* tp_call           */
    0,              /* tp_str            */
    0,              /* tp_getattro       */
    0,              /* tp_setattro       */
    0,              /* tp_as_buffer      */
    Py_TPFLAGS_DEFAULT, /* tp_flags          */
    0,              /* tp_doc            */
    0,              /* tp_traverse       */
    0,              /* tp_clear          */
    0,              /* tp_richcompare    */
    0,              /* tp_weaklistoffset */
    0,              /* tp_iter           */
    0,              /* tp_iternext       */
    __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    0,              /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_FunctionCaller, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(0);
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCaller__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __FunctionCaller__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __FunctionCaller__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_FunctionCaller_shedskin_FunctionCaller(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(__FunctionCaller__::shedskin_FunctionCaller());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_FunctionCaller_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_FunctionCallerMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_FunctionCaller", (PyCFunction)Global_mepinta_pipeline_lo_FunctionCaller_shedskin_FunctionCaller, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_FunctionCaller(void) {

    __ss_mod_mepinta_pipeline_lo_FunctionCaller = Py_InitModule((char *)"FunctionCaller", Global_mepinta_pipeline_lo_FunctionCallerMethods);
    if(!__ss_mod_mepinta_pipeline_lo_FunctionCaller)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_FunctionCaller, "FunctionCaller", (PyObject *)&__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_FunctionCaller(void) {
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_FunctionCaller, (char *)"PROCESSOR_FUNC_NULL", __to_py(__FunctionCaller__::PROCESSOR_FUNC_NULL));

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __FunctionCaller__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __FunctionCaller__ { /* XXX */

PyObject *FunctionCaller::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObject *self = (__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObject *)(__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObjectType, 0));
        self->__ss_object = this;
        __ss_proxy->__setitem__(self->__ss_object, self);
        p = (PyObject *)self;
    }
    Py_INCREF(p);
    return p;
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace

namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__FunctionCaller__::__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (FunctionCaller expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__FunctionCaller__::__ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObject *)p)->__ss_object;
}
}
