#include "builtin.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "copy.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "sys.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/value_manager/ValueManager.hpp"
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
namespace __value_manager__ {
namespace __ValueManager__ {

str *const_0, *const_1, *const_2, *const_3, *const_4, *const_5, *const_6;

using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::strCharpToVoidp;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::doubleToVoidp;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::intToVoidp;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::voidpToDouble;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::voidpToInt;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::voidpCharpToStr;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::strStringToVoidp;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::voidpStringToStr;
using __pipeline_backend__::__logging__::__logging__::logDebug;
using __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager;

str *__name__;



/**
class ValueManager
*/

class_ *cl_ValueManager;

void *ValueManager::markChangeSetChangedProps(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids) {
    /**
    Add the changed properties of a "ChangeSet"
    :param pline: a pipeline (lo)
    :param prop_ids: a list of properties ids
    */
    __iter<__ss_int> *__135;
    list<__ss_int> *__134;
    __ss_int __136, p_id;
    list<__ss_int>::for_in_loop __137;


    FOR_IN(p_id,prop_ids,134,136,137)
        ((pline->getTopology(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::default_4))->changed_primary)->add(p_id);
    END_FOR

    return NULL;
}

list<__ss_int> *ValueManager::getInts(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids) {
    __iter<__ss_int> *__185;
    list<__ss_int> *__184, *prop_values;
    __ss_int __186, p_id;
    list<__ss_int>::for_in_loop __187;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop;

    prop_values = (new list<__ss_int>());

    FOR_IN(p_id,prop_ids,184,186,187)
        prop = (pline->all_properties)->__getitem__(p_id);
        if (__eq((((this->context_lo)->data_types)->__getitem__(prop->dtype_id))->name, const_0)) {
            prop_values->append(voidpToInt((prop->getValuePtr())->getValue()));
        }
    END_FOR

    return prop_values;
}

list<void *> *ValueManager::getUntypedPropsValues(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids) {
    __iter<__ss_int> *__145;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop;
    list<void *> *prop_values;
    list<__ss_int> *__144;
    list<__ss_int>::for_in_loop __147;
    __ss_int __146, p_id;

    prop_values = (new list<void *>());

    FOR_IN(p_id,prop_ids,144,146,147)
        prop = (pline->all_properties)->__getitem__(p_id);
        prop_values->append((prop->getValuePtr())->getValue());
    END_FOR

    return prop_values;
}

list<str *> *ValueManager::getCharps(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids) {
    list<str *> *prop_values;
    __iter<__ss_int> *__177;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop;
    list<__ss_int> *__176;
    list<__ss_int>::for_in_loop __179;
    __ss_int __178, p_id;

    prop_values = (new list<str *>());

    FOR_IN(p_id,prop_ids,176,178,179)
        prop = (pline->all_properties)->__getitem__(p_id);
        if (__eq((((this->context_lo)->data_types)->__getitem__(prop->dtype_id))->name, const_1)) {
            prop_values->append(voidpCharpToStr((prop->getValuePtr())->getValue()));
        }
    END_FOR

    return prop_values;
}

list<str *> *ValueManager::getStdStrings(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids) {
    __iter<__ss_int> *__173;
    list<str *> *prop_values;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop;
    list<__ss_int> *__172;
    list<__ss_int>::for_in_loop __175;
    __ss_int __174, p_id;

    prop_values = (new list<str *>());

    FOR_IN(p_id,prop_ids,172,174,175)
        prop = (pline->all_properties)->__getitem__(p_id);
        if (__eq((((this->context_lo)->data_types)->__getitem__(prop->dtype_id))->name, const_2)) {
            prop_values->append(voidpStringToStr((prop->getValuePtr())->getValue()));
        }
    END_FOR

    return prop_values;
}

void *ValueManager::setUntypedPropsValues(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids, list<void *> *prop_values) {
    __iter<tuple2<__ss_int, __ss_int> *> *__139, *__140;
    tuple2<__ss_int, __ss_int> *__138;
    list<__ss_int> *__142;
    __ss_int __141, index, p_id;
    __iter<tuple2<__ss_int, __ss_int> *>::for_in_loop __143;


    FOR_IN_ENUM(p_id,prop_ids,142,141)
        index = __141;
        this->__setPropValue(pline, p_id, prop_values->__getfast__(index));
    END_FOR

    return NULL;
}

void *ValueManager::markChangedProps(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids) {
    /**
    Add the changed properties (but do not below to a ChangeSet,
      when animating for example)
    :param pline: a pipeline (lo)
    :param prop_ids: a list of properties ids
    */
    __iter<__ss_int> *__131;
    list<__ss_int> *__130;
    __ss_int __132, p_id;
    list<__ss_int>::for_in_loop __133;


    FOR_IN(p_id,prop_ids,130,132,133)
        (pline->changed_primary)->add(p_id);
    END_FOR

    return NULL;
}

void *ValueManager::__setPropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, void *value) {
    /**
    Directly passing a void*, no need for casting and checking (checking must be done before)
    */
    
    logDebug(__modct(const_3, 1, ___box(prop_id)));
    (this->p_value_mngr)->replacePropValue((pline->all_properties)->__getitem__(prop_id), value);
    (pline->changed_primary)->add(prop_id);
    return NULL;
}

void *ValueManager::setDoubles(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids, list<double> *prop_values) {
    tuple2<__ss_int, __ss_int> *__160;
    list<__ss_int> *__164;
    __ss_int __163, index, p_id;
    __iter<tuple2<__ss_int, __ss_int> *>::for_in_loop __165;
    __iter<tuple2<__ss_int, __ss_int> *> *__161, *__162;


    FOR_IN_ENUM(p_id,prop_ids,164,163)
        index = __163;
        this->__setPropValue(pline, p_id, doubleToVoidp(prop_values->__getfast__(index)));
    END_FOR

    return NULL;
}

void *ValueManager::setCharps(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids, list<str *> *prop_values) {
    tuple2<__ss_int, __ss_int> *__154;
    list<__ss_int> *__158;
    __iter<tuple2<__ss_int, __ss_int> *> *__155, *__156;
    __ss_int __157, index, p_id;
    __iter<tuple2<__ss_int, __ss_int> *>::for_in_loop __159;


    FOR_IN_ENUM(p_id,prop_ids,158,157)
        index = __157;
        this->__setPropValue(pline, p_id, strCharpToVoidp(prop_values->__getfast__(index)));
    END_FOR

    return NULL;
}

list<double> *ValueManager::getDoubles(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids) {
    __iter<__ss_int> *__181;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop;
    list<__ss_int> *__180;
    list<double> *prop_values;
    list<__ss_int>::for_in_loop __183;
    __ss_int __182, p_id;

    prop_values = (new list<double>());

    FOR_IN(p_id,prop_ids,180,182,183)
        prop = (pline->all_properties)->__getitem__(p_id);
        if (__eq((((this->context_lo)->data_types)->__getitem__(prop->dtype_id))->name, const_4)) {
            prop_values->append(voidpToDouble((prop->getValuePtr())->getValue()));
        }
    END_FOR

    return prop_values;
}

void *ValueManager::setStdStrings(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids, list<str *> *prop_values) {
    list<__ss_int> *__152;
    tuple2<__ss_int, __ss_int> *__148;
    __iter<tuple2<__ss_int, __ss_int> *> *__149, *__150;
    __ss_int __151, index, p_id;
    __iter<tuple2<__ss_int, __ss_int> *>::for_in_loop __153;


    FOR_IN_ENUM(p_id,prop_ids,152,151)
        index = __151;
        this->__setPropValue(pline, p_id, strStringToVoidp(prop_values->__getfast__(index)));
    END_FOR

    return NULL;
}

void *ValueManager::__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
    
    this->context_lo = context_lo;
    this->p_value_mngr = (new __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager(context_lo));
    return NULL;
}

void *ValueManager::setInts(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids, list<__ss_int> *prop_values) {
    list<__ss_int> *__170;
    tuple2<__ss_int, __ss_int> *__166;
    __iter<tuple2<__ss_int, __ss_int> *> *__167, *__168;
    __ss_int __169, index, p_id;
    __iter<tuple2<__ss_int, __ss_int> *>::for_in_loop __171;


    FOR_IN_ENUM(p_id,prop_ids,170,169)
        index = __169;
        this->__setPropValue(pline, p_id, intToVoidp(prop_values->__getfast__(index)));
    END_FOR

    return NULL;
}

void *shedskin_ValueManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id) {
    list<__ss_int> *prop_ids;
    ValueManager *vm;

    vm = (new ValueManager(context_lo));
    prop_ids = (new list<__ss_int>(1,prop_id));
    vm->markChangedProps(pline, prop_ids);
    vm->markChangeSetChangedProps(pline, prop_ids);
    vm->setStdStrings(pline, prop_ids, (new list<str *>(1,const_5)));
    vm->setCharps(pline, prop_ids, (new list<str *>(1,const_5)));
    vm->setInts(pline, prop_ids, (new list<__ss_int>(1,1)));
    vm->setDoubles(pline, prop_ids, (new list<double>(1,1.1)));
    vm->setUntypedPropsValues(pline, prop_ids, (new list<void *>(1,NULL)));
    vm->getStdStrings(pline, prop_ids);
    vm->getCharps(pline, prop_ids);
    vm->getDoubles(pline, prop_ids);
    vm->getInts(pline, prop_ids);
    vm->getUntypedPropsValues(pline, prop_ids);
    return NULL;
}

void __init() {
    const_0 = new str("int");
    const_1 = new str("charp");
    const_2 = new str("cpp_std_string");
    const_3 = new str("Setting value to prop_id=%r");
    const_4 = new str("double");
    const_5 = new str("value");
    const_6 = new str("__main__");

    __name__ = new str("ValueManager");

    cl_ValueManager = new class_("ValueManager");
    if (__eq(__name__, const_6)) {
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
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "copy.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "sys.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/value_manager/ValueManager.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include <structmember.h>
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "copy.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "sys.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/value_manager/ValueManager.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_value_manager_ValueManager;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __value_manager__ { /* XXX */
namespace __ValueManager__ { /* XXX */

/* class ValueManager */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__value_manager__::__ValueManager__::ValueManager *__ss_object;
} __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject;

static PyMemberDef __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_markChangeSetChangedProps(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->markChangeSetChangedProps(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_getInts(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->getInts(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_getUntypedPropsValues(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->getUntypedPropsValues(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_getCharps(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->getCharps(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_getStdStrings(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->getStdStrings(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_setUntypedPropsValues(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);
        list<void *> *arg_2 = __ss_arg<list<void *> *>("prop_values", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->setUntypedPropsValues(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_markChangedProps(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->markChangedProps(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager___setPropValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("prop_id", 1, 0, 0, args, kwargs);
        void *arg_2 = __ss_arg<void *>("value", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->__setPropValue(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_setDoubles(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);
        list<double> *arg_2 = __ss_arg<list<double> *>("prop_values", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->setDoubles(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_setCharps(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);
        list<str *> *arg_2 = __ss_arg<list<str *> *>("prop_values", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->setCharps(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_getDoubles(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->getDoubles(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_setStdStrings(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);
        list<str *> *arg_2 = __ss_arg<list<str *> *>("prop_values", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->setStdStrings(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->__init__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_setInts(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("prop_ids", 1, 0, 0, args, kwargs);
        list<__ss_int> *arg_2 = __ss_arg<list<__ss_int> *>("prop_values", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->setInts(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"markChangeSetChangedProps", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_markChangeSetChangedProps, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getInts", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_getInts, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getUntypedPropsValues", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_getUntypedPropsValues, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getCharps", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_getCharps, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getStdStrings", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_getStdStrings, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"setUntypedPropsValues", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_setUntypedPropsValues, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"markChangedProps", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_markChangedProps, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setPropValue", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager___setPropValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"setDoubles", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_setDoubles, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"setCharps", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_setCharps, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getDoubles", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_getDoubles, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"setStdStrings", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_setStdStrings, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"setInts", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_setInts, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *self = (__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__value_manager__::__ValueManager__::ValueManager();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__value_manager__::__ValueManager__::cl_ValueManager;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerDealloc(__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_p_value_mngr(__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->p_value_mngr);
}

int __ss_set___ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_p_value_mngr(__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->p_value_mngr = __to_ss<__mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_context_lo(__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->context_lo);
}

int __ss_set___ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_context_lo(__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerGetSet[] = {
    {(char *)"p_value_mngr", (getter)__ss_get___ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_p_value_mngr, (setter)__ss_set___ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_p_value_mngr, (char *)"", NULL},
    {(char *)"context_lo", (getter)__ss_get___ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_context_lo, (setter)__ss_set___ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_context_lo, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "ValueManager.ValueManager",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_value_manager_ValueManager, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(2);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->p_value_mngr));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->context_lo));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->p_value_mngr = __to_ss<__mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)self)->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(PyTuple_GetItem(state, 1));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __value_manager__
} // namespace __ValueManager__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __value_manager__ { /* XXX */
namespace __ValueManager__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_value_manager_ValueManager_shedskin_ValueManager(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 1, 0, 0, args, kwargs);
        __ss_int arg_2 = __ss_arg<__ss_int >("prop_id", 2, 0, 0, args, kwargs);

        return __to_py(__ValueManager__::shedskin_ValueManager(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_value_manager_ValueManager_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_value_manager_ValueManagerMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_ValueManager", (PyCFunction)Global_mepinta_pipeline_lo_value_manager_ValueManager_shedskin_ValueManager, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_value_manager_ValueManager(void) {

    __ss_mod_mepinta_pipeline_lo_value_manager_ValueManager = Py_InitModule((char *)"ValueManager", Global_mepinta_pipeline_lo_value_manager_ValueManagerMethods);
    if(!__ss_mod_mepinta_pipeline_lo_value_manager_ValueManager)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_value_manager_ValueManager, "ValueManager", (PyObject *)&__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_value_manager_ValueManager(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __value_manager__

} // namespace __ValueManager__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __value_manager__ { /* XXX */
namespace __ValueManager__ { /* XXX */

PyObject *ValueManager::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *self = (__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)(__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__value_manager__::__ValueManager__::ValueManager *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__value_manager__::__ValueManager__::__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (ValueManager expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__value_manager__::__ValueManager__::__ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObject *)p)->__ss_object;
}
}
