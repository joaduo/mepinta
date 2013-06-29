#include "builtin.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
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
namespace __generic_data__ {
namespace __DirectedGraph__ {

str *const_0, *const_1, *const_2, *const_3, *const_4;


str *__name__;
__ss_int NULL_UID;



/**
class DirectedGraphIterator
*/

class_ *cl_DirectedGraphIterator;

tuple2<__ss_int, __ss_int> *DirectedGraphIterator::next() {
    tuple2<__ss_int, __ss_int> *ids;

    if ((this->current<len(this->__keys))) {
        ids = (new tuple2<__ss_int, __ss_int>(2,(this->__keys)->__getfast__(this->current),(this->__values)->__getfast__(this->current)));
        this->current = (this->current+1);
        return ids;
    }
    else {
        return (new tuple2<__ss_int, __ss_int>(2,NULL_UID,NULL_UID));
    }
    return 0;
}

void *DirectedGraphIterator::__init__(list<__ss_int> *keys, list<__ss_int> *values) {
    
    this->current = 0;
    this->__keys = keys;
    this->__values = values;
    return NULL;
}

/**
class DirectedGraph
*/

class_ *cl_DirectedGraph;

list<__ss_int> *DirectedGraph::__getslice__(__ss_int id_1, __ss_int id_2) {
    __ss_int index_hi, index_lo;
    __ss_bool __10, __11;

    if ((id_1>id_2)) {
        return (new list<__ss_int>());
    }
    index_lo = this->bisect_left(this->__keys, id_1, 0, (-1));
    index_hi = this->bisectRight(this->__keys, id_2, 0, (-1));
    if ((index_lo!=index_hi)) {
        if ((((this->__keys)->__getfast__(index_lo)==id_1) and ((this->__keys)->__getfast__((index_hi-1))==id_2))) {
            return (this->__values)->__slice__(3, index_lo, index_hi, 0);
        }
        else {
            return (new list<__ss_int>());
        }
    }
    return 0;
}

str *DirectedGraph::__str__() {
    tuple2<__ss_int, __ss_int> *__22;
    __iter<tuple2<__ss_int, __ss_int> *>::for_in_loop __27;
    str *_str_;
    list<__ss_int> *__26;
    __iter<tuple2<__ss_int, __ss_int> *> *__23, *__24;
    __ss_int __25, index, k;

    _str_ = const_0;

    FOR_IN_ENUM(k,this->__keys,26,25)
        index = __25;
        _str_ = (_str_)->__iadd__(__modct(const_1, 2, ___box(k), ___box((this->__values)->__getfast__(index))));
    END_FOR

    return _str_;
}

__ss_int DirectedGraph::bisectRight(list<__ss_int> *a, __ss_int x, __ss_int lo, __ss_int hi) {
    /**
    */
    __ss_int mid;

    if ((lo<0)) {
        throw ((new ValueError(const_2)));
    }
    if ((hi==(-1))) {
        hi = len(a);
    }

    while ((lo<hi)) {
        mid = __floordiv((lo+hi),2);
        if ((x<a->__getfast__(mid))) {
            hi = mid;
        }
        else {
            lo = (mid+1);
        }
    }
    return lo;
}

void *DirectedGraph::__init__() {
    
    this->__keys = (new list<__ss_int>());
    this->__values = (new list<__ss_int>());
    return NULL;
}

__ss_int DirectedGraph::index(__ss_int item_id) {
    __ss_int index;

    index = this->bisect_left(this->__keys, item_id, 0, (-1));
    if (((this->__keys)->__getfast__(index)==item_id)) {
        return index;
    }
    else {
        throw ((new ValueError(__modct(const_3, 1, (this->__class__)->__name__))));
    }
    return 0;
}

void *DirectedGraph::__delslice__(__ss_int id_1, __ss_int id_2) {
    __ss_int index_hi, index_lo;
    __ss_bool __7, __8;

    if ((id_1>id_2)) {
        return NULL;
    }
    index_lo = this->bisect_left(this->__keys, id_1, 0, (-1));
    index_hi = this->bisectRight(this->__keys, id_2, 0, (-1));
    if ((index_lo!=index_hi)) {
        if ((((this->__keys)->__getfast__(index_lo)==id_1) and ((this->__keys)->__getfast__((index_hi-1))==id_2))) {
            (this->__keys)->__delete__(3, index_lo, index_hi, 0);
            (this->__values)->__delete__(3, index_lo, index_hi, 0);
        }
    }
    return 0;
}

__ss_bool DirectedGraph::__contains__(__ss_int item_id) {
    __ss_int index;

    index = this->bisect_left(this->__keys, item_id, 0, (-1));
    if ((len(this->__keys)==index)) {
        return False;
    }
    else if (((this->__keys)->__getfast__(index)==item_id)) {
        return True;
    }
    else {
        return False;
    }
    return False;
}

void *DirectedGraph::add(__ss_int item_id, __ss_int value) {
    
    return this->__setitem__(item_id, value);
}

__ss_int DirectedGraph::getFirst(__ss_int item_id) {
    __ss_int index;

    index = this->bisect_left(this->__keys, item_id, 0, (-1));
    return (this->__values)->__getfast__(index);
}

__ss_bool DirectedGraph::has(__ss_int item_id, __ss_int value) {
    tuple2<__ss_int, __ss_int> *__17;
    __ss_bool __18, __19, __20, __21;
    __ss_int hi, index, lo;

    __17 = this->bisectLeftRight(this->__keys, item_id, 0, (-1));
    lo = __17->__getfirst__();
    hi = __17->__getsecond__();
    index = this->bisect_left(this->__values, value, lo, hi);
    if (((lo!=hi) and (len(this->__keys)!=index))) {
        if ((((this->__keys)->__getfast__(index)==item_id) and ((this->__values)->__getfast__(index)==value))) {
            return True;
        }
    }
    return False;
}

__ss_int DirectedGraph::__len__() {
    
    return len(this->__keys);
}

list<__ss_int> *DirectedGraph::__getitem__(__ss_int item_id) {
    tuple2<__ss_int, __ss_int> *__9;
    __ss_int index_hi, index_lo;

    __9 = this->bisectLeftRight(this->__keys, item_id, 0, (-1));
    index_lo = __9->__getfirst__();
    index_hi = __9->__getsecond__();
    if ((index_lo!=index_hi)) {
        return (this->__values)->__slice__(3, index_lo, index_hi, 0);
    }
    else {
        return (new list<__ss_int>());
    }
    return 0;
}

void *DirectedGraph::__setitem__(__ss_int item_id, __ss_int value) {
    tuple2<__ss_int, __ss_int> *__12;
    __ss_int hi, index, lo;

    __12 = this->bisectLeftRight(this->__keys, item_id, 0, (-1));
    lo = __12->__getfirst__();
    hi = __12->__getsecond__();
    index = this->bisect_left(this->__values, value, lo, hi);
    (this->__keys)->insert(index, item_id);
    (this->__values)->insert(index, value);
    return NULL;
}

list<__ss_int> *DirectedGraph::__slice__(__ss_int id_1, __ss_int id_2) {
    
    return this->__getslice__(id_1, id_2);
}

DirectedGraphIterator *DirectedGraph::getSsIterator() {
    
    return (new DirectedGraphIterator(this->__keys, this->__values));
}

tuple2<__ss_int, __ss_int> *DirectedGraph::bisectLeftRight(list<__ss_int> *a, __ss_int x, __ss_int lo, __ss_int hi) {
    /**
    */
    __ss_int mid, value;

    if ((lo<0)) {
        throw ((new ValueError(const_2)));
    }
    if ((hi==(-1))) {
        hi = len(a);
    }
    if ((hi==0)) {
        return (new tuple2<__ss_int, __ss_int>(2,lo,hi));
    }

    while ((lo<hi)) {
        mid = __floordiv((lo+hi),2);
        value = a->__getfast__(mid);
        if ((value<x)) {
            lo = (mid+1);
        }
        else if ((value>x)) {
            hi = mid;
        }
        else {
            break;
        }
    }
    if ((value==x)) {
        if ((a->__getfast__((hi-1))!=x)) {
            hi = this->bisectRight(a, x, (mid+1), hi);
        }
        if ((a->__getfast__(lo)!=x)) {
            lo = this->bisect_left(a, x, lo, mid);
        }
    }
    return (new tuple2<__ss_int, __ss_int>(2,lo,hi));
}

__ss_int DirectedGraph::count(__ss_int item_id) {
    tuple2<__ss_int, __ss_int> *__16;
    __ss_int index_hi, index_lo;

    __16 = this->bisectLeftRight(this->__keys, item_id, 0, (-1));
    index_lo = __16->__getfirst__();
    index_hi = __16->__getsecond__();
    return (index_hi-index_lo);
}

void *DirectedGraph::__delitem__(__ss_int item_id) {
    /**
      Deletes Values for a specific id  
    */
    tuple2<__ss_int, __ss_int> *__6;
    __ss_int index_hi, index_lo;

    __6 = this->bisectLeftRight(this->__keys, item_id, 0, (-1));
    index_lo = __6->__getfirst__();
    index_hi = __6->__getsecond__();
    if ((index_lo!=index_hi)) {
        (this->__keys)->__delete__(3, index_lo, index_hi, 0);
        (this->__values)->__delete__(3, index_lo, index_hi, 0);
    }
    return NULL;
}

__ss_int DirectedGraph::bisect_left(list<__ss_int> *a, __ss_int x, __ss_int lo, __ss_int hi) {
    /**
    Return the index where to insert item x in list a, assuming a is sorted.
    
    The return value i is such that all e in a[:i] have e < x, and all e in
    a[i:] have e >= x.  So if x already appears in the list, a.insert(x) will
    insert just before the leftmost x already there.
    
    Optional args lo (default 0) and hi (default len(a)) bound the
    slice of a to be searched.
    
    Replaced def bisect_left(self,a, x, lo=0, hi=None): to hi=-1
      So that there is no type warnings on ShedSkin
    */
    __ss_int mid;

    if ((lo<0)) {
        throw ((new ValueError(const_2)));
    }
    if ((hi==(-1))) {
        hi = len(a);
    }

    while ((lo<hi)) {
        mid = __floordiv((lo+hi),2);
        if ((a->__getfast__(mid)<x)) {
            lo = (mid+1);
        }
        else {
            hi = mid;
        }
    }
    return lo;
}

void *DirectedGraph::remove(__ss_int item_id, __ss_int value) {
    tuple2<__ss_int, __ss_int> *__13;
    __ss_bool __14, __15;
    __ss_int hi, index, lo;

    __13 = this->bisectLeftRight(this->__keys, item_id, 0, (-1));
    lo = __13->__getfirst__();
    hi = __13->__getsecond__();
    if ((lo!=hi)) {
        index = this->bisect_left(this->__values, value, lo, hi);
        if ((((this->__keys)->__getfast__(index)==item_id) and ((this->__values)->__getfast__(index)==value))) {
            (this->__keys)->__delitem__(index);
            (this->__values)->__delitem__(index);
        }
    }
    return NULL;
}

DirectedGraph *DirectedGraph::__deepcopy__(dict<void *, pyobj *> *memo) {
    DirectedGraph *c = new DirectedGraph();
    memo->__setitem__(this, c);
    c->__keys = __deepcopy(__keys);
    c->_DirectedGraph__keys = __deepcopy(_DirectedGraph__keys);
    c->__values = __deepcopy(__values);
    c->_DirectedGraph__values = __deepcopy(_DirectedGraph__values);
    return c;
}

void *shedskin_DirectedGraph() {
    tuple2<__ss_int, __ss_int> *e;
    DirectedGraph *tbl;
    list<__ss_int> *a, *b;
    DirectedGraphIterator *iterator;

    a = (new list<__ss_int>(10,1,2,4,5,6,6,6,8,100,3221));
    b = (new list<__ss_int>(10,1,2,4,5,6,5,9,8,100,3221));
    tbl = (new DirectedGraph(1));
    tbl->_DirectedGraph__keys = a;
    tbl->_DirectedGraph__values = b;
    tbl->__delitem__(1);
    tbl->__delslice__(2, 5);
    tbl->__getitem__(5);
    tbl->getFirst(6);
    tbl->__getslice__(6, 100);
    tbl->__slice__(6, 100);
    len(tbl);
    tbl->__setitem__(1, 10);
    tbl->add(1, 11);
    tbl->remove(1, 10);
    tbl->count(6);
    iterator = tbl->getSsIterator();
    e = iterator->next();

    while ((e->__getfirst__()!=0)) {
        e = iterator->next();
    }
    ___bool((tbl)->__contains__(6));
    tbl->has(1, 10);
    tbl->index(6);
    __str(tbl);
    return NULL;
}

void *shedskin_test() {
    DirectedGraph *id_indexed_table;
    list<__ss_int> *a, *b;

    id_indexed_table = (new DirectedGraph(1));
    id_indexed_table->add(4, 543);
    id_indexed_table->add(4, 45);
    a = (new list<__ss_int>(10,1,2,4,5,6,6,6,8,100,3221));
    b = (new list<__ss_int>(10,1,2,4,5,6,5,9,8,100,3221));
    id_indexed_table = (new DirectedGraph(1));
    id_indexed_table->__keys = a;
    id_indexed_table->__values = b;
    id_indexed_table->__setitem__(1, 20);
    id_indexed_table->__delitem__(1);
    id_indexed_table->__delslice__(2, 6);
    id_indexed_table->add(4, 543);
    id_indexed_table->add(4, 45);
    id_indexed_table->add(8, 8);
    id_indexed_table->add(8, 20);
    id_indexed_table->remove(8, 8);
    id_indexed_table->remove(8, 20);
    id_indexed_table->add(203, 423123);
    return NULL;
}

void __init() {
    const_0 = new str("");
    const_1 = new str("%s:%s ");
    const_2 = new str("lo must be non-negative");
    const_3 = new str("%.index(x): x not in table");
    const_4 = new str("__main__");

    __name__ = new str("DirectedGraph");

    NULL_UID = __mepinta__::__pipeline__::__lo__::__constants__::NULL_UID;
    cl_DirectedGraphIterator = new class_("DirectedGraphIterator");
    cl_DirectedGraph = new class_("DirectedGraph");
    if (__eq(__name__, const_4)) {
        shedskin_DirectedGraph();
        shedskin_test();
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
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include <structmember.h>
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/constants.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_generic_data_DirectedGraph;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __generic_data__ { /* XXX */
namespace __DirectedGraph__ { /* XXX */

/* class DirectedGraphIterator */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraphIterator *__ss_object;
} __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject;

static PyMemberDef __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator_next(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject *)self)->__ss_object->next());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        list<__ss_int> *arg_0 = __ss_arg<list<__ss_int> *>("keys", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("values", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject *)self)->__ss_object->__init__(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"next", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator_next, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject *self = (__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraphIterator();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::cl_DirectedGraphIterator;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorDealloc(__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator_current(__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject *self, void *closure) {
    return __to_py(self->__ss_object->current);
}

int __ss_set___ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator_current(__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->current = __to_ss<__ss_int >(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorGetSet[] = {
    {(char *)"current", (getter)__ss_get___ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator_current, (setter)__ss_set___ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator_current, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "DirectedGraph.DirectedGraphIterator",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_generic_data_DirectedGraph, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(1);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject *)self)->__ss_object->current));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIterator__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject *)self)->__ss_object->current = __to_ss<__ss_int >(PyTuple_GetItem(state, 0));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __generic_data__
} // namespace __DirectedGraph__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __generic_data__ { /* XXX */
namespace __DirectedGraph__ { /* XXX */

/* class DirectedGraph */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *__ss_object;
} __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject;

static PyMemberDef __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___getslice__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("id_1", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("id_2", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->__getslice__(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___str__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->__str__());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_bisectRight(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        list<__ss_int> *arg_0 = __ss_arg<list<__ss_int> *>("a", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("x", 1, 0, 0, args, kwargs);
        __ss_int arg_2 = __ss_arg<__ss_int >("lo", 2, 1, 0, args, kwargs);
        __ss_int arg_3 = __ss_arg<__ss_int >("hi", 3, 1, (-1), args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->bisectRight(arg_0, arg_1, arg_2, arg_3));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->__init__());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_index(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("item_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->index(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___delslice__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("id_1", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("id_2", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->__delslice__(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___contains__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("item_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->__contains__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_add(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("item_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("value", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->add(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_getFirst(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("item_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->getFirst(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_has(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("item_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("value", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->has(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___len__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->__len__());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___getitem__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("item_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->__getitem__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___setitem__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("item_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("value", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->__setitem__(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___slice__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("id_1", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("id_2", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->__slice__(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_getSsIterator(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->getSsIterator());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_bisectLeftRight(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        list<__ss_int> *arg_0 = __ss_arg<list<__ss_int> *>("a", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("x", 1, 0, 0, args, kwargs);
        __ss_int arg_2 = __ss_arg<__ss_int >("lo", 2, 1, 0, args, kwargs);
        __ss_int arg_3 = __ss_arg<__ss_int >("hi", 3, 1, (-1), args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->bisectLeftRight(arg_0, arg_1, arg_2, arg_3));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_count(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("item_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->count(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___delitem__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("item_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->__delitem__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_bisect_left(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        list<__ss_int> *arg_0 = __ss_arg<list<__ss_int> *>("a", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("x", 1, 0, 0, args, kwargs);
        __ss_int arg_2 = __ss_arg<__ss_int >("lo", 2, 1, 0, args, kwargs);
        __ss_int arg_3 = __ss_arg<__ss_int >("hi", 3, 1, (-1), args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->bisect_left(arg_0, arg_1, arg_2, arg_3));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_remove(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("item_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("value", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->remove(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__getslice__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___getslice__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__str__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___str__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"bisectRight", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_bisectRight, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"index", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_index, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__delslice__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___delslice__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__contains__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___contains__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"add", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_add, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getFirst", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_getFirst, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"has", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_has, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__len__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___len__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__getitem__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___getitem__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setitem__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___setitem__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__slice__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___slice__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getSsIterator", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_getSsIterator, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"bisectLeftRight", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_bisectLeftRight, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"count", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_count, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__delitem__", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___delitem__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"bisect_left", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_bisect_left, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"remove", (PyCFunction)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_remove, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *self = (__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::cl_DirectedGraph;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphDealloc(__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__DirectedGraph__keys(__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *self, void *closure) {
    return __to_py(self->__ss_object->_DirectedGraph__keys);
}

int __ss_set___ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__DirectedGraph__keys(__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->_DirectedGraph__keys = __to_ss<list<__ss_int> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__DirectedGraph__values(__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *self, void *closure) {
    return __to_py(self->__ss_object->_DirectedGraph__values);
}

int __ss_set___ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__DirectedGraph__values(__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->_DirectedGraph__values = __to_ss<list<__ss_int> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphGetSet[] = {
    {(char *)"_DirectedGraph__keys", (getter)__ss_get___ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__DirectedGraph__keys, (setter)__ss_set___ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__DirectedGraph__keys, (char *)"", NULL},
    {(char *)"_DirectedGraph__values", (getter)__ss_get___ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__DirectedGraph__values, (setter)__ss_set___ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__DirectedGraph__values, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "DirectedGraph.DirectedGraph",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph_as_number,  /* tp_as_number      */
    0,              /* tp_as_sequence    */
    0,              /* tp_as_mapping     */
    0,              /* tp_hash           */
    0,              /* tp_call           */
    (PyObject *(*)(PyObject *))__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___str__, /* tp_str           */
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
    __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_generic_data_DirectedGraph, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(2);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->_DirectedGraph__keys));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->_DirectedGraph__values));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraph__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->_DirectedGraph__keys = __to_ss<list<__ss_int> *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)self)->__ss_object->_DirectedGraph__values = __to_ss<list<__ss_int> *>(PyTuple_GetItem(state, 1));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __generic_data__
} // namespace __DirectedGraph__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __generic_data__ { /* XXX */
namespace __DirectedGraph__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_generic_data_DirectedGraph_shedskin_test(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(__DirectedGraph__::shedskin_test());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *Global_mepinta_pipeline_lo_generic_data_DirectedGraph_shedskin_DirectedGraph(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(__DirectedGraph__::shedskin_DirectedGraph());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_generic_data_DirectedGraph_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_generic_data_DirectedGraphMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_test", (PyCFunction)Global_mepinta_pipeline_lo_generic_data_DirectedGraph_shedskin_test, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_DirectedGraph", (PyCFunction)Global_mepinta_pipeline_lo_generic_data_DirectedGraph_shedskin_DirectedGraph, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_generic_data_DirectedGraph(void) {

    __ss_mod_mepinta_pipeline_lo_generic_data_DirectedGraph = Py_InitModule((char *)"DirectedGraph", Global_mepinta_pipeline_lo_generic_data_DirectedGraphMethods);
    if(!__ss_mod_mepinta_pipeline_lo_generic_data_DirectedGraph)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_generic_data_DirectedGraph, "DirectedGraphIterator", (PyObject *)&__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObjectType);
    if (PyType_Ready(&__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_generic_data_DirectedGraph, "DirectedGraph", (PyObject *)&__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_generic_data_DirectedGraph(void) {
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_generic_data_DirectedGraph, (char *)"NULL_UID", __to_py(__DirectedGraph__::NULL_UID));

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __generic_data__

} // namespace __DirectedGraph__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __generic_data__ { /* XXX */
namespace __DirectedGraph__ { /* XXX */

PyObject *DirectedGraphIterator::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject *self = (__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject *)(__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraphIterator *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (DirectedGraphIterator expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObject *)p)->__ss_object;
}
}
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __generic_data__ { /* XXX */
namespace __DirectedGraph__ { /* XXX */

PyObject *DirectedGraph::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *self = (__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)(__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (DirectedGraph expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::__ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObject *)p)->__ss_object;
}
}
