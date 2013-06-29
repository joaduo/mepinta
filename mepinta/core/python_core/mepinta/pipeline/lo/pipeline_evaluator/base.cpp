#include "builtin.hpp"
#include "copy.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"

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
namespace __pipeline_evaluator__ {
namespace __base__ {

str *const_0;

using __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller;
using __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager;

str *__name__;



/**
class PipelineEvaluatorBase
*/

class_ *cl_PipelineEvaluatorBase;

tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *PipelineEvaluatorBase::evaluateProp(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id) {
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop;

    prop = (pline->all_properties)->__getitem__(prop_id);
    return (new tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>(2,prop_id,prop));
}

void *PipelineEvaluatorBase::__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
    
    this->context_lo = context_lo;
    this->p_value_mngr = (new __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager(context_lo));
    this->func_caller = (new __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller());
    return NULL;
}

PipelineEvaluatorBase *shedskin_PipelineEvaluatorBase(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    PipelineEvaluatorBase *pe;

    pe = (new PipelineEvaluatorBase(context_lo));
    return pe;
}

void __init() {
    const_0 = new str("__main__");

    __name__ = new str("base");

    cl_PipelineEvaluatorBase = new class_("PipelineEvaluatorBase");
    if (__eq(__name__, const_0)) {
    }
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
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include <structmember.h>
#include "copy.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_base;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __base__ { /* XXX */

/* class PipelineEvaluatorBase */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *__ss_object;
} __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject;

static PyMemberDef __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_evaluateProp(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("prop_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *)self)->__ss_object->evaluateProp(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *)self)->__ss_object->__init__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"evaluateProp", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_evaluateProp, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *self = (__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::cl_PipelineEvaluatorBase;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseDealloc(__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_func_caller(__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *self, void *closure) {
    return __to_py(self->__ss_object->func_caller);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_func_caller(__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->func_caller = __to_ss<__mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_p_value_mngr(__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *self, void *closure) {
    return __to_py(self->__ss_object->p_value_mngr);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_p_value_mngr(__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->p_value_mngr = __to_ss<__mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_context_lo(__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *self, void *closure) {
    return __to_py(self->__ss_object->context_lo);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_context_lo(__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseGetSet[] = {
    {(char *)"func_caller", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_func_caller, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_func_caller, (char *)"", NULL},
    {(char *)"p_value_mngr", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_p_value_mngr, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_p_value_mngr, (char *)"", NULL},
    {(char *)"context_lo", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_context_lo, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_context_lo, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "base.PipelineEvaluatorBase",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_base, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(3);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *)self)->__ss_object->func_caller));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *)self)->__ss_object->p_value_mngr));
    PyTuple_SetItem(b, 2, __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *)self)->__ss_object->context_lo));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBase__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *)self)->__ss_object->func_caller = __to_ss<__mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *)self)->__ss_object->p_value_mngr = __to_ss<__mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *>(PyTuple_GetItem(state, 1));
    ((__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *)self)->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(PyTuple_GetItem(state, 2));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __pipeline_evaluator__
} // namespace __base__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __base__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_pipeline_evaluator_base_shedskin_PipelineEvaluatorBase(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 2, 0, 0, args, kwargs);

        return __to_py(__base__::shedskin_PipelineEvaluatorBase(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_pipeline_evaluator_base_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_pipeline_evaluator_baseMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_PipelineEvaluatorBase", (PyCFunction)Global_mepinta_pipeline_lo_pipeline_evaluator_base_shedskin_PipelineEvaluatorBase, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_evaluator_base(void) {

    __ss_mod_mepinta_pipeline_lo_pipeline_evaluator_base = Py_InitModule((char *)"base", Global_mepinta_pipeline_lo_pipeline_evaluator_baseMethods);
    if(!__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_base)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_base, "PipelineEvaluatorBase", (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_evaluator_base(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __pipeline_evaluator__

} // namespace __base__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __base__ { /* XXX */

PyObject *PipelineEvaluatorBase::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *self = (__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *)(__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (PipelineEvaluatorBase expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObject *)p)->__ss_object;
}
}
