#ifndef __MEPINTA_PIPELINE_LO_REENTRANT_DATA_MODEL_HPP
#define __MEPINTA_PIPELINE_LO_REENTRANT_DATA_MODEL_HPP

using namespace __shedskin__;

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
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __reentrant__ {
namespace __data_model__ {

class ProcessorContext;


extern str *__name__;


extern class_ *cl_ProcessorContext;
class ProcessorContext : public pyobj {
public:
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline;
    __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *pline_evaluator;
    __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo;

    ProcessorContext() {}
    ProcessorContext(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *pline_evaluator) {
        this->__class__ = cl_ProcessorContext;
        __init__(context_lo, pline, pline_evaluator);
    }
    void *__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *pline_evaluator);
    virtual PyObject *__to_py__();
};

void __init();
ProcessorContext *shedskin_reentrant_data_model(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *pline_evaluator);

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_reentrant_data_model(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_reentrant_data_model(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_reentrant_data_model_ProcessorContextObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__reentrant__::__data_model__::ProcessorContext *__to_ss(PyObject *p);
}
#endif
