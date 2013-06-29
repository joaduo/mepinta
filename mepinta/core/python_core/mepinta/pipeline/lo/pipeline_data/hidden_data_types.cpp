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
namespace __pipeline_data__ {
namespace __hidden_data_types__ {

str *const_0;


str *__name__;



/**
class FunctionPropertyValue
*/

class_ *cl_FunctionPropertyValue;

void *FunctionPropertyValue::__init__(__ss_int func_id) {
    
    this->func_id = func_id;
    this->args = NULL;
    return NULL;
}


/**
class FunctumPropertyValue
*/

class_ *cl_FunctumPropertyValue;

__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *FunctumPropertyValue::getFunctumProp() {
    
    return this->functum_prop;
}

void *FunctumPropertyValue::setFunctumProp(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *functum_prop) {
    
    this->functum_prop = functum_prop;
    return NULL;
}

void *FunctumPropertyValue::__init__(__ss_int func_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *functum_prop) {
    
    FunctionPropertyValue::__init__(func_id);
    this->functum_prop = functum_prop;
    return NULL;
}

FunctionPropertyValue *shedskin_hidden_data_types(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    FunctumPropertyValue *fumpv;
    __ss_int func_id;
    FunctionPropertyValue *fpv;

    func_id = 100;
    fpv = (new FunctionPropertyValue(func_id));
    fumpv = (new FunctumPropertyValue(func_id, prop));
    fumpv->setFunctumProp(prop);
    fumpv->getFunctumProp();
    return fpv;
}

void __init() {
    const_0 = new str("__main__");

    __name__ = new str("hidden_data_types");

    cl_FunctionPropertyValue = new class_("FunctionPropertyValue");
    cl_FunctumPropertyValue = new class_("FunctumPropertyValue");
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
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_pipeline_data_hidden_data_types;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __hidden_data_types__ { /* XXX */

/* class FunctionPropertyValue */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *__ss_object;
} __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject;

static PyMemberDef __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("func_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *)self)->__ss_object->__init__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::cl_FunctionPropertyValue;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueDealloc(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue_args(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *self, void *closure) {
    return __to_py(self->__ss_object->args);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue_args(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->args = NULL;
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue_func_id(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *self, void *closure) {
    return __to_py(self->__ss_object->func_id);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue_func_id(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->func_id = __to_ss<__ss_int >(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueGetSet[] = {
    {(char *)"args", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue_args, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue_args, (char *)"", NULL},
    {(char *)"func_id", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue_func_id, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue_func_id, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "hidden_data_types.FunctionPropertyValue",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_pipeline_data_hidden_data_types, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(2);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *)self)->__ss_object->args));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *)self)->__ss_object->func_id));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValue__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *)self)->__ss_object->args = __to_ss<void *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *)self)->__ss_object->func_id = __to_ss<__ss_int >(PyTuple_GetItem(state, 1));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __pipeline_data__
} // namespace __hidden_data_types__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __hidden_data_types__ { /* XXX */

/* class FunctumPropertyValue */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue *__ss_object;
} __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject;

static PyMemberDef __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_getFunctumProp(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *)self)->__ss_object->getFunctumProp());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_setFunctumProp(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("functum_prop", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *)self)->__ss_object->setFunctumProp(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("func_id", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("functum_prop", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *)self)->__ss_object->__init__(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getFunctumProp", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_getFunctumProp, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"setFunctumProp", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_setFunctumProp, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::cl_FunctumPropertyValue;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueDealloc(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_args(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *self, void *closure) {
    return __to_py(self->__ss_object->args);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_args(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->args = NULL;
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_functum_prop(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *self, void *closure) {
    return __to_py(self->__ss_object->functum_prop);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_functum_prop(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->functum_prop = __to_ss<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_func_id(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *self, void *closure) {
    return __to_py(self->__ss_object->func_id);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_func_id(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->func_id = __to_ss<__ss_int >(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueGetSet[] = {
    {(char *)"args", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_args, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_args, (char *)"", NULL},
    {(char *)"functum_prop", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_functum_prop, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_functum_prop, (char *)"", NULL},
    {(char *)"func_id", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_func_id, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_func_id, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "hidden_data_types.FunctumPropertyValue",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueGetSet,       /* tp_getset         */
    &__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObjectType,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_pipeline_data_hidden_data_types, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(3);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *)self)->__ss_object->args));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *)self)->__ss_object->functum_prop));
    PyTuple_SetItem(b, 2, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *)self)->__ss_object->func_id));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValue__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *)self)->__ss_object->args = __to_ss<void *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *)self)->__ss_object->functum_prop = __to_ss<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>(PyTuple_GetItem(state, 1));
    ((__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *)self)->__ss_object->func_id = __to_ss<__ss_int >(PyTuple_GetItem(state, 2));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __pipeline_data__
} // namespace __hidden_data_types__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __hidden_data_types__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_pipeline_data_hidden_data_types_shedskin_hidden_data_types(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 0, 0, 0, args, kwargs);

        return __to_py(__hidden_data_types__::shedskin_hidden_data_types(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_pipeline_data_hidden_data_types_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_pipeline_data_hidden_data_typesMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_hidden_data_types", (PyCFunction)Global_mepinta_pipeline_lo_pipeline_data_hidden_data_types_shedskin_hidden_data_types, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_data_hidden_data_types(void) {

    __ss_mod_mepinta_pipeline_lo_pipeline_data_hidden_data_types = Py_InitModule((char *)"hidden_data_types", Global_mepinta_pipeline_lo_pipeline_data_hidden_data_typesMethods);
    if(!__ss_mod_mepinta_pipeline_lo_pipeline_data_hidden_data_types)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_data_hidden_data_types, "FunctionPropertyValue", (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObjectType);
    if (PyType_Ready(&__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_data_hidden_data_types, "FunctumPropertyValue", (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_data_hidden_data_types(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __pipeline_data__

} // namespace __hidden_data_types__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __hidden_data_types__ { /* XXX */

PyObject *FunctionPropertyValue::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *)(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (FunctionPropertyValue expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObject *)p)->__ss_object;
}
}
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __hidden_data_types__ { /* XXX */

PyObject *FunctumPropertyValue::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *)(__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (FunctumPropertyValue expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::__ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObject *)p)->__ss_object;
}
}
