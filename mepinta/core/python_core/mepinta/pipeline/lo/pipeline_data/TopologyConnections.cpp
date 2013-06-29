#include "builtin.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "pipeline_backend/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"

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
namespace __TopologyConnections__ {

str *const_0, *const_1;

using __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph;
using __pipeline_backend__::__logging__::__logging__::logDebug;
using __mepinta__::__pipeline__::__lo__::__generic_data__::__BiDirectedGraph__::BiDirectedGraph;

str *__name__;



/**
class TopologyConnections
*/

class_ *cl_TopologyConnections;

void *TopologyConnections::disconnect(__ss_int dent_id, __ss_int dency_id) {
    
    (this->navigation)->disconnect(dent_id, dency_id);
    if ((this->dpdencies)->has(dent_id, dency_id)) {
        (this->dpdencies)->remove(dent_id, dency_id);
    }
    if ((this->dpdents)->has(dency_id, dent_id)) {
        (this->dpdents)->remove(dency_id, dent_id);
    }
    return NULL;
}

list<__ss_int> *TopologyConnections::disconnectAll(__ss_int prop_id) {
    
    this->disconnectDpdencies(prop_id);
    return this->disconnectDpdents(prop_id);
}

void *TopologyConnections::connectDency(__ss_int dent_id, __ss_int dency_id) {
    
    (this->navigation)->connect(dent_id, dency_id);
    if (__NOT((this->dpdencies)->has(dent_id, dency_id))) {
        (this->dpdencies)->add(dent_id, dency_id);
    }
    return NULL;
}

str *TopologyConnections::__str__() {
    
    return __modct(const_0, 3, (this->__class__)->__name__, this->dpdencies, this->dpdents);
}

__ss_int TopologyConnections::__len__() {
    
    return len(this->navigation);
}

void *TopologyConnections::disconnectDpdencies(__ss_int dent_id) {
    __iter<__ss_int> *__37;
    list<__ss_int> *__36;
    __ss_int __38, dency_id;
    list<__ss_int>::for_in_loop __39;

    (this->navigation)->disconnectDpdencies(dent_id);
    logDebug(__modct(const_1, 1, ___box(dent_id)));

    FOR_IN(dency_id,(this->dpdencies)->__getitem__(dent_id),36,38,39)
        if ((this->dpdents)->has(dency_id, dent_id)) {
            (this->dpdents)->remove(dency_id, dent_id);
        }
    END_FOR

    (this->dpdencies)->__delitem__(dent_id);
    return NULL;
}

void *TopologyConnections::connect(__ss_int dent_id, __ss_int dency_id) {
    
    (this->navigation)->connect(dent_id, dency_id);
    if (__NOT((this->dpdencies)->has(dent_id, dency_id))) {
        (this->dpdencies)->add(dent_id, dency_id);
    }
    if (__NOT((this->dpdents)->has(dency_id, dent_id))) {
        (this->dpdents)->add(dency_id, dent_id);
    }
    return NULL;
}

list<__ss_int> *TopologyConnections::disconnectDpdents(__ss_int dency_id) {
    __iter<__ss_int> *__41;
    list<__ss_int> *__40, *dents_ids;
    __ss_int __42, dent_id;
    list<__ss_int>::for_in_loop __43;

    (this->navigation)->disconnectDpdents(dency_id);
    dents_ids = (this->dpdents)->__getitem__(dency_id);
    logDebug(__modct(const_1, 1, ___box(dency_id)));

    FOR_IN(dent_id,dents_ids,40,42,43)
        if ((this->dpdencies)->has(dent_id, dency_id)) {
            (this->dpdencies)->remove(dent_id, dency_id);
        }
    END_FOR

    (this->dpdents)->__delitem__(dency_id);
    return dents_ids;
}

void *TopologyConnections::connectDent(__ss_int dent_id, __ss_int dency_id) {
    
    (this->navigation)->connect(dent_id, dency_id);
    if (__NOT((this->dpdents)->has(dency_id, dent_id))) {
        (this->dpdents)->add(dency_id, dent_id);
    }
    return NULL;
}

void *TopologyConnections::__init__() {
    
    this->navigation = (new __mepinta__::__pipeline__::__lo__::__generic_data__::__BiDirectedGraph__::BiDirectedGraph(1));
    this->dpdencies = (new __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph(1));
    this->dpdents = (new __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph(1));
    return NULL;
}

TopologyConnections *TopologyConnections::__deepcopy__(dict<void *, pyobj *> *memo) {
    TopologyConnections *c = new TopologyConnections();
    memo->__setitem__(this, c);
    c->dpdents = __deepcopy(dpdents);
    c->dpdencies = __deepcopy(dpdencies);
    c->navigation = __deepcopy(navigation);
    return c;
}

void *shedskin_TopologyConnections() {
    __ss_int dency_id, dent_id;
    TopologyConnections *cbdg;

    cbdg = (new TopologyConnections(1));
    dent_id = 1;
    dency_id = 2;
    cbdg->connectDency(dent_id, dency_id);
    cbdg->connectDent(dent_id, dency_id);
    cbdg->connect(dent_id, dency_id);
    cbdg->disconnect(dent_id, dency_id);
    cbdg->disconnectDpdencies(dent_id);
    cbdg->disconnectDpdencies(dent_id);
    cbdg->disconnectAll(1);
    cbdg->__str__();
    cbdg->__len__();
    return NULL;
}

void __init() {
    const_0 = new str("%s: Dents %s | Dencies %s");
    const_1 = new str("Disconnecting property: %s");

    __name__ = new str("TopologyConnections");

    cl_TopologyConnections = new class_("TopologyConnections");
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "pipeline_backend/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include <structmember.h>
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "pipeline_backend/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_pipeline_data_TopologyConnections;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __TopologyConnections__ { /* XXX */

/* class TopologyConnections */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__TopologyConnections__::TopologyConnections *__ss_object;
} __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject;

static PyMemberDef __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_disconnect(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dent_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("dency_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->disconnect(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_disconnectAll(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("prop_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->disconnectAll(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_connectDency(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dent_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("dency_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->connectDency(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections___str__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->__str__());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections___len__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->__len__());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_disconnectDpdencies(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dent_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->disconnectDpdencies(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_connect(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dent_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("dency_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->connect(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_disconnectDpdents(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dency_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->disconnectDpdents(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_connectDent(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dent_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("dency_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->connectDent(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->__init__());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"disconnect", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_disconnect, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"disconnectAll", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_disconnectAll, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"connectDency", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_connectDency, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__str__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections___str__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__len__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections___len__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"disconnectDpdencies", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_disconnectDpdencies, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"connect", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_connect, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"disconnectDpdents", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_disconnectDpdents, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"connectDent", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_connectDent, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__TopologyConnections__::TopologyConnections();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__pipeline_data__::__TopologyConnections__::cl_TopologyConnections;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsDealloc(__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_dpdents(__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *self, void *closure) {
    return __to_py(self->__ss_object->dpdents);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_dpdents(__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->dpdents = __to_ss<__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_dpdencies(__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *self, void *closure) {
    return __to_py(self->__ss_object->dpdencies);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_dpdencies(__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->dpdencies = __to_ss<__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_navigation(__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *self, void *closure) {
    return __to_py(self->__ss_object->navigation);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_navigation(__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->navigation = __to_ss<__mepinta__::__pipeline__::__lo__::__generic_data__::__BiDirectedGraph__::BiDirectedGraph *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsGetSet[] = {
    {(char *)"dpdents", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_dpdents, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_dpdents, (char *)"", NULL},
    {(char *)"dpdencies", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_dpdencies, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_dpdencies, (char *)"", NULL},
    {(char *)"navigation", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_navigation, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_navigation, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "TopologyConnections.TopologyConnections",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections_as_number,  /* tp_as_number      */
    0,              /* tp_as_sequence    */
    0,              /* tp_as_mapping     */
    0,              /* tp_hash           */
    0,              /* tp_call           */
    (PyObject *(*)(PyObject *))__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections___str__, /* tp_str           */
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
    __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_pipeline_data_TopologyConnections, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(3);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->dpdents));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->dpdencies));
    PyTuple_SetItem(b, 2, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->navigation));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnections__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->dpdents = __to_ss<__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->dpdencies = __to_ss<__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *>(PyTuple_GetItem(state, 1));
    ((__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)self)->__ss_object->navigation = __to_ss<__mepinta__::__pipeline__::__lo__::__generic_data__::__BiDirectedGraph__::BiDirectedGraph *>(PyTuple_GetItem(state, 2));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __pipeline_data__
} // namespace __TopologyConnections__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __TopologyConnections__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_pipeline_data_TopologyConnections_shedskin_TopologyConnections(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(__TopologyConnections__::shedskin_TopologyConnections());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_pipeline_data_TopologyConnections_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_pipeline_data_TopologyConnectionsMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_TopologyConnections", (PyCFunction)Global_mepinta_pipeline_lo_pipeline_data_TopologyConnections_shedskin_TopologyConnections, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_data_TopologyConnections(void) {

    __ss_mod_mepinta_pipeline_lo_pipeline_data_TopologyConnections = Py_InitModule((char *)"TopologyConnections", Global_mepinta_pipeline_lo_pipeline_data_TopologyConnectionsMethods);
    if(!__ss_mod_mepinta_pipeline_lo_pipeline_data_TopologyConnections)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_data_TopologyConnections, "TopologyConnections", (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_data_TopologyConnections(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __pipeline_data__

} // namespace __TopologyConnections__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __TopologyConnections__ { /* XXX */

PyObject *TopologyConnections::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)(__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__TopologyConnections__::TopologyConnections *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__pipeline_data__::__TopologyConnections__::__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (TopologyConnections expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__pipeline_data__::__TopologyConnections__::__ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObject *)p)->__ss_object;
}
}
