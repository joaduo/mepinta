#include "builtin.hpp"
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
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
#include "mepinta/pipeline/lo/value_manager/DebugPropertyValueManager.hpp"
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
namespace __value_manager__ {
namespace __DebugPropertyValueManager__ {

str *const_0, *const_1, *const_2;

using __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer;
using __pipeline_backend__::__logging__::__logging__::logError;
using __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager;
using __mepinta__::__pipeline__::__lo__::__exceptions__::__MepintaLoError__::MepintaLoError;
using __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller;

str *__name__;



/**
class DebugPropertyValueManager
*/

class_ *cl_DebugPropertyValueManager;

void *DebugPropertyValueManager::replacePropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, void *value) {
    
    (this->prop_value_mngr)->replacePropValue(prop, value);
    this->__checkRepr(prop);
    return NULL;
}

void *DebugPropertyValueManager::deletePropsValues(list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *props) {
    list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *__254;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop;
    void *value;
    __iter<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *__255;
    __ss_int __256;
    list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>::for_in_loop __257;


    FOR_IN(prop,props,254,256,257)
        value = (prop->getValuePtr())->getValue();
        if ((value!=NULL)) {
            this->__checkValueRepr(prop, value);
        }
    END_FOR

    (this->prop_value_mngr)->deletePropsValues(props);
    return NULL;
}

void *DebugPropertyValueManager::copyPropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *value_ptr) {
    
    this->__checkValueRepr(prop, value_ptr->getValue());
    (this->prop_value_mngr)->copyPropValue(prop, value_ptr);
    this->__checkRepr(prop);
    return NULL;
}

void *DebugPropertyValueManager::__getCheckReprFunction(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    str *msg;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *data_type;
    void *func_ptr_check_repr;

    data_type = ((this->context_lo)->data_types)->__getitem__(prop->dtype_id);
    func_ptr_check_repr = data_type->getFuncPtr(const_0);
    if ((func_ptr_check_repr==NULL)) {
        msg = __modct(const_1, 1, data_type);
        logError(msg);
        throw ((new __mepinta__::__pipeline__::__lo__::__exceptions__::__MepintaLoError__::MepintaLoError(msg)));
    }
    return func_ptr_check_repr;
}

void *DebugPropertyValueManager::__checkValueRepr(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, void *value) {
    str *msg;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *data_type;
    void *func_ptr_check_repr;

    func_ptr_check_repr = this->__getCheckReprFunction(prop);
    if (__NOT((this->func_caller)->callIntFuncVoidp(func_ptr_check_repr, value))) {
        data_type = ((this->context_lo)->data_types)->__getitem__(prop->dtype_id);
        msg = __modct(const_2, 2, prop, data_type);
        throw ((new __mepinta__::__pipeline__::__lo__::__exceptions__::__MepintaLoError__::MepintaLoError(msg)));
    }
    return NULL;
}

void *DebugPropertyValueManager::initPropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    
    (this->prop_value_mngr)->initPropValue(prop);
    this->__checkRepr(prop);
    return NULL;
}

void *DebugPropertyValueManager::setPropValuePointer(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *value_ptr) {
    
    this->__checkValueRepr(prop, value_ptr->getValue());
    (this->prop_value_mngr)->setPropValuePointer(prop, value_ptr);
    return NULL;
}

void *DebugPropertyValueManager::__checkRepr(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    
    this->__checkRepr(prop);
    return NULL;
}

void *DebugPropertyValueManager::__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
    
    this->context_lo = context_lo;
    this->prop_value_mngr = (new __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager(this->context_lo));
    this->func_caller = (new __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller());
    return NULL;
}

void *shedskin_DebugPropertyValueManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *value_ptr;
    void *value;
    DebugPropertyValueManager *pvm;

    pvm = (new DebugPropertyValueManager(context_lo));
    value = NULL;
    pvm->replacePropValue(prop, value);
    pvm->initPropValue(prop);
    value_ptr = (new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer(NULL));
    pvm->setPropValuePointer(prop, value_ptr);
    pvm->copyPropValue(prop, value_ptr);
    pvm->deletePropsValues((new list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>(1,prop)));
    return NULL;
}

void __init() {
    const_0 = new str("checkRepr");
    const_1 = new str("Cannot find checkRepr function for data_type:%r");
    const_2 = new str("checkRepr failed for prop:%r and data_type:%r");

    __name__ = new str("DebugPropertyValueManager");

    cl_DebugPropertyValueManager = new class_("DebugPropertyValueManager");
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
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
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
#include "mepinta/pipeline/lo/value_manager/DebugPropertyValueManager.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include <structmember.h>
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
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
#include "mepinta/pipeline/lo/value_manager/DebugPropertyValueManager.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __value_manager__ { /* XXX */
namespace __DebugPropertyValueManager__ { /* XXX */

/* class DebugPropertyValueManager */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__value_manager__::__DebugPropertyValueManager__::DebugPropertyValueManager *__ss_object;
} __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject;

static PyMemberDef __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_replacePropValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 0, 0, 0, args, kwargs);
        void *arg_1 = __ss_arg<void *>("value", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->replacePropValue(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_deletePropsValues(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *arg_0 = __ss_arg<list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *>("props", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->deletePropsValues(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_copyPropValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *>("value_ptr", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->copyPropValue(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager___getCheckReprFunction(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->__getCheckReprFunction(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager___checkValueRepr(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 0, 0, 0, args, kwargs);
        void *arg_1 = __ss_arg<void *>("value", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->__checkValueRepr(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_initPropValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->initPropValue(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_setPropValuePointer(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *>("value_ptr", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->setPropValuePointer(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager___checkRepr(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->__checkRepr(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->__init__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"replacePropValue", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_replacePropValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"deletePropsValues", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_deletePropsValues, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"copyPropValue", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_copyPropValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__getCheckReprFunction", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager___getCheckReprFunction, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__checkValueRepr", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager___checkValueRepr, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"initPropValue", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_initPropValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"setPropValuePointer", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_setPropValuePointer, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__checkRepr", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager___checkRepr, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *self = (__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__value_manager__::__DebugPropertyValueManager__::DebugPropertyValueManager();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__value_manager__::__DebugPropertyValueManager__::cl_DebugPropertyValueManager;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerDealloc(__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_func_caller(__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->func_caller);
}

int __ss_set___ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_func_caller(__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->func_caller = __to_ss<__mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_context_lo(__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->context_lo);
}

int __ss_set___ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_context_lo(__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_prop_value_mngr(__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->prop_value_mngr);
}

int __ss_set___ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_prop_value_mngr(__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->prop_value_mngr = __to_ss<__mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerGetSet[] = {
    {(char *)"func_caller", (getter)__ss_get___ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_func_caller, (setter)__ss_set___ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_func_caller, (char *)"", NULL},
    {(char *)"context_lo", (getter)__ss_get___ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_context_lo, (setter)__ss_set___ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_context_lo, (char *)"", NULL},
    {(char *)"prop_value_mngr", (getter)__ss_get___ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_prop_value_mngr, (setter)__ss_set___ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_prop_value_mngr, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "DebugPropertyValueManager.DebugPropertyValueManager",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(3);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->func_caller));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->context_lo));
    PyTuple_SetItem(b, 2, __to_py(((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->prop_value_mngr));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->func_caller = __to_ss<__mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(PyTuple_GetItem(state, 1));
    ((__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)self)->__ss_object->prop_value_mngr = __to_ss<__mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *>(PyTuple_GetItem(state, 2));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __value_manager__
} // namespace __DebugPropertyValueManager__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __value_manager__ { /* XXX */
namespace __DebugPropertyValueManager__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_shedskin_DebugPropertyValueManager(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 1, 0, 0, args, kwargs);

        return __to_py(__DebugPropertyValueManager__::shedskin_DebugPropertyValueManager(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_value_manager_DebugPropertyValueManagerMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_DebugPropertyValueManager", (PyCFunction)Global_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_shedskin_DebugPropertyValueManager, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_value_manager_DebugPropertyValueManager(void) {

    __ss_mod_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager = Py_InitModule((char *)"DebugPropertyValueManager", Global_mepinta_pipeline_lo_value_manager_DebugPropertyValueManagerMethods);
    if(!__ss_mod_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager, "DebugPropertyValueManager", (PyObject *)&__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_value_manager_DebugPropertyValueManager(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __value_manager__

} // namespace __DebugPropertyValueManager__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __value_manager__ { /* XXX */
namespace __DebugPropertyValueManager__ { /* XXX */

PyObject *DebugPropertyValueManager::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *self = (__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)(__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__value_manager__::__DebugPropertyValueManager__::DebugPropertyValueManager *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__value_manager__::__DebugPropertyValueManager__::__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (DebugPropertyValueManager expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__value_manager__::__DebugPropertyValueManager__::__ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObject *)p)->__ss_object;
}
}
