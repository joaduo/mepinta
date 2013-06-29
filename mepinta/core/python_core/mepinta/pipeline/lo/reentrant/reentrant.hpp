#ifndef __MEPINTA_PIPELINE_LO_REENTRANT_REENTRANT_HPP
#define __MEPINTA_PIPELINE_LO_REENTRANT_REENTRANT_HPP

using namespace __shedskin__;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */
class PropertyValuePointer;
class Pipeline;
class DataType;
class ProcessorFunction;
class Property;
class Topology;
}
}
}
}
}
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __reentrant__ { /* XXX */
namespace __data_model__ { /* XXX */
class ProcessorContext;
}
}
}
}
}
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __base__ { /* XXX */
class PipelineEvaluatorBase;
}
}
}
}
}
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __context_lo__ { /* XXX */
namespace __ContextLo__ { /* XXX */
class ContextLo;
}
}
}
}
}
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __reentrant__ {
namespace __reentrant__ {

extern str *const_0, *const_1, *const_2, *const_3;



extern str *__name__;


void __init();
__ss_bool isDataTypeAlias(__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *processor_context, str *data_type_name, str *data_type_alias);
tuple2<__ss_int, void *> *evaluateProp(__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *processor_context, __ss_int prop_id);
void *shedskin_reentrant(__mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *processor_context);

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_reentrant_reentrant(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_reentrant_reentrant(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
namespace __shedskin__ { /* XXX */

}
#endif
