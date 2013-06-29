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
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
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
namespace __pipeline_evaluator__ {
namespace __ProcessorArgsManager__ {

using __pipeline_backend__::__args_management__::__args_management__::createArgs;
using __pipeline_backend__::__args_management__::__args_management__::argsAppendProp;
using __pipeline_backend__::__args_management__::__args_management__::argsSetChanged;
using __pipeline_backend__::__args_management__::__args_management__::argsSetUnchanged;
using __pipeline_backend__::__args_management__::__args_management__::argsBuildChangedSet;
using __pipeline_backend__::__args_management__::__args_management__::argsSetCapacity;
using __pipeline_backend__::__args_management__::__args_management__::getThreadArgs;
using __pipeline_backend__::__args_management__::__args_management__::argsSetThreadId;

str *__name__;
__ss_int CUSTOM_INPUT_PROPS, CUSTOM_OUTPUT_PROPS, INPUT_PROPS, OUTPUT_PROPS;



/**
class ProcessorArgsManager
*/

class_ *cl_ProcessorArgsManager;

void *ProcessorArgsManager::unchangedValue() {
    
    argsSetUnchanged(this->args, this->in_out_id, this->__getCurrentIndex());
    return NULL;
}

void *ProcessorArgsManager::changedValue() {
    
    argsSetChanged(this->args, this->in_out_id, this->__getCurrentIndex());
    return NULL;
}

void *ProcessorArgsManager::createArgs(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *func_prop_value, __ss_int thread_id) {
    
    if ((func_prop_value->args==NULL)) {
        this->new_args = True;
        func_prop_value->args = __pipeline_backend__::__args_management__::__args_management__::createArgs(0, 0);
    }
    else {
        this->new_args = False;
    }
    argsSetThreadId(func_prop_value->args, thread_id);
    return func_prop_value->args;
}

set<__ss_int> *ProcessorArgsManager::buildChangedSet() {
    set<__ss_int> *changed;

    changed = (new set<__ss_int>());
    argsBuildChangedSet(this->args, OUTPUT_PROPS, changed);
    argsBuildChangedSet(this->args, CUSTOM_OUTPUT_PROPS, changed);
    return changed;
}

void *ProcessorArgsManager::nextProp() {
    
    this->__incrementCurrentIndex(1);
    return NULL;
}

__ss_int ProcessorArgsManager::__getCurrentIndex() {
    
    return (this->indexes)->__getitem__(this->in_out_id);
}

void *ProcessorArgsManager::setInOut(__ss_int in_out_id) {
    
    this->in_out_id = in_out_id;
    return NULL;
}

void *ProcessorArgsManager::append(__ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop_real) {
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *data_type;

    data_type = ((this->context_lo)->data_types)->__getitem__(prop_real->dtype_id);
    argsAppendProp(this->args, this->in_out_id, this->__getCurrentIndex(), prop_id, prop, prop_real, data_type);
    return NULL;
}

void *ProcessorArgsManager::__incrementCurrentIndex(__ss_int delta) {
    dict<__ss_int, __ss_int> *__228;
    __ss_int __229;

    this->indexes->__addtoitem__(this->in_out_id, delta);
    return NULL;
}

void *ProcessorArgsManager::getArgs() {
    
    return this->args;
}

void *ProcessorArgsManager::__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *func_prop_value, __ss_int thread_id) {
    
    this->context_lo = context_lo;
    this->args = this->createArgs(func_prop_value, thread_id);
    this->indexes = (new dict<__ss_int, __ss_int>(4, (new tuple2<__ss_int , __ss_int >(2,INPUT_PROPS,0)),(new tuple2<__ss_int , __ss_int >(2,OUTPUT_PROPS,0)),(new tuple2<__ss_int , __ss_int >(2,CUSTOM_INPUT_PROPS,0)),(new tuple2<__ss_int , __ss_int >(2,CUSTOM_OUTPUT_PROPS,0))));
    this->marked = False;
    return NULL;
}

ProcessorArgsManager *shedskin_ProcessorArgsManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *func_prop_value, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    __ss_int prop_id;
    ProcessorArgsManager *pam;

    pam = (new ProcessorArgsManager(context_lo, func_prop_value, 0));
    prop_id = 100;
    pam->setInOut(1);
    pam->append(prop_id, prop, prop);
    pam->getArgs();
    pam->nextProp();
    pam->append(prop_id, prop, prop);
    pam->changedValue();
    pam->unchangedValue();
    pam->buildChangedSet();
    return pam;
}

void __init() {
    __name__ = new str("ProcessorArgsManager");

    OUTPUT_PROPS = __mepinta__::__pipeline__::__lo__::__constants__::OUTPUT_PROPS;
    CUSTOM_OUTPUT_PROPS = __mepinta__::__pipeline__::__lo__::__constants__::CUSTOM_OUTPUT_PROPS;
    INPUT_PROPS = __mepinta__::__pipeline__::__lo__::__constants__::INPUT_PROPS;
    CUSTOM_INPUT_PROPS = __mepinta__::__pipeline__::__lo__::__constants__::CUSTOM_INPUT_PROPS;
    cl_ProcessorArgsManager = new class_("ProcessorArgsManager");
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
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
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
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __ProcessorArgsManager__ { /* XXX */

/* class ProcessorArgsManager */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *__ss_object;
} __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject;

static PyMemberDef __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_unchangedValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->unchangedValue());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_changedValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->changedValue());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_createArgs(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *>("func_prop_value", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("thread_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->createArgs(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_buildChangedSet(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->buildChangedSet());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_nextProp(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->nextProp());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager___getCurrentIndex(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->__getCurrentIndex());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_setInOut(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("in_out_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->setInOut(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_append(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("prop_id", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop_real", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->append(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager___incrementCurrentIndex(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("delta", 0, 1, 1, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->__incrementCurrentIndex(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_getArgs(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->getArgs());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *>("func_prop_value", 1, 0, 0, args, kwargs);
        __ss_int arg_2 = __ss_arg<__ss_int >("thread_id", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->__init__(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"unchangedValue", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_unchangedValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"changedValue", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_changedValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"createArgs", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_createArgs, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"buildChangedSet", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_buildChangedSet, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"nextProp", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_nextProp, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__getCurrentIndex", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager___getCurrentIndex, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"setInOut", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_setInOut, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"append", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_append, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__incrementCurrentIndex", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager___incrementCurrentIndex, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getArgs", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_getArgs, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self = (__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::cl_ProcessorArgsManager;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerDealloc(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_args(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->args);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_args(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->args = NULL;
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_marked(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->marked);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_marked(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->marked = __to_ss<__ss_bool >(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_in_out_id(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->in_out_id);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_in_out_id(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->in_out_id = __to_ss<__ss_int >(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_new_args(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->new_args);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_new_args(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->new_args = __to_ss<__ss_bool >(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_indexes(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->indexes);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_indexes(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->indexes = __to_ss<dict<__ss_int, __ss_int> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_context_lo(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self, void *closure) {
    return __to_py(self->__ss_object->context_lo);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_context_lo(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerGetSet[] = {
    {(char *)"args", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_args, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_args, (char *)"", NULL},
    {(char *)"marked", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_marked, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_marked, (char *)"", NULL},
    {(char *)"in_out_id", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_in_out_id, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_in_out_id, (char *)"", NULL},
    {(char *)"new_args", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_new_args, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_new_args, (char *)"", NULL},
    {(char *)"indexes", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_indexes, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_indexes, (char *)"", NULL},
    {(char *)"context_lo", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_context_lo, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_context_lo, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "ProcessorArgsManager.ProcessorArgsManager",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(6);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->args));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->marked));
    PyTuple_SetItem(b, 2, __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->in_out_id));
    PyTuple_SetItem(b, 3, __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->new_args));
    PyTuple_SetItem(b, 4, __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->indexes));
    PyTuple_SetItem(b, 5, __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->context_lo));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManager__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->args = __to_ss<void *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->marked = __to_ss<__ss_bool >(PyTuple_GetItem(state, 1));
    ((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->in_out_id = __to_ss<__ss_int >(PyTuple_GetItem(state, 2));
    ((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->new_args = __to_ss<__ss_bool >(PyTuple_GetItem(state, 3));
    ((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->indexes = __to_ss<dict<__ss_int, __ss_int> *>(PyTuple_GetItem(state, 4));
    ((__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)self)->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(PyTuple_GetItem(state, 5));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __pipeline_evaluator__
} // namespace __ProcessorArgsManager__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __ProcessorArgsManager__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_shedskin_ProcessorArgsManager(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *>("func_prop_value", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 2, 0, 0, args, kwargs);

        return __to_py(__ProcessorArgsManager__::shedskin_ProcessorArgsManager(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManagerMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_ProcessorArgsManager", (PyCFunction)Global_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_shedskin_ProcessorArgsManager, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager(void) {

    __ss_mod_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager = Py_InitModule((char *)"ProcessorArgsManager", Global_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManagerMethods);
    if(!__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager, "ProcessorArgsManager", (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager(void) {
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager, (char *)"CUSTOM_OUTPUT_PROPS", __to_py(__ProcessorArgsManager__::CUSTOM_OUTPUT_PROPS));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager, (char *)"INPUT_PROPS", __to_py(__ProcessorArgsManager__::INPUT_PROPS));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager, (char *)"CUSTOM_INPUT_PROPS", __to_py(__ProcessorArgsManager__::CUSTOM_INPUT_PROPS));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager, (char *)"OUTPUT_PROPS", __to_py(__ProcessorArgsManager__::OUTPUT_PROPS));

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __pipeline_evaluator__

} // namespace __ProcessorArgsManager__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __ProcessorArgsManager__ { /* XXX */

PyObject *ProcessorArgsManager::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *self = (__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)(__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (ProcessorArgsManager expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::__ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObject *)p)->__ss_object;
}
}
