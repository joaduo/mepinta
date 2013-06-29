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
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/property_manager/PropertyManager.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"

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
namespace __property_manager__ {
namespace __PropertyManager__ {

str *const_0, *const_1, *const_2, *const_3, *const_4, *const_5, *const_6;

using __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue;
using __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue;
using __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager;
using __pipeline_backend__::__logging__::__logging__::logDebug;
using __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::anyPtrToVoidp;

str *__name__;
__ss_int FUNCTION_PROPERTY_FLAG, FUNCTUM_PROPERTY_FLAG, INPUT_PROPERTY_FLAG, NULL_UID;



/**
class PropertyManager
*/

class_ *cl_PropertyManager;

list<__ss_int> *PropertyManager::createFuncProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<str *> *prop_names, list<__ss_int> *func_ptr_ids) {
    list<str *> *__198;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop;
    list<__ss_int> *prop_ids;
    __iter<tuple2<__ss_int, str *> *>::for_in_loop __199;
    str *prop_name;
    tuple2<__ss_int, str *> *__194;
    __ss_int __197, index;
    __iter<tuple2<__ss_int, str *> *> *__195, *__196;

    logDebug(__modct(const_0, 1, prop_names));
    prop_ids = (new list<__ss_int>());

    FOR_IN_ENUM(prop_name,prop_names,198,197)
        index = __197;
        prop = (new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property(FUNCTION_PROPERTY_FLAG, prop_name, NULL_UID));
        (this->p_value_mngr)->replacePropValue(prop, anyPtrToVoidp((new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue(func_ptr_ids->__getfast__(index)))));
        prop_ids->append(pline->addProperty(prop));
    END_FOR

    return prop_ids;
}

void *PropertyManager::removeFilters(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids) {
    __iter<__ss_int> *__215;
    list<__ss_int> *__214;
    __ss_int __216, p_id;
    list<__ss_int>::for_in_loop __217;

    logDebug(__modct(const_1, 1, prop_ids));

    FOR_IN(p_id,prop_ids,214,216,217)
        if ((pline->marked_outputs)->__contains__(p_id)) {
            (pline->marked_outputs)->remove(p_id);
        }
    END_FOR

    return NULL;
}

void *PropertyManager::deleteProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids) {
    /**
    Deletes properties permanently from a pipeline. (also delete their values to
    avoid memory leaks)
    :param pline:
    :param prop_ids:
    */
    __iter<__ss_int> *__207;
    list<__ss_int> *__206;
    __ss_int __208, p_id;
    list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *props;
    list<__ss_int>::for_in_loop __209;

    props = (new list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>());

    FOR_IN(p_id,prop_ids,206,208,209)
        props->append(pline->deleteProperty(p_id));
    END_FOR

    (this->p_value_mngr)->deletePropertiesValues();
    return NULL;
}

void *PropertyManager::addNonCached(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *dent_ids, list<__ss_int> *dency_ids) {
    tuple2<__ss_int, __ss_int> *__218;
    list<__ss_int> *__222;
    __ss_int __221, dent_id, index;
    __iter<tuple2<__ss_int, __ss_int> *>::for_in_loop __223;
    __iter<tuple2<__ss_int, __ss_int> *> *__219, *__220;

    logDebug(__modct(const_2, 2, dent_ids, dency_ids));

    FOR_IN_ENUM(dent_id,dent_ids,222,221)
        index = __221;
        if (__NOT((pline->cached_link)->has(dent_id, dency_ids->__getfast__(index)))) {
            (pline->cached_link)->add(dent_id, dency_ids->__getfast__(index));
        }
    END_FOR

    return NULL;
}

list<__ss_int> *PropertyManager::createProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<str *> *prop_names, list<__ss_int> *dtype_ids, __ss_int prop_flags) {
    list<str *> *__192;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop;
    list<__ss_int> *prop_ids;
    __iter<tuple2<__ss_int, str *> *>::for_in_loop __193;
    str *prop_name;
    tuple2<__ss_int, str *> *__188;
    __ss_int __191, index;
    __iter<tuple2<__ss_int, str *> *> *__189, *__190;

    prop_ids = (new list<__ss_int>());
    logDebug(__modct(const_3, 1, prop_names));

    FOR_IN_ENUM(prop_name,prop_names,192,191)
        index = __191;
        prop = (new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property(prop_flags, prop_name, dtype_ids->__getfast__(index)));
        prop_ids->append(pline->addProperty(prop));
    END_FOR

    return prop_ids;
}

void *PropertyManager::addFilters(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids) {
    __iter<__ss_int> *__211;
    list<__ss_int> *__210;
    __ss_int __212, p_id;
    list<__ss_int>::for_in_loop __213;

    logDebug(__modct(const_4, 1, prop_ids));

    FOR_IN(p_id,prop_ids,210,212,213)
        (pline->marked_outputs)->add(p_id);
    END_FOR

    return NULL;
}

list<__ss_int> *PropertyManager::createFunctumProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<str *> *prop_names, list<__ss_int> *func_ptr_ids, list<__ss_int> *dtype_ids, __ss_int prop_flags) {
    list<str *> *__204;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *functum_prop, *prop;
    list<__ss_int> *prop_ids;
    tuple2<__ss_int, str *> *__200;
    str *prop_name;
    __iter<tuple2<__ss_int, str *> *>::for_in_loop __205;
    __ss_int __203, index;
    __iter<tuple2<__ss_int, str *> *> *__201, *__202;

    logDebug(__modct(const_5, 1, prop_names));
    prop_ids = (new list<__ss_int>());

    FOR_IN_ENUM(prop_name,prop_names,204,203)
        index = __203;
        prop = (new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property(((FUNCTUM_PROPERTY_FLAG)|(prop_flags)), prop_name, NULL_UID));
        functum_prop = (new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property(FUNCTION_PROPERTY_FLAG, prop_name, dtype_ids->__getfast__(index)));
        (this->p_value_mngr)->replacePropValue(prop, anyPtrToVoidp((new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue(func_ptr_ids->__getfast__(index), functum_prop))));
        prop_ids->append(pline->addProperty(prop));
    END_FOR

    return prop_ids;
}

void *PropertyManager::removeNonCached(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *dent_ids) {
    __iter<__ss_int> *__225;
    list<__ss_int> *__224;
    __ss_int __226, dent_id;
    list<__ss_int>::for_in_loop __227;


    FOR_IN(dent_id,dent_ids,224,226,227)
        (pline->cached_link)->__delitem__(dent_id);
    END_FOR

    return NULL;
}

void *PropertyManager::__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
    
    this->context_lo = context_lo;
    this->p_value_mngr = (new __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager(context_lo));
    return NULL;
}

void *shedskin_PropertyManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id) {
    list<str *> *prop_names;
    list<__ss_int> *prop_ids;
    PropertyManager *pm;

    pm = (new PropertyManager(context_lo));
    prop_ids = (new list<__ss_int>(1,prop_id));
    pm->addFilters(pline, prop_ids);
    pm->removeFilters(pline, prop_ids);
    pm->addNonCached(pline, prop_ids, prop_ids);
    pm->removeNonCached(pline, prop_ids);
    prop_names = (new list<str *>(1,const_6));
    pm->createFuncProperties(pline, prop_names, (new list<__ss_int>(1,0)));
    pm->createFunctumProperties(pline, prop_names, (new list<__ss_int>(1,0)), (new list<__ss_int>(1,0)), 0);
    pm->createProperties(pline, prop_names, (new list<__ss_int>(1,0)), INPUT_PROPERTY_FLAG);
    pm->deleteProperties(pline, prop_ids);
    return NULL;
}

void __init() {
    const_0 = new str("Creating functions %s");
    const_1 = new str("Removing propagation filter properties %r");
    const_2 = new str("Setting non cached connections %r <-> %r");
    const_3 = new str("Creating properties %s");
    const_4 = new str("Adding propagation filter properties %r");
    const_5 = new str("Creating functums %s");
    const_6 = new str("name");

    __name__ = new str("PropertyManager");

    FUNCTION_PROPERTY_FLAG = __mepinta__::__pipeline__::__lo__::__constants__::FUNCTION_PROPERTY_FLAG;
    INPUT_PROPERTY_FLAG = __mepinta__::__pipeline__::__lo__::__constants__::INPUT_PROPERTY_FLAG;
    NULL_UID = __mepinta__::__pipeline__::__lo__::__constants__::NULL_UID;
    FUNCTUM_PROPERTY_FLAG = __mepinta__::__pipeline__::__lo__::__constants__::FUNCTUM_PROPERTY_FLAG;
    cl_PropertyManager = new class_("PropertyManager");
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
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/property_manager/PropertyManager.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
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
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/property_manager/PropertyManager.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_property_manager_PropertyManager;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __property_manager__ { /* XXX */
namespace __PropertyManager__ { /* XXX */

/* class PropertyManager */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__property_manager__::__PropertyManager__::PropertyManager *__ss_object;
} __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject;

static PyMemberDef __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_createFuncProperties(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<str *> *arg_1 = __ss_arg<list<str *> *>("prop_names", 1, 0, 0, args, kwargs);
        list<__ss_int> *arg_2 = __ss_arg<list<__ss_int> *>("func_ptr_ids", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)self)->__ss_object->createFuncProperties(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_removeFilters(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)self)->__ss_object->removeFilters(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_deleteProperties(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)self)->__ss_object->deleteProperties(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_addNonCached(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("dent_ids", 1, 0, 0, args, kwargs);
        list<__ss_int> *arg_2 = __ss_arg<list<__ss_int> *>("dency_ids", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)self)->__ss_object->addNonCached(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_createProperties(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<str *> *arg_1 = __ss_arg<list<str *> *>("prop_names", 1, 0, 0, args, kwargs);
        list<__ss_int> *arg_2 = __ss_arg<list<__ss_int> *>("dtype_ids", 2, 0, 0, args, kwargs);
        __ss_int arg_3 = __ss_arg<__ss_int >("prop_flags", 3, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)self)->__ss_object->createProperties(arg_0, arg_1, arg_2, arg_3));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_addFilters(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)self)->__ss_object->addFilters(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_createFunctumProperties(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<str *> *arg_1 = __ss_arg<list<str *> *>("prop_names", 1, 0, 0, args, kwargs);
        list<__ss_int> *arg_2 = __ss_arg<list<__ss_int> *>("func_ptr_ids", 2, 0, 0, args, kwargs);
        list<__ss_int> *arg_3 = __ss_arg<list<__ss_int> *>("dtype_ids", 3, 0, 0, args, kwargs);
        __ss_int arg_4 = __ss_arg<__ss_int >("prop_flags", 4, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)self)->__ss_object->createFunctumProperties(arg_0, arg_1, arg_2, arg_3, arg_4));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_removeNonCached(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("dent_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)self)->__ss_object->removeNonCached(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)self)->__ss_object->__init__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"createFuncProperties", (PyCFunction)__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_createFuncProperties, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"removeFilters", (PyCFunction)__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_removeFilters, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"deleteProperties", (PyCFunction)__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_deleteProperties, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"addNonCached", (PyCFunction)__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_addNonCached, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"createProperties", (PyCFunction)__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_createProperties, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"addFilters", (PyCFunction)__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_addFilters, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"createFunctumProperties", (PyCFunction)__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_createFunctumProperties, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"removeNonCached", (PyCFunction)__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_removeNonCached, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *self = (__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__property_manager__::__PropertyManager__::PropertyManager();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__property_manager__::__PropertyManager__::cl_PropertyManager;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerDealloc(__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_p_value_mngr(__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->p_value_mngr);
}

int __ss_set___ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_p_value_mngr(__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->p_value_mngr = __to_ss<__mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_context_lo(__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->context_lo);
}

int __ss_set___ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_context_lo(__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerGetSet[] = {
    {(char *)"p_value_mngr", (getter)__ss_get___ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_p_value_mngr, (setter)__ss_set___ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_p_value_mngr, (char *)"", NULL},
    {(char *)"context_lo", (getter)__ss_get___ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_context_lo, (setter)__ss_set___ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_context_lo, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "PropertyManager.PropertyManager",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_property_manager_PropertyManager, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(2);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)self)->__ss_object->p_value_mngr));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)self)->__ss_object->context_lo));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)self)->__ss_object->p_value_mngr = __to_ss<__mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)self)->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(PyTuple_GetItem(state, 1));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __property_manager__
} // namespace __PropertyManager__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __property_manager__ { /* XXX */
namespace __PropertyManager__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_property_manager_PropertyManager_shedskin_PropertyManager(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 1, 0, 0, args, kwargs);
        __ss_int arg_2 = __ss_arg<__ss_int >("prop_id", 2, 0, 0, args, kwargs);

        return __to_py(__PropertyManager__::shedskin_PropertyManager(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_property_manager_PropertyManager_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_property_manager_PropertyManagerMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_PropertyManager", (PyCFunction)Global_mepinta_pipeline_lo_property_manager_PropertyManager_shedskin_PropertyManager, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_property_manager_PropertyManager(void) {

    __ss_mod_mepinta_pipeline_lo_property_manager_PropertyManager = Py_InitModule((char *)"PropertyManager", Global_mepinta_pipeline_lo_property_manager_PropertyManagerMethods);
    if(!__ss_mod_mepinta_pipeline_lo_property_manager_PropertyManager)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_property_manager_PropertyManager, "PropertyManager", (PyObject *)&__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_property_manager_PropertyManager(void) {
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_property_manager_PropertyManager, (char *)"INPUT_PROPERTY_FLAG", __to_py(__PropertyManager__::INPUT_PROPERTY_FLAG));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_property_manager_PropertyManager, (char *)"FUNCTUM_PROPERTY_FLAG", __to_py(__PropertyManager__::FUNCTUM_PROPERTY_FLAG));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_property_manager_PropertyManager, (char *)"FUNCTION_PROPERTY_FLAG", __to_py(__PropertyManager__::FUNCTION_PROPERTY_FLAG));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_property_manager_PropertyManager, (char *)"NULL_UID", __to_py(__PropertyManager__::NULL_UID));

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __property_manager__

} // namespace __PropertyManager__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __property_manager__ { /* XXX */
namespace __PropertyManager__ { /* XXX */

PyObject *PropertyManager::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *self = (__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)(__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__property_manager__::__PropertyManager__::PropertyManager *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__property_manager__::__PropertyManager__::__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (PropertyManager expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__property_manager__::__PropertyManager__::__ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObject *)p)->__ss_object;
}
}
