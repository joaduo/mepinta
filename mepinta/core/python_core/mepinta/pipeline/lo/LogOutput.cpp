#include "builtin.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "pipeline_backend/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/lo/LogOutput.hpp"

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
namespace __LogOutput__ {

str *const_0;

using __pipeline_backend__::__logging__::__logging__::logCritical;
using __pipeline_backend__::__logging__::__logging__::logDebug;
using __pipeline_backend__::__logging__::__logging__::logError;
using __pipeline_backend__::__logging__::__logging__::logInfo;
using __pipeline_backend__::__logging__::__logging__::logWarning;
using __pipeline_backend__::__logging__::__logging__::logVerbose;
using __pipeline_backend__::__logging__::__logging__::setLogLevel;

str *__name__;



/**
class LogOutput
*/

class_ *cl_LogOutput;

void *LogOutput::info(str *msg) {
    
    logInfo(msg);
    return NULL;
}

void *LogOutput::verbose(str *msg) {
    
    logVerbose(msg);
    return NULL;
}

void *LogOutput::setLevel(__ss_int level) {
    
    setLogLevel(level);
    return NULL;
}

void *LogOutput::critical(str *msg) {
    
    logCritical(msg);
    return NULL;
}

void *LogOutput::error(str *msg) {
    
    logError(msg);
    return NULL;
}

void *LogOutput::debug(str *msg) {
    
    logDebug(msg);
    return NULL;
}

void *LogOutput::warning(str *msg) {
    
    logWarning(msg);
    return NULL;
}

void *shedskin_LogOutput() {
    LogOutput *lo;
    str *msg;

    lo = (new LogOutput());
    msg = const_0;
    lo->setLevel(0);
    lo->critical(msg);
    lo->debug(msg);
    lo->error(msg);
    lo->info(msg);
    lo->warning(msg);
    lo->verbose(msg);
    lo->setLevel(1);
    return NULL;
}

void __init() {
    const_0 = new str("Log message");

    __name__ = new str("LogOutput");

    cl_LogOutput = new class_("LogOutput");
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "pipeline_backend/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/lo/LogOutput.hpp"
#include <structmember.h>
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "pipeline_backend/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/lo/LogOutput.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_LogOutput;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __LogOutput__ { /* XXX */

/* class LogOutput */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__LogOutput__::LogOutput *__ss_object;
} __ss_mepinta_pipeline_lo_LogOutput_LogOutputObject;

static PyMemberDef __ss_mepinta_pipeline_lo_LogOutput_LogOutputMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_LogOutput_LogOutput_info(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("msg", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_LogOutput_LogOutputObject *)self)->__ss_object->info(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_LogOutput_LogOutput_verbose(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("msg", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_LogOutput_LogOutputObject *)self)->__ss_object->verbose(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_LogOutput_LogOutput_setLevel(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("level", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_LogOutput_LogOutputObject *)self)->__ss_object->setLevel(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_LogOutput_LogOutput_critical(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("msg", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_LogOutput_LogOutputObject *)self)->__ss_object->critical(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_LogOutput_LogOutput_error(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("msg", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_LogOutput_LogOutputObject *)self)->__ss_object->error(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_LogOutput_LogOutput_debug(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("msg", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_LogOutput_LogOutputObject *)self)->__ss_object->debug(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_LogOutput_LogOutput_warning(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("msg", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_LogOutput_LogOutputObject *)self)->__ss_object->warning(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_LogOutput_LogOutput_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_LogOutput_LogOutput__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_LogOutput_LogOutput__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_LogOutput_LogOutputMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_LogOutput_LogOutput__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_LogOutput_LogOutput__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"info", (PyCFunction)__ss_mepinta_pipeline_lo_LogOutput_LogOutput_info, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"verbose", (PyCFunction)__ss_mepinta_pipeline_lo_LogOutput_LogOutput_verbose, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"setLevel", (PyCFunction)__ss_mepinta_pipeline_lo_LogOutput_LogOutput_setLevel, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"critical", (PyCFunction)__ss_mepinta_pipeline_lo_LogOutput_LogOutput_critical, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"error", (PyCFunction)__ss_mepinta_pipeline_lo_LogOutput_LogOutput_error, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"debug", (PyCFunction)__ss_mepinta_pipeline_lo_LogOutput_LogOutput_debug, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"warning", (PyCFunction)__ss_mepinta_pipeline_lo_LogOutput_LogOutput_warning, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_LogOutput_LogOutputNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_LogOutput_LogOutputObject *self = (__ss_mepinta_pipeline_lo_LogOutput_LogOutputObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__LogOutput__::LogOutput();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__LogOutput__::cl_LogOutput;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_LogOutput_LogOutputDealloc(__ss_mepinta_pipeline_lo_LogOutput_LogOutputObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyGetSetDef __ss_mepinta_pipeline_lo_LogOutput_LogOutputGetSet[] = {
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_LogOutput_LogOutputObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "LogOutput.LogOutput",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_LogOutput_LogOutputObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_LogOutput_LogOutputDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_LogOutput_LogOutput_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_LogOutput_LogOutputMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_LogOutput_LogOutputMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_LogOutput_LogOutputGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    0,              /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_LogOutput_LogOutputNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_LogOutput_LogOutput__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_LogOutput, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_LogOutput_LogOutputObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_LogOutput_LogOutputObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(0);
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_LogOutput_LogOutput__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __LogOutput__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __LogOutput__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_LogOutput_shedskin_LogOutput(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(__LogOutput__::shedskin_LogOutput());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_LogOutput_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_LogOutputMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_LogOutput", (PyCFunction)Global_mepinta_pipeline_lo_LogOutput_shedskin_LogOutput, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_LogOutput(void) {

    __ss_mod_mepinta_pipeline_lo_LogOutput = Py_InitModule((char *)"LogOutput", Global_mepinta_pipeline_lo_LogOutputMethods);
    if(!__ss_mod_mepinta_pipeline_lo_LogOutput)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_LogOutput_LogOutputObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_LogOutput, "LogOutput", (PyObject *)&__ss_mepinta_pipeline_lo_LogOutput_LogOutputObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_LogOutput(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __LogOutput__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __LogOutput__ { /* XXX */

PyObject *LogOutput::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_LogOutput_LogOutputObject *self = (__ss_mepinta_pipeline_lo_LogOutput_LogOutputObject *)(__ss_mepinta_pipeline_lo_LogOutput_LogOutputObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_LogOutput_LogOutputObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__LogOutput__::LogOutput *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__LogOutput__::__ss_mepinta_pipeline_lo_LogOutput_LogOutputObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (LogOutput expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__LogOutput__::__ss_mepinta_pipeline_lo_LogOutput_LogOutputObject *)p)->__ss_object;
}
}
