#include "builtin.hpp"
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/topology_manager/TopologyManager.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
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
namespace __topology_manager__ {
namespace __TopologyManager__ {

str *const_0, *const_1, *const_2;

using __pipeline_backend__::__logging__::__logging__::logDebug;

str *__name__;


list<__ss_int> * default_0;


/**
class TopologyManager
*/

class_ *cl_TopologyManager;

void *TopologyManager::connectPropsDencies(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_dent_ids, list<__ss_int> *prop_dency_ids) {
    list<__ss_int> *__80;
    tuple2<__ss_int, __ss_int> *__76;
    __iter<tuple2<__ss_int, __ss_int> *> *__77, *__78;
    __ss_int __79, dency_id, dent_id, index;
    __iter<tuple2<__ss_int, __ss_int> *>::for_in_loop __81;


    FOR_IN_ENUM(dent_id,prop_dent_ids,80,79)
        index = __79;
        dency_id = prop_dency_ids->__getfast__(index);
        topo->connectDency(dent_id, dency_id);
    END_FOR

    return NULL;
}

void *TopologyManager::addProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_ids) {
    __iter<__ss_int> *__63;
    list<__ss_int> *__62;
    __ss_int __64, prop_id;
    list<__ss_int>::for_in_loop __65;


    FOR_IN(prop_id,prop_ids,62,64,65)
        topo->addPropId(prop_id);
    END_FOR

    return NULL;
}

void *TopologyManager::disconnectProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_dent_ids, list<__ss_int> *prop_dency_ids) {
    tuple2<__ss_int, __ss_int> *__92;
    __iter<__ss_int> *__89;
    __iter<tuple2<__ss_int, __ss_int> *>::for_in_loop __97;
    list<__ss_int> *__88, *__96;
    list<__ss_int>::for_in_loop __91;
    __iter<tuple2<__ss_int, __ss_int> *> *__93, *__94;
    __ss_int __90, __95, dency_id, dent_id, index;

    if ((len(prop_dency_ids)==0)) {

        FOR_IN(dent_id,prop_dent_ids,88,90,91)
            topo->disconnectDpdencies(dent_id);
        END_FOR

    }
    else {

        FOR_IN_ENUM(dent_id,prop_dent_ids,96,95)
            index = __95;
            dency_id = prop_dency_ids->__getfast__(index);
            topo->disconnect(dent_id, dency_id);
        END_FOR

    }
    return NULL;
}

void *TopologyManager::enableCached(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *cached_ids) {
    __iter<__ss_int> *__107;
    list<__ss_int> *__106;
    __ss_int __108, prop_id;
    list<__ss_int>::for_in_loop __109;

    logDebug(__modct(const_0, 1, cached_ids));

    FOR_IN(prop_id,cached_ids,106,108,109)
        (topo->cached)->add(prop_id);
    END_FOR

    return NULL;
}

void *TopologyManager::removeChanged(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_changed_ids) {
    __iter<__ss_int> *__103;
    list<__ss_int> *__102;
    __ss_int __104, prop_changed_id;
    list<__ss_int>::for_in_loop __105;


    FOR_IN(prop_changed_id,prop_changed_ids,102,104,105)
        (topo->changed_primary)->remove(prop_changed_id);
    END_FOR

    return NULL;
}

void *TopologyManager::removeProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_ids) {
    __iter<__ss_int> *__67;
    list<__ss_int> *__66;
    __ss_int __68, prop_id;
    list<__ss_int>::for_in_loop __69;


    FOR_IN(prop_id,prop_ids,66,68,69)
        topo->removePropId(prop_id);
    END_FOR

    return NULL;
}

void *TopologyManager::connectProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_dent_ids, list<__ss_int> *prop_dency_ids) {
    __iter<tuple2<__ss_int, __ss_int> *> *__71, *__72;
    tuple2<__ss_int, __ss_int> *__70;
    __iter<tuple2<__ss_int, __ss_int> *>::for_in_loop __75;
    __ss_int __73, dency_id, dent_id, index;
    list<__ss_int> *__74;

    logDebug(__modct(const_1, 2, prop_dent_ids, prop_dency_ids));

    FOR_IN_ENUM(dent_id,prop_dent_ids,74,73)
        index = __73;
        dency_id = prop_dency_ids->__getfast__(index);
        topo->connect(dent_id, dency_id);
    END_FOR

    return NULL;
}

void *TopologyManager::addChanged(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_changed_ids) {
    __iter<__ss_int> *__99;
    list<__ss_int> *__98;
    __ss_int __100, prop_changed_id;
    list<__ss_int>::for_in_loop __101;


    FOR_IN(prop_changed_id,prop_changed_ids,98,100,101)
        (topo->changed_primary)->add(prop_changed_id);
    END_FOR

    return NULL;
}

void *TopologyManager::disableCached(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *cached_ids) {
    __iter<__ss_int> *__111;
    list<__ss_int> *__110;
    __ss_int __112, prop_id;
    list<__ss_int>::for_in_loop __113;


    FOR_IN(prop_id,cached_ids,110,112,113)
        if ((topo->cached)->__contains__(prop_id)) {
            (topo->cached)->remove(prop_id);
        }
    END_FOR

    return NULL;
}

void *TopologyManager::__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
    
    return NULL;
}

void *TopologyManager::connectPropsDents(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_dent_ids, list<__ss_int> *prop_dency_ids) {
    tuple2<__ss_int, __ss_int> *__82;
    list<__ss_int> *__86;
    __ss_int __85, dency_id, dent_id, index;
    __iter<tuple2<__ss_int, __ss_int> *> *__83, *__84;
    __iter<tuple2<__ss_int, __ss_int> *>::for_in_loop __87;


    FOR_IN_ENUM(dent_id,prop_dent_ids,86,85)
        index = __85;
        dency_id = prop_dency_ids->__getfast__(index);
        topo->connectDent(dent_id, dency_id);
    END_FOR

    return NULL;
}

void *shedskin_TopologyManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo) {
    list<__ss_int> *prop_ids;
    TopologyManager *pm;

    pm = (new TopologyManager(context_lo));
    prop_ids = (new list<__ss_int>(1,0));
    pm->addChanged(topo, prop_ids);
    pm->addProperties(topo, prop_ids);
    pm->connectProperties(topo, prop_ids, prop_ids);
    pm->connectPropsDencies(topo, prop_ids, prop_ids);
    pm->connectPropsDents(topo, prop_ids, prop_ids);
    pm->disableCached(topo, prop_ids);
    pm->disconnectProperties(topo, prop_ids, prop_ids);
    pm->enableCached(topo, prop_ids);
    pm->removeChanged(topo, prop_ids);
    pm->removeProperties(topo, prop_ids);
    return NULL;
}

void __init() {
    const_0 = new str("Enable caching on %r");
    const_1 = new str("Connecting properties dpdents=%s dpdencies=%s");
    const_2 = new str("__main__");

    __name__ = new str("TopologyManager");

    default_0 = (new list<__ss_int>());
    cl_TopologyManager = new class_("TopologyManager");
    if (__eq(__name__, const_2)) {
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
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/topology_manager/TopologyManager.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include <structmember.h>
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/topology_manager/TopologyManager.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_topology_manager_TopologyManager;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __topology_manager__ { /* XXX */
namespace __TopologyManager__ { /* XXX */

/* class TopologyManager */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__topology_manager__::__TopologyManager__::TopologyManager *__ss_object;
} __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject;

static PyMemberDef __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_connectPropsDencies(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *>("topo", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_dent_ids", 1, 0, 0, args, kwargs);
        list<__ss_int> *arg_2 = __ss_arg<list<__ss_int> *>("prop_dency_ids", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)self)->__ss_object->connectPropsDencies(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_addProperties(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *>("topo", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)self)->__ss_object->addProperties(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_disconnectProperties(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *>("topo", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_dent_ids", 1, 0, 0, args, kwargs);
        list<__ss_int> *arg_2 = __ss_arg<list<__ss_int> *>("prop_dency_ids", 2, 1, __TopologyManager__::default_0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)self)->__ss_object->disconnectProperties(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_enableCached(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *>("topo", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("cached_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)self)->__ss_object->enableCached(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_removeChanged(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *>("topo", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_changed_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)self)->__ss_object->removeChanged(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_removeProperties(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *>("topo", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)self)->__ss_object->removeProperties(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_connectProperties(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *>("topo", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_dent_ids", 1, 0, 0, args, kwargs);
        list<__ss_int> *arg_2 = __ss_arg<list<__ss_int> *>("prop_dency_ids", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)self)->__ss_object->connectProperties(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_addChanged(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *>("topo", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_changed_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)self)->__ss_object->addChanged(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_disableCached(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *>("topo", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("cached_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)self)->__ss_object->disableCached(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)self)->__ss_object->__init__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_connectPropsDents(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *>("topo", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_dent_ids", 1, 0, 0, args, kwargs);
        list<__ss_int> *arg_2 = __ss_arg<list<__ss_int> *>("prop_dency_ids", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)self)->__ss_object->connectPropsDents(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"connectPropsDencies", (PyCFunction)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_connectPropsDencies, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"addProperties", (PyCFunction)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_addProperties, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"disconnectProperties", (PyCFunction)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_disconnectProperties, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"enableCached", (PyCFunction)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_enableCached, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"removeChanged", (PyCFunction)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_removeChanged, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"removeProperties", (PyCFunction)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_removeProperties, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"connectProperties", (PyCFunction)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_connectProperties, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"addChanged", (PyCFunction)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_addChanged, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"disableCached", (PyCFunction)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_disableCached, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"connectPropsDents", (PyCFunction)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_connectPropsDents, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *self = (__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__topology_manager__::__TopologyManager__::TopologyManager();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__topology_manager__::__TopologyManager__::cl_TopologyManager;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerDealloc(__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyGetSetDef __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerGetSet[] = {
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "TopologyManager.TopologyManager",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_topology_manager_TopologyManager, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(0);
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __topology_manager__
} // namespace __TopologyManager__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __topology_manager__ { /* XXX */
namespace __TopologyManager__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_topology_manager_TopologyManager_shedskin_TopologyManager(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *>("topo", 1, 0, 0, args, kwargs);

        return __to_py(__TopologyManager__::shedskin_TopologyManager(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_topology_manager_TopologyManager_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_topology_manager_TopologyManagerMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_TopologyManager", (PyCFunction)Global_mepinta_pipeline_lo_topology_manager_TopologyManager_shedskin_TopologyManager, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_topology_manager_TopologyManager(void) {

    __ss_mod_mepinta_pipeline_lo_topology_manager_TopologyManager = Py_InitModule((char *)"TopologyManager", Global_mepinta_pipeline_lo_topology_manager_TopologyManagerMethods);
    if(!__ss_mod_mepinta_pipeline_lo_topology_manager_TopologyManager)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_topology_manager_TopologyManager, "TopologyManager", (PyObject *)&__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_topology_manager_TopologyManager(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __topology_manager__

} // namespace __TopologyManager__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __topology_manager__ { /* XXX */
namespace __TopologyManager__ { /* XXX */

PyObject *TopologyManager::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *self = (__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)(__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__topology_manager__::__TopologyManager__::TopologyManager *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__topology_manager__::__TopologyManager__::__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (TopologyManager expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__topology_manager__::__TopologyManager__::__ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObject *)p)->__ss_object;
}
}
