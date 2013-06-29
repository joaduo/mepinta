#include "builtin.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "copy.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
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
namespace __pipeline_evaluator__ {
namespace __PipelineEvaluatorFunctum__ {

str *const_0, *const_1, *const_10, *const_11, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;

using __mepinta__::__pipeline__::__lo__::__constants__::hasFlags;
using __pipeline_backend__::__logging__::__logging__::logDebug;
using __pipeline_backend__::__logging__::__logging__::logWarning;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::voidp_to_FunctumPropertyValue;
using __pipeline_backend__::__void_pointer_casting__::__void_pointer_casting__::voidp_to_FunctionPropertyValue;
using __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager;
using __pipeline_backend__::__args_management__::__args_management__::getFunctumStructVoidp;
using __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase;
using __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer;

str *__name__;
__ss_int CUSTOM_INPUT_PROPS, CUSTOM_OUTPUT_PROPS, CUSTOM_PROPERTY_FLAG, FUNCTION_PROPERTY_FLAG, FUNCTUM_PROPERTY_FLAG, INPUT_PROPS, OUTPUT_PROPS, PROCESSOR_EXIT_NORMAL;



/**
class PipelineEvaluatorFunctum
*/

class_ *cl_PipelineEvaluatorFunctum;

tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *PipelineEvaluatorFunctum::__evalFunctumOrDependency(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    list<__ss_int> *dencies;
    __ss_int dency_id;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *dency_prop;

    dencies = (((pline->getTopology(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::default_4))->connections)->dpdencies)->__getitem__(prop_id);
    if ((len(dencies)==1)) {
        dency_id = dencies->__getfast__(0);
        dency_prop = (pline->all_properties)->__getitem__(dency_id);
        if (hasFlags(dency_prop->type, FUNCTUM_PROPERTY_FLAG)) {
            return this->__evalFunctumOrDependency(pline, dency_id, dency_prop);
        }
    }
    return this->__evalFunctum(pline, prop_id, prop);
}

void *PipelineEvaluatorFunctum::__outputValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int out_id, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *args_mngr) {
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *out_prop;

    out_prop = (pline->all_properties)->__getitem__(out_id);
    if (hasFlags(out_prop->type, CUSTOM_PROPERTY_FLAG)) {
        args_mngr->setInOut(CUSTOM_OUTPUT_PROPS);
    }
    else {
        args_mngr->setInOut(OUTPUT_PROPS);
    }
    if ((pline->changed_track)->__contains__(out_id)) {
        (pline->changed_track)->remove(out_id);
    }
    if (__NOT(hasFlags(out_prop->type, FUNCTION_PROPERTY_FLAG))) {
        (this->p_value_mngr)->initPropValue(out_prop);
        args_mngr->append(out_id, out_prop, out_prop);
        args_mngr->unchangedValue();
        args_mngr->nextProp();
    }
    return NULL;
}

tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *PipelineEvaluatorFunctum::evaluateProp(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id) {
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop;

    prop = (pline->all_properties)->__getitem__(prop_id);
    return this->__evalProperty(pline, prop_id, prop);
}

set<__ss_int> *PipelineEvaluatorFunctum::__evalFunction(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    __iter<__ss_int> *__231, *__235;
    __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *args_mngr;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *func_prop_value;
    list<__ss_int> *__230, *__234, *inputs_ids, *outputs_ids;
    list<__ss_int>::for_in_loop __233, __237;
    __ss_int __232, __236, dent_id, input_id;

    logDebug(__modct(const_0, 1, ___box(prop_id)));
    if (__NOT((pline->changed_track)->__contains__(prop_id))) {
        return NULL;
    }
    (pline->changed_track)->remove(prop_id);
    func_prop_value = voidp_to_FunctionPropertyValue(prop->getValue());
    inputs_ids = (((pline->getTopology(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::default_4))->connections)->dpdencies)->__getitem__(prop_id);
    outputs_ids = (((pline->getTopology(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::default_4))->connections)->dpdents)->__getitem__(prop_id);
    args_mngr = (new __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager(this->context_lo, func_prop_value, 0));

    FOR_IN(input_id,inputs_ids,230,232,233)
        this->__inputValue(pline, input_id, args_mngr);
    END_FOR


    FOR_IN(dent_id,outputs_ids,234,236,237)
        this->__outputValue(pline, dent_id, args_mngr);
    END_FOR

    return this->__callProcessor(pline, prop_id, prop, func_prop_value, args_mngr);
}

set<__ss_int> *PipelineEvaluatorFunctum::__callProcessor(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *func_prop_value, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *args_mngr) {
    void *func_ptr;
    __ss_int exit_status;

    func_ptr = (((this->context_lo)->functions)->__getitem__(func_prop_value->func_id))->getFuncPointer();
    logDebug(__modct(const_1, 1, prop->name));
    exit_status = (this->func_caller)->callProcessorFunc(func_ptr, args_mngr->getArgs());
    logDebug(__modct(const_2, 1, prop->name));
    if ((exit_status!=PROCESSOR_EXIT_NORMAL)) {
        logDebug(__modct(const_3, 2, prop->name, ___box(exit_status)));
    }
    if ((pline->marked_outputs)->__contains__(prop_id)) {
        return args_mngr->buildChangedSet();
    }
    return NULL;
}

tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *PipelineEvaluatorFunctum::__evaleDataProperty(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    __iter<__ss_int> *__249;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *dency_prop;
    __ss_bool changed;
    list<__ss_int> *__248, *dencies;
    list<__ss_int>::for_in_loop __251;
    __ss_int __250, dency_id;

    dencies = (((pline->getTopology(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::default_4))->connections)->dpdencies)->__getitem__(prop_id);
    logDebug(__modct(const_4, 1, ___box(prop_id)));
    changed = False;
    if ((pline->changed_track)->__contains__(prop_id)) {
        changed = True;
        logDebug(__modct(const_5, 1, ___box(prop_id)));
        (pline->changed_track)->remove(prop_id);
        if ((pline->cached_link)->__contains__(prop_id)) {
            this->__solveNonCached(pline, prop_id, prop);
        }
    }

    FOR_IN(dency_id,dencies,248,250,251)
        dency_prop = (pline->all_properties)->__getitem__(dency_id);
        if (hasFlags(dency_prop->type, FUNCTION_PROPERTY_FLAG)) {
            if (changed) {
                this->__evalFunction(pline, dency_id, dency_prop);
            }
        }
        else {
            if ((len(dencies)==1)) {
                return this->__evalProperty(pline, dency_id, dency_prop);
            }
            else {
                logWarning(__modct(const_6, 1, ___box(prop_id)));
            }
        }
    END_FOR

    if (changed) {
        (this->p_value_mngr)->initPropValue(prop);
    }
    return (new tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>(2,prop_id,prop));
}

void *PipelineEvaluatorFunctum::__solveNonCached(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int out_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *out_prop) {
    __ss_int input_id;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *input_prop;
    tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *__239;

    input_id = (pline->cached_link)->getFirst(out_id);
    input_prop = (pline->all_properties)->__getitem__(input_id);
    __239 = this->__evalProperty(pline, input_id, input_prop);
    input_id = __239->__getfirst__();
    input_prop = __239->__getsecond__();
    if (((pline->getTopology(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::default_4))->cached)->__contains__(out_id)) {
        logDebug(__modct(const_7, 2, out_prop->name, ___box(out_id)));
        (this->p_value_mngr)->copyPropValue(out_prop, input_prop->getValuePtr());
    }
    else {
        this->__stealInput(pline, out_id, out_prop, input_id, input_prop);
    }
    return NULL;
}

tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *PipelineEvaluatorFunctum::__evalProperty(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    
    if (hasFlags(prop->type, FUNCTION_PROPERTY_FLAG)) {
        this->__evalFunction(pline, prop_id, prop);
        return (new tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>(2,prop_id,prop));
    }
    else {
        if (hasFlags(prop->type, FUNCTUM_PROPERTY_FLAG)) {
            return this->__evalFunctumOrDependency(pline, prop_id, prop);
        }
        else {
            return this->__evaleDataProperty(pline, prop_id, prop);
        }
    }
    return 0;
}

__ss_int PipelineEvaluatorFunctum::__inputValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int input_id, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *args_mngr) {
    __ss_int _;
    __ss_bool changed;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *dency_prop, *input_prop;
    tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *__238;

    input_prop = (pline->all_properties)->__getitem__(input_id);
    if (hasFlags(input_prop->type, CUSTOM_PROPERTY_FLAG)) {
        args_mngr->setInOut(CUSTOM_INPUT_PROPS);
    }
    else {
        args_mngr->setInOut(INPUT_PROPS);
    }
    if (hasFlags(input_prop->type, FUNCTION_PROPERTY_FLAG)) {
        this->__evalFunction(pline, input_id, input_prop);
        return input_id;
    }
    else {
        changed = ___bool((pline->changed_track)->__contains__(input_id));
        __238 = this->__evalProperty(pline, input_id, input_prop);
        _ = __238->__getfirst__();
        dency_prop = __238->__getsecond__();
        args_mngr->append(input_id, input_prop, dency_prop);
        if (changed) {
            args_mngr->changedValue();
        }
        else {
            args_mngr->unchangedValue();
        }
        args_mngr->nextProp();
        return input_id;
    }
    return 0;
}

void *PipelineEvaluatorFunctum::__stealInput(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int out_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *out_prop, __ss_int input_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *input_prop) {
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *vpointer_none;

    logDebug(const_8);
    logDebug(__modct(const_9, 4, out_prop->name, ___box(out_id), input_prop->name, ___box(input_id)));
    (this->p_value_mngr)->setPropValuePointer(out_prop, input_prop->getValuePtr());
    logDebug(__modct(const_10, 2, input_prop->name, ___box(input_id)));
    vpointer_none = (new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer(NULL));
    (this->p_value_mngr)->setPropValuePointer(input_prop, vpointer_none);
    ((pline->getTopology(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::default_4))->changed_primary)->add(input_id);
    return NULL;
}

tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *PipelineEvaluatorFunctum::__evalFunctum(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop) {
    /**
    Evaluates all the dependencies of a functum, and packs function and
    dependencies together for later evaluation.
    :param pline: Pipeline
    :param prop_id: Property id of the prop parameter
    :param prop: Pipeline's Property
    */
    __iter<__ss_int> *__241, *__245;
    __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *args_mngr;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *functum_prop;
    list<__ss_int> *__240, *__244, *inputs_ids, *outputs_ids;
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue *functum_prop_value;
    void *func_ptr, *functum_struct;
    list<__ss_int>::for_in_loop __243, __247;
    __ss_int __242, __246, dent_id, input_id;

    logDebug(__modct(const_11, 1, ___box(prop_id)));
    functum_prop_value = voidp_to_FunctumPropertyValue(prop->getValue());
    inputs_ids = (((pline->getTopology(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::default_4))->connections)->dpdencies)->__getitem__(prop_id);
    outputs_ids = (((pline->getTopology(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::default_4))->connections)->dpdents)->__getitem__(prop_id);
    args_mngr = (new __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager(this->context_lo, ((__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *)(functum_prop_value)), 0));
    if ((pline->changed_track)->__contains__(prop_id)) {
        (pline->changed_track)->remove(prop_id);
    }

    FOR_IN(input_id,inputs_ids,240,242,243)
        this->__inputValue(pline, input_id, args_mngr);
    END_FOR


    FOR_IN(dent_id,outputs_ids,244,246,247)
        this->__outputValue(pline, dent_id, args_mngr);
    END_FOR

    functum_prop = functum_prop_value->getFunctumProp();
    if ((functum_prop->getValue()==NULL)) {
        func_ptr = (((this->context_lo)->functions)->__getitem__(functum_prop_value->func_id))->getFuncPointer();
        functum_struct = getFunctumStructVoidp(func_ptr, args_mngr->getArgs());
        (this->p_value_mngr)->replacePropValue(functum_prop, functum_struct);
    }
    return (new tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>(2,prop_id,functum_prop));
}

void *shedskin_PipelineEvaluatorFunctum(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *args_mngr) {
    __ss_int prop_id;
    dict<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *__252;
    PipelineEvaluatorFunctum *pe;

    pe = (new PipelineEvaluatorFunctum(context_lo));
    prop_id = 100;
    pline->all_properties->__setitem__(prop_id, prop);
    pe->evaluateProp(pline, prop_id);
    return NULL;
}

void __init() {
    const_0 = new str("Evaluating function with prop_id=%r");
    const_1 = new str("Entering processor function '%s'.");
    const_2 = new str("Leaving processor function '%s'.");
    const_3 = new str("Processor function '%s' with unnormal exit status: %r.");
    const_4 = new str("Evaluating property with prop_id=%r");
    const_5 = new str("Removing changed Property with prop_id=%r");
    const_6 = new str("A common (in/out/internal) property shouldn't be connected to functions and other properties.For prop_id: %r ");
    const_7 = new str("Copying value for property:%r id=%r");
    const_8 = new str("Non cached properties should be used in a restricted context.");
    const_9 = new str("Stealing value for property:%r id=%r from property:%r id=%r");
    const_10 = new str("Detaching from previous property:%r id=%r");
    const_11 = new str("Evaluating functum with prop_id=%r");

    __name__ = new str("PipelineEvaluatorFunctum");

    FUNCTION_PROPERTY_FLAG = __mepinta__::__pipeline__::__lo__::__constants__::FUNCTION_PROPERTY_FLAG;
    INPUT_PROPS = __mepinta__::__pipeline__::__lo__::__constants__::INPUT_PROPS;
    OUTPUT_PROPS = __mepinta__::__pipeline__::__lo__::__constants__::OUTPUT_PROPS;
    FUNCTUM_PROPERTY_FLAG = __mepinta__::__pipeline__::__lo__::__constants__::FUNCTUM_PROPERTY_FLAG;
    PROCESSOR_EXIT_NORMAL = __mepinta__::__pipeline__::__lo__::__constants__::PROCESSOR_EXIT_NORMAL;
    CUSTOM_INPUT_PROPS = __mepinta__::__pipeline__::__lo__::__constants__::CUSTOM_INPUT_PROPS;
    CUSTOM_PROPERTY_FLAG = __mepinta__::__pipeline__::__lo__::__constants__::CUSTOM_PROPERTY_FLAG;
    CUSTOM_OUTPUT_PROPS = __mepinta__::__pipeline__::__lo__::__constants__::CUSTOM_OUTPUT_PROPS;
    cl_PipelineEvaluatorFunctum = new class_("PipelineEvaluatorFunctum");
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
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include <structmember.h>
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "copy.hpp"
#include "pipeline_backend/args_management/__init__.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/PipelineEvaluatorFunctum.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __PipelineEvaluatorFunctum__ { /* XXX */

/* class PipelineEvaluatorFunctum */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__PipelineEvaluatorFunctum__::PipelineEvaluatorFunctum *__ss_object;
} __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject;

static PyMemberDef __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___evalFunctumOrDependency(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("prop_id", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->__evalFunctumOrDependency(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___outputValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("out_id", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *>("args_mngr", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->__outputValue(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_evaluateProp(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("prop_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->evaluateProp(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___evalFunction(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("prop_id", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->__evalFunction(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___callProcessor(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("prop_id", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 2, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *arg_3 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *>("func_prop_value", 3, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *arg_4 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *>("args_mngr", 4, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->__callProcessor(arg_0, arg_1, arg_2, arg_3, arg_4));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___evaleDataProperty(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("prop_id", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->__evaleDataProperty(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___solveNonCached(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("out_id", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("out_prop", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->__solveNonCached(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___evalProperty(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("prop_id", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->__evalProperty(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___inputValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("input_id", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *>("args_mngr", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->__inputValue(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___stealInput(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("out_id", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("out_prop", 2, 0, 0, args, kwargs);
        __ss_int arg_3 = __ss_arg<__ss_int >("input_id", 3, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_4 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("input_prop", 4, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->__stealInput(arg_0, arg_1, arg_2, arg_3, arg_4));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___evalFunctum(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("prop_id", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->__evalFunctum(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_as_number = {
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

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__evalFunctumOrDependency", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___evalFunctumOrDependency, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__outputValue", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___outputValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"evaluateProp", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_evaluateProp, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__evalFunction", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___evalFunction, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__callProcessor", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___callProcessor, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__evaleDataProperty", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___evaleDataProperty, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__solveNonCached", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___solveNonCached, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__evalProperty", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___evalProperty, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__inputValue", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___inputValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__stealInput", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___stealInput, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__evalFunctum", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum___evalFunctum, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *self = (__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__PipelineEvaluatorFunctum__::PipelineEvaluatorFunctum();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__PipelineEvaluatorFunctum__::cl_PipelineEvaluatorFunctum;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumDealloc(__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_func_caller(__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *self, void *closure) {
    return __to_py(self->__ss_object->func_caller);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_func_caller(__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->func_caller = __to_ss<__mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_p_value_mngr(__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *self, void *closure) {
    return __to_py(self->__ss_object->p_value_mngr);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_p_value_mngr(__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->p_value_mngr = __to_ss<__mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_context_lo(__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *self, void *closure) {
    return __to_py(self->__ss_object->context_lo);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_context_lo(__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumGetSet[] = {
    {(char *)"func_caller", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_func_caller, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_func_caller, (char *)"", NULL},
    {(char *)"p_value_mngr", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_p_value_mngr, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_p_value_mngr, (char *)"", NULL},
    {(char *)"context_lo", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_context_lo, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_context_lo, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "PipelineEvaluatorFunctum.PipelineEvaluatorFunctum",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum_as_number,  /* tp_as_number      */
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
    __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumGetSet,       /* tp_getset         */
    &__ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObjectType,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    0,              /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(3);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->func_caller));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->p_value_mngr));
    PyTuple_SetItem(b, 2, __to_py(((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->context_lo));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctum__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->func_caller = __to_ss<__mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->p_value_mngr = __to_ss<__mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *>(PyTuple_GetItem(state, 1));
    ((__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)self)->__ss_object->context_lo = __to_ss<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>(PyTuple_GetItem(state, 2));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __pipeline_evaluator__
} // namespace __PipelineEvaluatorFunctum__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __PipelineEvaluatorFunctum__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_shedskin_PipelineEvaluatorFunctum(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *arg_0 = __ss_arg<__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *>("context_lo", 0, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *arg_1 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *>("pline", 1, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *arg_2 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *>("prop", 2, 0, 0, args, kwargs);
        __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *arg_3 = __ss_arg<__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *>("args_mngr", 3, 0, 0, args, kwargs);

        return __to_py(__PipelineEvaluatorFunctum__::shedskin_PipelineEvaluatorFunctum(arg_0, arg_1, arg_2, arg_3));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctumMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_PipelineEvaluatorFunctum", (PyCFunction)Global_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_shedskin_PipelineEvaluatorFunctum, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum(void) {

    __ss_mod_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum = Py_InitModule((char *)"PipelineEvaluatorFunctum", Global_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctumMethods);
    if(!__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum, "PipelineEvaluatorFunctum", (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum(void) {
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum, (char *)"CUSTOM_OUTPUT_PROPS", __to_py(__PipelineEvaluatorFunctum__::CUSTOM_OUTPUT_PROPS));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum, (char *)"INPUT_PROPS", __to_py(__PipelineEvaluatorFunctum__::INPUT_PROPS));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum, (char *)"CUSTOM_PROPERTY_FLAG", __to_py(__PipelineEvaluatorFunctum__::CUSTOM_PROPERTY_FLAG));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum, (char *)"FUNCTUM_PROPERTY_FLAG", __to_py(__PipelineEvaluatorFunctum__::FUNCTUM_PROPERTY_FLAG));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum, (char *)"PROCESSOR_EXIT_NORMAL", __to_py(__PipelineEvaluatorFunctum__::PROCESSOR_EXIT_NORMAL));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum, (char *)"CUSTOM_INPUT_PROPS", __to_py(__PipelineEvaluatorFunctum__::CUSTOM_INPUT_PROPS));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum, (char *)"OUTPUT_PROPS", __to_py(__PipelineEvaluatorFunctum__::OUTPUT_PROPS));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum, (char *)"FUNCTION_PROPERTY_FLAG", __to_py(__PipelineEvaluatorFunctum__::FUNCTION_PROPERTY_FLAG));

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __pipeline_evaluator__

} // namespace __PipelineEvaluatorFunctum__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __PipelineEvaluatorFunctum__ { /* XXX */

PyObject *PipelineEvaluatorFunctum::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *self = (__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)(__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObjectType, 0));
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

template<> __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__PipelineEvaluatorFunctum__::PipelineEvaluatorFunctum *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__PipelineEvaluatorFunctum__::__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (PipelineEvaluatorFunctum expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__PipelineEvaluatorFunctum__::__ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObject *)p)->__ss_object;
}
}
