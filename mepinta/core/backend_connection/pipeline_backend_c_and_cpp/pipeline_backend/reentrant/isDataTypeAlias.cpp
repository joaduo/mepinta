#include "builtin.hpp"
#include "copy.hpp"
#include "sys.hpp"

#include "pipeline_backend/args_management/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/base.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/reentrant/__init__.hpp"
#include "mepinta/pipeline/lo/context_lo/ContextLo.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/ProcessorArgsManager.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "mepinta/pipeline/lo/value_manager/PropertyValueManager.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "pipeline_backend/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/__init__.hpp"
#include "pipeline_backend/args_management/args_management.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"

#include "mepinta/pipeline/lo/reentrant/data_model.hpp"
#include "mepinta/pipeline/lo/reentrant/reentrant.hpp"
#include "pipeline_backend/reentrant/isDataTypeAlias.hpp"

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
namespace __isDataTypeAlias__ {

str *const_0, *const_1;

using __mepinta__::__pipeline__::__lo__::__reentrant__::__reentrant__::isDataTypeAlias;

str *__name__;


typedef __mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcesssorContext ProcesssorContext;

//int MP_isDataTypeAlias(void* processor_context, str *data_type_name, str *data_type_alias)
int MP_isDataTypeAlias(void* processor_context, char *data_type_name, char *data_type_alias){
  //return isDataTypeAlias((ProcesssorContext*)processor_context, data_type_name, data_type_alias);
  str data_type_name_str(data_type_name);
  str data_type_alias_str(data_type_alias);
  return isDataTypeAlias((ProcesssorContext*)processor_context, &data_type_name_str, &data_type_alias_str);
}

void *shedskin_backend_reentrant_isDataTypeAlias(__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcesssorContext *processor_context) {
    
//    isDataTypeAlias(processor_context, const_0, const_1);
    return NULL;
}

void __init() {
//    const_0 = new str("int");
//    const_1 = new str("int32_t");

    __name__ = new str("isDataTypeAlias");

}

} // module namespace
} // module namespace
} // module namespace

