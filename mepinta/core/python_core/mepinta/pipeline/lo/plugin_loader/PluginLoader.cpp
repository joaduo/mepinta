#include "builtin.hpp"
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/load_unload_library/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/load_unload_library/load_unload_library.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/lo/plugin_loader/PluginLoader.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/__init__.hpp"
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
namespace __plugin_loader__ {
namespace __PluginLoader__ {

str *const_0, *const_1, *const_10, *const_11, *const_12, *const_13, *const_14, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;

using __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType;
using __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction;
using __pipeline_backend__::__logging__::__logging__::logInfo;
using __pipeline_backend__::__logging__::__logging__::logDebug;
using __pipeline_backend__::__solve_symbol__::__solve_symbol__::solve_symbol;
using __pipeline_backend__::__load_unload_library__::__load_unload_library__::unloadLibrary;
using __pipeline_backend__::__load_unload_library__::__load_unload_library__::loadLibrary;

str *__name__;



/**
class PluginLoader
*/

class_ *cl_PluginLoader;

__ss_bool PluginLoader::processorIsLoaded(str *path) {
    
    return ((this->context_lo)->processors_paths)->__contains__(path);
}

void *PluginLoader::loadProcessorLibrary(str *path, dict<str *, __ss_int> *func_dict) {
    dict<str *, __ss_int> *__121;
    void *func_ptr, *handle;
    __iter<str *> *__122;
    dict<str *, void *> *__120;
    dict<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction *> *__125;
    str *func_name;
    dict<str *, __ss_int>::for_in_loop __124;
    __ss_int __123, func_id;

    if ((!((this->context_lo)->processors_paths)->__contains__(path))) {
        logInfo(__modct(const_0, 2, path, func_dict));
        handle = loadLibrary(path, const_1);
        (this->context_lo)->processors_paths->__setitem__(path, handle);

        FOR_IN(func_name,func_dict,121,123,124)
            func_id = func_dict->__getitem__(func_name);
            func_ptr = solve_symbol(handle, const_2, func_name);
            if (((this->context_lo)->functions)->__contains__(func_id)) {
                (((this->context_lo)->functions)->__getitem__(func_id))->updateFuncPointer(func_ptr);
            }
            else {
                (this->context_lo)->functions->__setitem__(func_id, (new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction(func_name, func_ptr)));
            }
        END_FOR

    }
    else {
        logDebug(__modct(const_3, 2, path, func_dict));
    }
    return NULL;
}

void *PluginLoader::unloadDataTypeLibrary(str *path, __ss_int dtype_id) {
    
    if (((this->context_lo)->data_types_paths)->__contains__(path)) {
        logInfo(__modct(const_4, 2, path, ___box(dtype_id)));
        unloadLibrary(((this->context_lo)->data_types_paths)->__getitem__(path));
        ((this->context_lo)->data_types_paths)->__delitem__(path);
        (((this->context_lo)->data_types)->__getitem__(dtype_id))->updateHandle(NULL);
    }
    else {
        logDebug(__modct(const_5, 2, path, ___box(dtype_id)));
    }
    return NULL;
}

void *PluginLoader::__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
    
    this->context_lo = context_lo;
    return NULL;
}

void *PluginLoader::unloadProcessorLibrary(str *path, list<__ss_int> *func_ids) {
    __iter<__ss_int> *__117;
    list<__ss_int> *__116;
    __ss_int __118, f_id;
    list<__ss_int>::for_in_loop __119;

    if (((this->context_lo)->processors_paths)->__contains__(path)) {
        logInfo(__modct(const_6, 2, path, func_ids));
        unloadLibrary(((this->context_lo)->processors_paths)->__getitem__(path));

        FOR_IN(f_id,func_ids,116,118,119)
            (((this->context_lo)->functions)->__getitem__(f_id))->updateFuncPointer(NULL);
        END_FOR

        ((this->context_lo)->processors_paths)->__delitem__(path);
    }
    else {
        logDebug(__modct(const_7, 2, path, func_ids));
    }
    return NULL;
}

__ss_bool PluginLoader::dataTypeIsLoaded(str *path) {
    
    return ((this->context_lo)->data_types_paths)->__contains__(path);
}

void *PluginLoader::loadDataTypeLibrary(str *path, str *data_type_name, __ss_int dtype_id) {
    dict<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *> *__115;
    void *handle;
    dict<str *, void *> *__114;

    if ((!((this->context_lo)->data_types_paths)->__contains__(path))) {
        logInfo(__modct(const_8, 3, path, data_type_name, ___box(dtype_id)));
        handle = loadLibrary(path, const_9);
        (this->context_lo)->data_types_paths->__setitem__(path, handle);
        if ((!((this->context_lo)->data_types)->__contains__(dtype_id))) {
            (this->context_lo)->data_types->__setitem__(dtype_id, (new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType(data_type_name, handle)));
        }
        else {
            (((this->context_lo)->data_types)->__getitem__(dtype_id))->updateHandle(handle);
        }
    }
    else {
        logDebug(__modct(const_10, 3, path, data_type_name, ___box(dtype_id)));
    }
    return NULL;
}

void *shedskin_PluginLoader(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
    PluginLoader *soll;

    soll = (new PluginLoader(context_lo));
    soll->loadDataTypeLibrary(const_11, const_12, 1);
    soll->unloadDataTypeLibrary(const_11, 1);
    soll->loadProcessorLibrary(const_11, (new dict<str *, __ss_int>(1, (new tuple2<str *, __ss_int >(2,const_13,1)))));
    soll->unloadProcessorLibrary(const_11, (new list<__ss_int>(1,1)));
    soll->processorIsLoaded(const_11);
    soll->dataTypeIsLoaded(const_11);
    return NULL;
}

void *shedskin_test() {
    
    return NULL;
}

void __init() {
    const_0 = new str("Loading processor library at %r with func_dict=%r ");
    const_1 = new str("local");
    const_2 = new str("");
    const_3 = new str("Processor library already loaded. (at %r with func_dict=%r)");
    const_4 = new str("Unloading data type library at %r with dtype_id=%r");
    const_5 = new str("Data type library already unloaded.(at %r with dtype_id=%r)");
    const_6 = new str("Unloading processor library at %r with func_ids=%r");
    const_7 = new str("Processor library already unloaded. (at %r with func_ids=%r)");
    const_8 = new str("Loading data type library at %r with data_type_name=%r and dtype_id=%r");
    const_9 = new str("global");
    const_10 = new str("Loading data type library already loaded. At %r with data_type_name=%r and dtype_id=%r");
    const_11 = new str("/path/to.so");
    const_12 = new str("Data Type Name");
    const_13 = new str("Func Name");
    const_14 = new str("__main__");

    __name__ = new str("PluginLoader");

    cl_PluginLoader = new class_("PluginLoader");
    if (__eq(__name__, const_14)) {
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
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/load_unload_library/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/load_unload_library/load_unload_library.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/lo/plugin_loader/PluginLoader.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/__init__.hpp"
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
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/load_unload_library/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/load_unload_library/load_unload_library.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "sys.hpp"
#include "mepinta/pipeline/lo/plugin_loader/PluginLoader.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_plugin_loader_PluginLoader;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __plugin_loader__ { /* XXX */
namespace __PluginLoader__ { /* XXX */

/* class PluginLoader */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__plugin_loader__::__PluginLoader__::PluginLoader *__ss_object;
} __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject;

static PyMemberDef __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_processorIsLoaded(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("path", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *)self)->__ss_object->processorIsLoaded(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_loadProcessorLibrary(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("path", 0, 0, 0, args, kwargs);
        dict<str *, __ss_int> *arg_1 = __ss_arg<dict<str *, __ss_int> *>("func_dict", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *)self)->__ss_object->loadProcessorLibrary(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_unloadDataTypeLibrary(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("path", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("dtype_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *)self)->__ss_object->unloadDataTypeLibrary(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *)self)->__ss_object->__init__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_unloadProcessorLibrary(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("path", 0, 0, 0, args, kwargs);
        list<__ss_int> *arg_1 = __ss_arg<list<__ss_int> *>("func_ids", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *)self)->__ss_object->unloadProcessorLibrary(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_dataTypeIsLoaded(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("path", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *)self)->__ss_object->dataTypeIsLoaded(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_loadDataTypeLibrary(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("path", 0, 0, 0, args, kwargs);
        str *arg_1 = __ss_arg<str *>("data_type_name", 1, 0, 0, args, kwargs);
        __ss_int arg_2 = __ss_arg<__ss_int >("dtype_id", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *)self)->__ss_object->loadDataTypeLibrary(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"processorIsLoaded", (PyCFunction)__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_processorIsLoaded, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"loadProcessorLibrary", (PyCFunction)__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_loadProcessorLibrary, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"unloadDataTypeLibrary", (PyCFunction)__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_unloadDataTypeLibrary, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"unloadProcessorLibrary", (PyCFunction)__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_unloadProcessorLibrary, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"dataTypeIsLoaded", (PyCFunction)__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_dataTypeIsLoaded, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"loadDataTypeLibrary", (PyCFunction)__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_loadDataTypeLibrary, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *self = (__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__plugin_loader__::__PluginLoader__::PluginLoader();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__plugin_loader__::__PluginLoader__::cl_PluginLoader;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderDealloc(__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_context_lo(__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *self, void *closure) {
    return __to_py(self->__ss_object->context_lo);
}

int __ss_set___ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_context_lo(__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderGetSet[] = {
    {(char *)"context_lo", (getter)__ss_get___ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_context_lo, (setter)__ss_set___ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_context_lo, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "PluginLoader.PluginLoader",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_plugin_loader_PluginLoader, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(1);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *)self)->__ss_object->context_lo));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoader__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *)self)->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(PyTuple_GetItem(state, 0));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __plugin_loader__
} // namespace __PluginLoader__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __plugin_loader__ { /* XXX */
namespace __PluginLoader__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_plugin_loader_PluginLoader_shedskin_test(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(__PluginLoader__::shedskin_test());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *Global_mepinta_pipeline_lo_plugin_loader_PluginLoader_shedskin_PluginLoader(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);

        return __to_py(__PluginLoader__::shedskin_PluginLoader(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_plugin_loader_PluginLoader_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_plugin_loader_PluginLoaderMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_test", (PyCFunction)Global_mepinta_pipeline_lo_plugin_loader_PluginLoader_shedskin_test, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_PluginLoader", (PyCFunction)Global_mepinta_pipeline_lo_plugin_loader_PluginLoader_shedskin_PluginLoader, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_plugin_loader_PluginLoader(void) {

    __ss_mod_mepinta_pipeline_lo_plugin_loader_PluginLoader = Py_InitModule((char *)"PluginLoader", Global_mepinta_pipeline_lo_plugin_loader_PluginLoaderMethods);
    if(!__ss_mod_mepinta_pipeline_lo_plugin_loader_PluginLoader)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_plugin_loader_PluginLoader, "PluginLoader", (PyObject *)&__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_plugin_loader_PluginLoader(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __plugin_loader__

} // namespace __PluginLoader__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __plugin_loader__ { /* XXX */
namespace __PluginLoader__ { /* XXX */

PyObject *PluginLoader::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *self = (__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *)(__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__plugin_loader__::__PluginLoader__::PluginLoader *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__plugin_loader__::__PluginLoader__::__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (PluginLoader expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__plugin_loader__::__PluginLoader__::__ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObject *)p)->__ss_object;
}
}
