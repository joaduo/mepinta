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
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include "mepinta/pipeline/lo/reentrant/reentrant.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/reentrant/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/context_lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"

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
namespace __reentrant__ {
namespace __reentrant__ {

str *const_0, *const_1, *const_2, *const_3;

using __pipeline_backend__::__logging__::__logging__::logDebug;
using __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo;
using __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase;

str *__name__;



__ss_bool isDataTypeAlias(__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *processor_context, str *data_type_name, str *data_type_alias) {
    
    logDebug(__modct(const_0, 2, data_type_alias, data_type_name));
    return ___bool((((processor_context->context_lo)->data_type_aliases)->__getitem__(data_type_name))->__contains__(data_type_alias));
}

tuple2<__ss_int, void *> *evaluateProp(__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *processor_context, __ss_int prop_id) {
    __ss_int dency_id;
    tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *__253;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *dency_prop;

    logDebug(__modct(const_1, 1, ___box(prop_id)));
    __253 = (processor_context->pline_evaluator)->evaluateProp(processor_context->pline, prop_id);
    dency_id = __253->__getfirst__();
    dency_prop = __253->__getsecond__();
    return (new tuple2<__ss_int, void *>(2,dency_id,(dency_prop->getValuePtr())->getValue()));
}

void *shedskin_reentrant(__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *processor_context) {
    
    isDataTypeAlias(processor_context, const_2, const_3);
    evaluateProp(processor_context, 1);
    return NULL;
}

void __init() {
    const_0 = new str("Checking if data type %s is an alias of %s");
    const_1 = new str("Evaluating prop_id %s in reentrant mode.");
    const_2 = new str("int");
    const_3 = new str("int32_t");

    __name__ = new str("reentrant");

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
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include "mepinta/pipeline/lo/reentrant/reentrant.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/reentrant/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/context_lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
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
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include "mepinta/pipeline/lo/reentrant/reentrant.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/reentrant/data_model.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/context_lo/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_reentrant_reentrant;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __reentrant__ { /* XXX */
namespace __reentrant__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_reentrant_reentrant_isDataTypeAlias(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *>("processor_context", 0, 0, 0, args, kwargs);
        str *arg_1 = __ss_arg<str *>("data_type_name", 1, 0, 0, args, kwargs);
        str *arg_2 = __ss_arg<str *>("data_type_alias", 2, 0, 0, args, kwargs);

        return __to_py(__reentrant__::isDataTypeAlias(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *Global_mepinta_pipeline_lo_reentrant_reentrant_shedskin_reentrant(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *>("processor_context", 0, 0, 0, args, kwargs);

        return __to_py(__reentrant__::shedskin_reentrant(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *Global_mepinta_pipeline_lo_reentrant_reentrant_evaluateProp(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *>("processor_context", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("prop_id", 1, 0, 0, args, kwargs);

        return __to_py(__reentrant__::evaluateProp(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_reentrant_reentrant_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_reentrant_reentrantMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"isDataTypeAlias", (PyCFunction)Global_mepinta_pipeline_lo_reentrant_reentrant_isDataTypeAlias, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_reentrant", (PyCFunction)Global_mepinta_pipeline_lo_reentrant_reentrant_shedskin_reentrant, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"evaluateProp", (PyCFunction)Global_mepinta_pipeline_lo_reentrant_reentrant_evaluateProp, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_reentrant_reentrant(void) {

    __ss_mod_mepinta_pipeline_lo_reentrant_reentrant = Py_InitModule((char *)"reentrant", Global_mepinta_pipeline_lo_reentrant_reentrantMethods);
    if(!__ss_mod_mepinta_pipeline_lo_reentrant_reentrant)
        return;



}

PyMODINIT_FUNC addmepinta_pipeline_lo_reentrant_reentrant(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __reentrant__

} // namespace __reentrant__

} // extern "C"
