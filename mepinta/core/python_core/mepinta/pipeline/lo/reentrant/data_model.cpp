#include "builtin.hpp"
#include "copy.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/reentrant/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"

/**
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo

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
namespace __reentrant__ {
namespace __data_model__ {


str *__name__;



/**
class ProcessorContext
*/

class_ *cl_ProcessorContext;

void *ProcessorContext::__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *pline_evaluator) {
    
    this->context_lo = context_lo;
    this->pline = pline;
    this->pline_evaluator = pline_evaluator;
    return NULL;
}

ProcessorContext *shedskin_reentrant_data_model(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *pline_evaluator) {
    ProcessorContext *processor_context;

    processor_context = (new ProcessorContext(context_lo, pline, pline_evaluator));
    return processor_context;
}

void __init() {
    __name__ = new str("data_model");

    cl_ProcessorContext = new class_("ProcessorContext");
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "copy.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/reentrant/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include <structmember.h>
#include "copy.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/reentrant/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_reentrant_data_model;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __reentrant__ { /* XXX */
namespace __data_model__ { /* XXX */

/* class ProcessorContext */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *__ss_object;
} __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject;

static PyMemberDef __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *>("pline_evaluator", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *)self)->__ss_object->__init__(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *self = (__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::cl_ProcessorContext;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextDealloc(__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_pline(__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *self, void *closure) {
    return __to_py(self->__ss_object->pline);
}

int __ss_set___ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_pline(__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->pline = __to_ss<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_pline_evaluator(__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *self, void *closure) {
    return __to_py(self->__ss_object->pline_evaluator);
}

int __ss_set___ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_pline_evaluator(__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->pline_evaluator = __to_ss<__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_context_lo(__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *self, void *closure) {
    return __to_py(self->__ss_object->context_lo);
}

int __ss_set___ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_context_lo(__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextGetSet[] = {
    {(char *)"pline", (getter)__ss_get___ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_pline, (setter)__ss_set___ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_pline, (char *)"", NULL},
    {(char *)"pline_evaluator", (getter)__ss_get___ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_pline_evaluator, (setter)__ss_set___ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_pline_evaluator, (char *)"", NULL},
    {(char *)"context_lo", (getter)__ss_get___ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_context_lo, (setter)__ss_set___ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_context_lo, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "data_model.ProcessorContext",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_reentrant_data_model, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(3);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *)self)->__ss_object->pline));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *)self)->__ss_object->pline_evaluator));
    PyTuple_SetItem(b, 2, __to_py(((__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *)self)->__ss_object->context_lo));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContext__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *)self)->__ss_object->pline = __to_ss<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *)self)->__ss_object->pline_evaluator = __to_ss<__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *>(PyTuple_GetItem(state, 1));
    ((__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *)self)->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(PyTuple_GetItem(state, 2));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __reentrant__
} // namespace __data_model__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __reentrant__ { /* XXX */
namespace __data_model__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_reentrant_data_model_shedskin_reentrant_data_model(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *>("pline_evaluator", 2, 0, 0, args, kwargs);

        return __to_py(__data_model__::shedskin_reentrant_data_model(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_reentrant_data_model_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_reentrant_data_modelMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_reentrant_data_model", (PyCFunction)Global_mepinta_pipeline_lo_reentrant_data_model_shedskin_reentrant_data_model, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_reentrant_data_model(void) {

    __ss_mod_mepinta_pipeline_lo_reentrant_data_model = Py_InitModule((char *)"data_model", Global_mepinta_pipeline_lo_reentrant_data_modelMethods);
    if(!__ss_mod_mepinta_pipeline_lo_reentrant_data_model)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_reentrant_data_model, "ProcessorContext", (PyObject *)&__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_reentrant_data_model(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __reentrant__

} // namespace __data_model__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __reentrant__ { /* XXX */
namespace __data_model__ { /* XXX */

PyObject *ProcessorContext::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *self = (__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *)(__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObjectType, 0));
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
} // module namespace

namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (ProcessorContext expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::__ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObject *)p)->__ss_object;
}
}
