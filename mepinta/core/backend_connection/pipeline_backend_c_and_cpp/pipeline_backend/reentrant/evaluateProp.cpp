#include "builtin.hpp"
#include "sys.hpp"
#include "copy.hpp"

#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"

#include "mepinta/pipeline/lo/reentrant/data_model.hpp"
#include "mepinta/pipeline/lo/reentrant/reentrant.hpp"
#include "pipeline_backend/reentrant/evaluateProp.hpp"

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

namespace __pipeline_backend__ {
namespace __reentrant__ {
namespace __evaluateProp__ {

using __mepinta__::__pipeline__::__lo__::__reentrant__::__reentrant__::evaluateProp;

str *__name__;


typedef __mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcesssorContext ProcesssorContext;

void* MP_evaluateProp(void*processor_context , __ss_int prop_id, int* dency_id) {
    tuple2<__ss_int, void *> *__246;
    void *value;
    __ss_int dency_id_return;

    __246 = evaluateProp((ProcesssorContext*)processor_context, prop_id);
    if(dency_id != NULL)
      *dency_id = __246->__getfirst__();
    value = __246->__getsecond__();
    return value;
}

void *shedskin_backend_reentrant_evaluateProp(__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcesssorContext *processor_context) {
    
//    evaluateProp(processor_context, 1, NULL);
    return NULL;
}

void __init() {
    __name__ = new str("evaluateProp");

}

} // module namespace
} // module namespace
} // module namespace

