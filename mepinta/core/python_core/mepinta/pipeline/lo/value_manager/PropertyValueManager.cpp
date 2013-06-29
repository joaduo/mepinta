#include "builtin.hpp"
#include "copy.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
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
namespace __value_manager__ {
namespace __PropertyValueManager__ {

str *const_0, *const_1, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;

using __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller;
using __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer;
using __pipeline_backend__::__args_management__::__args_management__::deleteArgs;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::voidp_to_FunctionPropertyValue;
using __pipeline_backend__::__logging__::__logging__::logDebug;

str *__name__;
__ss_int FUNCTION_PROPERTY_FLAG;



/**
class PropertyValueManager
*/

class_ *cl_PropertyValueManager;

void *PropertyValueManager::replacePropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, void *value) {
    void *func_ptr_del;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *data_type;

    logDebug(__modct(const_0, 1, prop));
    if (((prop->getValuePtr())->getValue()==NULL)) {
        (prop->getValuePtr())->replaceValue(value, NULL);
    }
    else {
        data_type = ((this->context_lo)->data_types)->__getitem__(prop->dtype_id);
        func_ptr_del = data_type->getFuncPtr(const_1);
        (prop->getValuePtr())->replaceValue(value, func_ptr_del);
    }
    return NULL;
}

void *PropertyValueManager::copyPropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *value_ptr) {
    void *func_ptr_copy, *value_copy;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *data_type;

    logDebug(__modct(const_2, 1, prop));
    data_type = ((this->context_lo)->data_types)->__getitem__(prop->dtype_id);
    func_ptr_copy = data_type->getFuncPtr(const_3);
    if ((func_ptr_copy!=NULL)) {
        if (((prop->getValuePtr())->getValue()==NULL)) {
            this->initPropValue(prop);
        }
        logDebug(__modct(const_4, 2, prop, value_ptr));
        (this->func_caller)->callCopyToFunc(func_ptr_copy, (prop->getValuePtr())->getValue(), value_ptr->getValue());
    }
    else {
        func_ptr_copy = data_type->getFuncPtr(const_5);
        value_copy = (this->func_caller)->callFunc(func_ptr_copy, value_ptr->getValue());
        this->setPropValuePointer(prop, (new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer(value_copy)));
    }
    return NULL;
}

void *PropertyValueManager::setPropValuePointer(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *value_ptr) {
    void *func_ptr_del;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *data_type;

    logDebug(__modct(const_6, 1, prop));
    data_type = ((this->context_lo)->data_types)->__getitem__(prop->dtype_id);
    func_ptr_del = data_type->getFuncPtr(const_1);
    prop->setValuePtr(value_ptr, func_ptr_del);
    return NULL;
}

void *PropertyValueManager::initPropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    /**
    */
    void *func_ptr_del, *func_ptr_new, *value;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *data_type;

    logDebug(__modct(const_7, 1, prop));
    if (((prop->getValuePtr())->getValue()==NULL)) {
        func_ptr_del = NULL;
        data_type = ((this->context_lo)->data_types)->__getitem__(prop->dtype_id);
        func_ptr_new = data_type->getFuncPtr(const_8);
        value = (this->func_caller)->callFuncNoArgs(func_ptr_new);
        (prop->getValuePtr())->replaceValue(value, func_ptr_del);
    }
    return NULL;
}

void *PropertyValueManager::deletePropsValues(list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *props) {
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *data_type;
    list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *__126;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop;
    void *func_ptr_del, *value;
    __iter<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *__127;
    __ss_int __128;
    list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>::for_in_loop __129;


    FOR_IN(prop,props,126,128,129)
        logDebug(__modct(const_9, 1, prop));
        value = (prop->getValuePtr())->getValue();
        if ((value!=NULL)) {
            if ((prop->type==FUNCTION_PROPERTY_FLAG)) {
                deleteArgs((voidp_to_FunctionPropertyValue(value))->args);
            }
            else {
                data_type = ((this->context_lo)->data_types)->__getitem__(prop->dtype_id);
                func_ptr_del = data_type->getFuncPtr(const_1);
                (prop->getValuePtr())->decrementReferenceCount(func_ptr_del);
            }
        }
    END_FOR

    return NULL;
}

void *PropertyValueManager::__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
    
    this->context_lo = context_lo;
    this->func_caller = (new __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller());
    return NULL;
}

void *shedskin_PropertyValueManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *value_ptr;
    void *value;
    PropertyValueManager *pvm;

    pvm = (new PropertyValueManager(context_lo));
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
    const_0 = new str("Replacing prop value for prop %r.");
    const_1 = new str("delete");
    const_2 = new str("Copying value for prop %r.");
    const_3 = new str("copyTo");
    const_4 = new str("Using copyTo for copying values to prop:%r from value_ptr:%r");
    const_5 = new str("copy");
    const_6 = new str("Setting value for prop %r.");
    const_7 = new str("Initializing value for prop %r.");
    const_8 = new str("new");
    const_9 = new str("Deleting value for prop %r.");

    __name__ = new str("PropertyValueManager");

    FUNCTION_PROPERTY_FLAG = __mepinta__::__pipeline__::__lo__::__constants__::FUNCTION_PROPERTY_FLAG;
    cl_PropertyValueManager = new class_("PropertyValueManager");
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
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
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
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_value_manager_PropertyValueManager;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __value_manager__ { /* XXX */
namespace __PropertyValueManager__ { /* XXX */

/* class PropertyValueManager */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *__ss_object;
} __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject;

static PyMemberDef __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_replacePropValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 0, 0, 0, args, kwargs);
        void *arg_1 = __ss_arg<void *>("value", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *)self)->__ss_object->replacePropValue(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_copyPropValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *>("value_ptr", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *)self)->__ss_object->copyPropValue(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_setPropValuePointer(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *>("value_ptr", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *)self)->__ss_object->setPropValuePointer(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_initPropValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *)self)->__ss_object->initPropValue(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_deletePropsValues(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *arg_0 = __ss_arg<list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *>("props", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *)self)->__ss_object->deletePropsValues(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *)self)->__ss_object->__init__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"replacePropValue", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_replacePropValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"copyPropValue", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_copyPropValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"setPropValuePointer", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_setPropValuePointer, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"initPropValue", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_initPropValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"deletePropsValues", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_deletePropsValues, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *self = (__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::cl_PropertyValueManager;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerDealloc(__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_func_caller(__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->func_caller);
}

int __ss_set___ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_func_caller(__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->func_caller = __to_ss<__mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_context_lo(__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->context_lo);
}

int __ss_set___ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_context_lo(__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerGetSet[] = {
    {(char *)"func_caller", (getter)__ss_get___ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_func_caller, (setter)__ss_set___ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_func_caller, (char *)"", NULL},
    {(char *)"context_lo", (getter)__ss_get___ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_context_lo, (setter)__ss_set___ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_context_lo, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "PropertyValueManager.PropertyValueManager",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_value_manager_PropertyValueManager, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(2);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *)self)->__ss_object->func_caller));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *)self)->__ss_object->context_lo));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *)self)->__ss_object->func_caller = __to_ss<__mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *)self)->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(PyTuple_GetItem(state, 1));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __value_manager__
} // namespace __PropertyValueManager__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __value_manager__ { /* XXX */
namespace __PropertyValueManager__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_value_manager_PropertyValueManager_shedskin_PropertyValueManager(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 1, 0, 0, args, kwargs);

        return __to_py(__PropertyValueManager__::shedskin_PropertyValueManager(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_value_manager_PropertyValueManager_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_value_manager_PropertyValueManagerMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_PropertyValueManager", (PyCFunction)Global_mepinta_pipeline_lo_value_manager_PropertyValueManager_shedskin_PropertyValueManager, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_value_manager_PropertyValueManager(void) {

    __ss_mod_mepinta_pipeline_lo_value_manager_PropertyValueManager = Py_InitModule((char *)"PropertyValueManager", Global_mepinta_pipeline_lo_value_manager_PropertyValueManagerMethods);
    if(!__ss_mod_mepinta_pipeline_lo_value_manager_PropertyValueManager)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_value_manager_PropertyValueManager, "PropertyValueManager", (PyObject *)&__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_value_manager_PropertyValueManager(void) {
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_value_manager_PropertyValueManager, (char *)"FUNCTION_PROPERTY_FLAG", __to_py(__PropertyValueManager__::FUNCTION_PROPERTY_FLAG));

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __value_manager__

} // namespace __PropertyValueManager__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __value_manager__ { /* XXX */
namespace __PropertyValueManager__ { /* XXX */

PyObject *PropertyValueManager::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *self = (__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *)(__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (PropertyValueManager expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::__ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObject *)p)->__ss_object;
}
}
