#include "builtin.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"

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
namespace __generic_data__ {
namespace __BiDirectedGraph__ {

str *const_0;

using __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph;
using __pipeline_backend__::__logging__::__logging__::logDebug;

str *__name__;



/**
class BiDirectedGraph
*/

class_ *cl_BiDirectedGraph;

void *BiDirectedGraph::disconnect(__ss_int dent_id, __ss_int dency_id) {
    
    if ((this->dpdencies)->has(dent_id, dency_id)) {
        (this->dpdencies)->remove(dent_id, dency_id);
        (this->dpdents)->remove(dency_id, dent_id);
    }
    return NULL;
}

list<__ss_int> *BiDirectedGraph::disconnectAll(__ss_int prop_id) {
    
    this->disconnectDpdencies(prop_id);
    return this->disconnectDpdents(prop_id);
}

str *BiDirectedGraph::__str__() {
    
    return (this->dpdencies)->__str__();
}

__ss_int BiDirectedGraph::__len__() {
    
    return len(this->dpdencies);
}

void *BiDirectedGraph::disconnectDpdencies(__ss_int dent_id) {
    __iter<__ss_int> *__29;
    list<__ss_int> *__28;
    __ss_int __30, dency_id;
    list<__ss_int>::for_in_loop __31;

    logDebug(__modct(const_0, 1, ___box(dent_id)));

    FOR_IN(dency_id,(this->dpdencies)->__getitem__(dent_id),28,30,31)
        (this->dpdents)->remove(dency_id, dent_id);
    END_FOR

    (this->dpdencies)->__delitem__(dent_id);
    return NULL;
}

void *BiDirectedGraph::connect(__ss_int dent_id, __ss_int dency_id) {
    
    if (__NOT((this->dpdencies)->has(dent_id, dency_id))) {
        (this->dpdencies)->add(dent_id, dency_id);
        (this->dpdents)->add(dency_id, dent_id);
    }
    return NULL;
}

list<__ss_int> *BiDirectedGraph::disconnectDpdents(__ss_int dency_id) {
    __iter<__ss_int> *__33;
    list<__ss_int> *__32, *dents_ids;
    __ss_int __34, dent_id;
    list<__ss_int>::for_in_loop __35;

    dents_ids = (this->dpdents)->__getitem__(dency_id);
    logDebug(__modct(const_0, 1, ___box(dency_id)));

    FOR_IN(dent_id,dents_ids,32,34,35)
        (this->dpdencies)->remove(dent_id, dency_id);
    END_FOR

    (this->dpdents)->__delitem__(dency_id);
    return dents_ids;
}

void *BiDirectedGraph::__init__() {
    
    this->dpdencies = (new __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph(1));
    this->dpdents = (new __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph(1));
    return NULL;
}

BiDirectedGraph *BiDirectedGraph::__deepcopy__(dict<void *, pyobj *> *memo) {
    BiDirectedGraph *c = new BiDirectedGraph();
    memo->__setitem__(this, c);
    c->dpdents = __deepcopy(dpdents);
    c->dpdencies = __deepcopy(dpdencies);
    return c;
}

void *shedskin_BiDirectedGraph() {
    __ss_int dency_id, dent_id;
    BiDirectedGraph *bdg;

    bdg = (new BiDirectedGraph(1));
    dent_id = 1;
    dency_id = 2;
    bdg->connect(dent_id, dency_id);
    bdg->disconnect(dent_id, dency_id);
    bdg->disconnectDpdencies(dent_id);
    bdg->disconnectDpdencies(dent_id);
    bdg->disconnectAll(1);
    bdg->__str__();
    bdg->__len__();
    return NULL;
}

void __init() {
    const_0 = new str("Disconnecting property: %s");

    __name__ = new str("BiDirectedGraph");

    cl_BiDirectedGraph = new class_("BiDirectedGraph");
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include <structmember.h>
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_generic_data_BiDirectedGraph;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __generic_data__ { /* XXX */
namespace __BiDirectedGraph__ { /* XXX */

/* class BiDirectedGraph */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__generic_data__::__BiDirectedGraph__::BiDirectedGraph *__ss_object;
} __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject;

static PyMemberDef __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_disconnect(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dent_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("dency_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)self)->__ss_object->disconnect(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_disconnectAll(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("prop_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)self)->__ss_object->disconnectAll(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph___str__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)self)->__ss_object->__str__());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph___len__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)self)->__ss_object->__len__());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_disconnectDpdencies(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dent_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)self)->__ss_object->disconnectDpdencies(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_connect(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dent_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("dency_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)self)->__ss_object->connect(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_disconnectDpdents(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dency_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)self)->__ss_object->disconnectDpdents(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)self)->__ss_object->__init__());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"disconnect", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_disconnect, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"disconnectAll", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_disconnectAll, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__str__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph___str__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__len__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph___len__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"disconnectDpdencies", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_disconnectDpdencies, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"connect", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_connect, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"disconnectDpdents", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_disconnectDpdents, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *self = (__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__generic_data__::__BiDirectedGraph__::BiDirectedGraph();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__generic_data__::__BiDirectedGraph__::cl_BiDirectedGraph;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphDealloc(__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_dpdents(__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *self, void *closure) {
    return __to_py(self->__ss_object->dpdents);
}

int __ss_set___ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_dpdents(__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->dpdents = __to_ss<__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_dpdencies(__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *self, void *closure) {
    return __to_py(self->__ss_object->dpdencies);
}

int __ss_set___ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_dpdencies(__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->dpdencies = __to_ss<__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphGetSet[] = {
    {(char *)"dpdents", (getter)__ss_get___ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_dpdents, (setter)__ss_set___ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_dpdents, (char *)"", NULL},
    {(char *)"dpdencies", (getter)__ss_get___ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_dpdencies, (setter)__ss_set___ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_dpdencies, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "BiDirectedGraph.BiDirectedGraph",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph_as_number,  /* tp_as_number      */
    0,              /* tp_as_sequence    */
    0,              /* tp_as_mapping     */
    0,              /* tp_hash           */
    0,              /* tp_call           */
    (PyObject *(*)(PyObject *))__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph___str__, /* tp_str           */
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
    __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_generic_data_BiDirectedGraph, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(2);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)self)->__ss_object->dpdents));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)self)->__ss_object->dpdencies));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraph__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)self)->__ss_object->dpdents = __to_ss<__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)self)->__ss_object->dpdencies = __to_ss<__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *>(PyTuple_GetItem(state, 1));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __generic_data__
} // namespace __BiDirectedGraph__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __generic_data__ { /* XXX */
namespace __BiDirectedGraph__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_generic_data_BiDirectedGraph_shedskin_BiDirectedGraph(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(__BiDirectedGraph__::shedskin_BiDirectedGraph());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_generic_data_BiDirectedGraph_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_generic_data_BiDirectedGraphMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_BiDirectedGraph", (PyCFunction)Global_mepinta_pipeline_lo_generic_data_BiDirectedGraph_shedskin_BiDirectedGraph, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_generic_data_BiDirectedGraph(void) {

    __ss_mod_mepinta_pipeline_lo_generic_data_BiDirectedGraph = Py_InitModule((char *)"BiDirectedGraph", Global_mepinta_pipeline_lo_generic_data_BiDirectedGraphMethods);
    if(!__ss_mod_mepinta_pipeline_lo_generic_data_BiDirectedGraph)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_generic_data_BiDirectedGraph, "BiDirectedGraph", (PyObject *)&__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_generic_data_BiDirectedGraph(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __generic_data__

} // namespace __BiDirectedGraph__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __generic_data__ { /* XXX */
namespace __BiDirectedGraph__ { /* XXX */

PyObject *BiDirectedGraph::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *self = (__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)(__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__generic_data__::__BiDirectedGraph__::BiDirectedGraph *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__generic_data__::__BiDirectedGraph__::__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (BiDirectedGraph expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__generic_data__::__BiDirectedGraph__::__ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObject *)p)->__ss_object;
}
}
