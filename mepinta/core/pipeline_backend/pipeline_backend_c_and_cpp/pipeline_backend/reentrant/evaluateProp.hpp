#ifndef __PIPELINE_BACKEND_REENTRANT_EVALUATEPROP_HPP
#define __PIPELINE_BACKEND_REENTRANT_EVALUATEPROP_HPP

#include "pipeline_backend_implementation/config.h"

using namespace __shedskin__;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __reentrant__ { /* XXX */
namespace __data_model__ { /* XXX */
class ProcesssorContext;
}
}
}
}
}
namespace __pipeline_backend__ {
namespace __reentrant__ {
namespace __evaluateProp__ {



extern str *__name__;


void __init();
extern "C" EXPORTED_SYMBOL void* MP_evaluateProp(void*processor_context , __ss_int prop_id, int* dency_id);
void *shedskin_backend_reentrant_evaluateProp(__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcesssorContext *processor_context);

} // module namespace
} // module namespace
} // module namespace
#endif
