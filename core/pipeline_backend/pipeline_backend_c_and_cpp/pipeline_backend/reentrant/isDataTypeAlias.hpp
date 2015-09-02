#ifndef __PIPELINE_BACKEND_REENTRANT_ISDATATYPEALIAS_HPP
#define __PIPELINE_BACKEND_REENTRANT_ISDATATYPEALIAS_HPP

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
namespace __isDataTypeAlias__ {

extern str *const_0, *const_1;



extern str *__name__;


void __init();
extern "C" EXPORTED_SYMBOL int MP_isDataTypeAlias(void* processor_context, char *data_type_name, char *data_type_alias);
void *shedskin_backend_reentrant_isDataTypeAlias(__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcesssorContext *processor_context);

} // module namespace
} // module namespace
} // module namespace
#endif
