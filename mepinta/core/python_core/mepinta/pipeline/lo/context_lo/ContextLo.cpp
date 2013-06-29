#include "builtin.hpp"
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
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
namespace __context_lo__ {
namespace __ContextLo__ {

str *const_0, *const_1, *const_2, *const_3;

using __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType;
using __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction;

str *__name__;



/**
class ContextLo
*/

class_ *cl_ContextLo;

void *ContextLo::__init__() {
    dict<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *> *__59;
    dict<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction *> *__60;

    this->data_types = (new dict<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *>());
    this->data_types_paths = (new dict<str *, void *>());
    this->functions = (new dict<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction *>());
    this->processors_paths = (new dict<str *, void *>());
    this->data_types->__setitem__(0, (new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType(const_0, NULL)));
    this->functions->__setitem__(0, (new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction(const_1, NULL)));
    this->data_type_aliases = (new dict<str *, list<str *> *>());
    return NULL;
}

void *ContextLo::appendDataTypeAlias(str *data_type_name, str *data_type_alias) {
    dict<str *, list<str *> *> *__61;

    if ((!(this->data_type_aliases)->__contains__(data_type_name))) {
        this->data_type_aliases->__setitem__(data_type_name, (new list<str *>()));
    }
    ((this->data_type_aliases)->__getitem__(data_type_name))->append(data_type_alias);
    return NULL;
}

ContextLo *shedskin_ContextLo() {
    ContextLo *context_lo;

    context_lo = (new ContextLo(1));
    context_lo->appendDataTypeAlias(const_2, const_3);
    return context_lo;
}

void __init() {
    const_0 = new str("Zero_Data_Type");
    const_1 = new str("Zero_Function");
    const_2 = new str("int");
    const_3 = new str("int32_t");

    __name__ = new str("ContextLo");

    cl_ContextLo = new class_("ContextLo");
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
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include <structmember.h>
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_context_lo_ContextLo;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __context_lo__ { /* XXX */
namespace __ContextLo__ { /* XXX */

/* class ContextLo */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *__ss_object;
} __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject;

static PyMemberDef __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)self)->__ss_object->__init__());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_appendDataTypeAlias(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("data_type_name", 0, 0, 0, args, kwargs);
        str *arg_1 = __ss_arg<str *>("data_type_alias", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)self)->__ss_object->appendDataTypeAlias(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"appendDataTypeAlias", (PyCFunction)__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_appendDataTypeAlias, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *self = (__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::cl_ContextLo;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoDealloc(__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_functions(__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *self, void *closure) {
    return __to_py(self->__ss_object->functions);
}

int __ss_set___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_functions(__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->functions = __to_ss<dict<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction *> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_processors_paths(__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *self, void *closure) {
    return __to_py(self->__ss_object->processors_paths);
}

int __ss_set___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_processors_paths(__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->processors_paths = __to_ss<dict<str *, void *> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_data_types(__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *self, void *closure) {
    return __to_py(self->__ss_object->data_types);
}

int __ss_set___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_data_types(__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->data_types = __to_ss<dict<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_data_type_aliases(__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *self, void *closure) {
    return __to_py(self->__ss_object->data_type_aliases);
}

int __ss_set___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_data_type_aliases(__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->data_type_aliases = __to_ss<dict<str *, list<str *> *> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_data_types_paths(__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *self, void *closure) {
    return __to_py(self->__ss_object->data_types_paths);
}

int __ss_set___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_data_types_paths(__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->data_types_paths = __to_ss<dict<str *, void *> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoGetSet[] = {
    {(char *)"functions", (getter)__ss_get___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_functions, (setter)__ss_set___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_functions, (char *)"", NULL},
    {(char *)"processors_paths", (getter)__ss_get___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_processors_paths, (setter)__ss_set___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_processors_paths, (char *)"", NULL},
    {(char *)"data_types", (getter)__ss_get___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_data_types, (setter)__ss_set___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_data_types, (char *)"", NULL},
    {(char *)"data_type_aliases", (getter)__ss_get___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_data_type_aliases, (setter)__ss_set___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_data_type_aliases, (char *)"", NULL},
    {(char *)"data_types_paths", (getter)__ss_get___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_data_types_paths, (setter)__ss_set___ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_data_types_paths, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "ContextLo.ContextLo",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_context_lo_ContextLo, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(5);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)self)->__ss_object->functions));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)self)->__ss_object->processors_paths));
    PyTuple_SetItem(b, 2, __to_py(((__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)self)->__ss_object->data_types));
    PyTuple_SetItem(b, 3, __to_py(((__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)self)->__ss_object->data_type_aliases));
    PyTuple_SetItem(b, 4, __to_py(((__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)self)->__ss_object->data_types_paths));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLo__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)self)->__ss_object->functions = __to_ss<dict<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction *> *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)self)->__ss_object->processors_paths = __to_ss<dict<str *, void *> *>(PyTuple_GetItem(state, 1));
    ((__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)self)->__ss_object->data_types = __to_ss<dict<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *> *>(PyTuple_GetItem(state, 2));
    ((__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)self)->__ss_object->data_type_aliases = __to_ss<dict<str *, list<str *> *> *>(PyTuple_GetItem(state, 3));
    ((__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)self)->__ss_object->data_types_paths = __to_ss<dict<str *, void *> *>(PyTuple_GetItem(state, 4));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __context_lo__
} // namespace __ContextLo__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __context_lo__ { /* XXX */
namespace __ContextLo__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_context_lo_ContextLo_shedskin_ContextLo(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(__ContextLo__::shedskin_ContextLo());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_context_lo_ContextLo_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_context_lo_ContextLoMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_ContextLo", (PyCFunction)Global_mepinta_pipeline_lo_context_lo_ContextLo_shedskin_ContextLo, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_context_lo_ContextLo(void) {

    __ss_mod_mepinta_pipeline_lo_context_lo_ContextLo = Py_InitModule((char *)"ContextLo", Global_mepinta_pipeline_lo_context_lo_ContextLoMethods);
    if(!__ss_mod_mepinta_pipeline_lo_context_lo_ContextLo)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_context_lo_ContextLo, "ContextLo", (PyObject *)&__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_context_lo_ContextLo(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __context_lo__

} // namespace __ContextLo__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __context_lo__ { /* XXX */
namespace __ContextLo__ { /* XXX */

PyObject *ContextLo::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *self = (__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)(__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (ContextLo expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::__ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObject *)p)->__ss_object;
}
}
