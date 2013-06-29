#include "builtin.hpp"
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/propagation/SimplePropagationManager.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"

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
namespace __pipeline_evaluator__ {
namespace __propagation__ {
namespace __SimplePropagationManager__ {


str *__name__;



/**
class SimplePropagationManager
*/

class_ *cl_SimplePropagationManager;

void *SimplePropagationManager::propagateChanges(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline) {
    
    if (len(pline->changed_primary)) {
        this->__propagate(pline->getTopology(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::default_4), pline->changed_primary, pline->changed_track);
    }
    return NULL;
}

void *SimplePropagationManager::__propagate(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, set<__ss_int> *changed, set<__ss_int> *changed_ppgation) {
    __ss_int prop_id;
    set<__ss_int> *affected_props;


    while (len(changed)) {
        prop_id = changed->pop();
        affected_props = (new set<__ss_int>());
        this->__propagateOneChange(topo, prop_id, affected_props);
        changed->difference_update(1, affected_props);
        changed_ppgation->update(1, affected_props);
    }
    return NULL;
}

void *SimplePropagationManager::__propagateOneChange(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, __ss_int prop_id, set<__ss_int> *affected_props) {
    set<__ss_int> *not_visited;

    not_visited = (new set<__ss_int>((new list<__ss_int>(1,prop_id))));

    while (len(not_visited)) {
        prop_id = not_visited->pop();
        if ((!(affected_props)->__contains__(prop_id))) {
            affected_props->add(prop_id);
            not_visited->update(1, ((topo->connections)->dpdents)->__getitem__(prop_id));
        }
    }
    return NULL;
}

void *SimplePropagationManager::__init__(__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *pline_evaluator) {
    
    return NULL;
}

void *shedskin_SimplePropagationManager(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *pline_evaluator) {
    SimplePropagationManager *spm;

    spm = (new SimplePropagationManager(pline_evaluator));
    spm->propagateChanges(pline);
    return NULL;
}

void __init() {
    __name__ = new str("SimplePropagationManager");

    cl_SimplePropagationManager = new class_("SimplePropagationManager");
}

} // module namespace
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
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/propagation/SimplePropagationManager.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include <structmember.h>
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/propagation/SimplePropagationManager.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __propagation__ { /* XXX */
namespace __SimplePropagationManager__ { /* XXX */

/* class SimplePropagationManager */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__propagation__::__SimplePropagationManager__::SimplePropagationManager *__ss_object;
} __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObject;

static PyMemberDef __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager_propagateChanges(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObject *)self)->__ss_object->propagateChanges(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager___propagate(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *>("topo", 0, 0, 0, args, kwargs);
        set<__ss_int> *arg_1 = __ss_arg<set<__ss_int> *>("changed", 1, 0, 0, args, kwargs);
        set<__ss_int> *arg_2 = __ss_arg<set<__ss_int> *>("changed_ppgation", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObject *)self)->__ss_object->__propagate(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager___propagateOneChange(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *>("topo", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("prop_id", 1, 0, 0, args, kwargs);
        set<__ss_int> *arg_2 = __ss_arg<set<__ss_int> *>("affected_props", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObject *)self)->__ss_object->__propagateOneChange(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *>("pline_evaluator", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObject *)self)->__ss_object->__init__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"propagateChanges", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager_propagateChanges, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__propagate", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager___propagate, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__propagateOneChange", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager___propagateOneChange, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObject *self = (__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__propagation__::__SimplePropagationManager__::SimplePropagationManager();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__propagation__::__SimplePropagationManager__::cl_SimplePropagationManager;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerDealloc(__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyGetSetDef __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerGetSet[] = {
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "SimplePropagationManager.SimplePropagationManager",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(0);
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __pipeline_evaluator__
} // namespace __propagation__
} // namespace __SimplePropagationManager__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __propagation__ { /* XXX */
namespace __SimplePropagationManager__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_shedskin_SimplePropagationManager(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *>("pline_evaluator", 1, 0, 0, args, kwargs);

        return __to_py(__SimplePropagationManager__::shedskin_SimplePropagationManager(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManagerMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_SimplePropagationManager", (PyCFunction)Global_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_shedskin_SimplePropagationManager, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager(void) {

    __ss_mod_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager = Py_InitModule((char *)"SimplePropagationManager", Global_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManagerMethods);
    if(!__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager, "SimplePropagationManager", (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __pipeline_evaluator__

} // namespace __propagation__

} // namespace __SimplePropagationManager__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __propagation__ { /* XXX */
namespace __SimplePropagationManager__ { /* XXX */

PyObject *SimplePropagationManager::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObject *self = (__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObject *)(__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObjectType, 0));
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
} // module namespace

namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__propagation__::__SimplePropagationManager__::SimplePropagationManager *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__propagation__::__SimplePropagationManager__::__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (SimplePropagationManager expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__propagation__::__SimplePropagationManager__::__ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObject *)p)->__ss_object;
}
}
