#ifndef __MEPINTA_PIPELINE_LO_PIPELINE_EVALUATOR_BASE_HPP
#define __MEPINTA_PIPELINE_LO_PIPELINE_EVALUATOR_BASE_HPP

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
namespace __FunctionCaller__ { /* XXX */
class FunctionCaller;
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
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __PipelineEvaluatorFunctum__ { /* XXX */
class PipelineEvaluatorFunctum;
}
}
}
}
}
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __value_manager__ { /* XXX */
namespace __PropertyValueManager__ { /* XXX */
class PropertyValueManager;
}
}
}
}
}
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __pipeline_evaluator__ {
namespace __base__ {

extern str *const_0;

class PipelineEvaluatorBase;


extern str *__name__;


extern class_ *cl_PipelineEvaluatorBase;
class PipelineEvaluatorBase : public pyobj {
public:
    __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *func_caller;
    __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *p_value_mngr;
    __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo;

    PipelineEvaluatorBase() {}
    PipelineEvaluatorBase(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
        this->__class__ = cl_PipelineEvaluatorBase;
        __init__(context_lo);
    }
    tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *evaluateProp(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id);
    void *__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo);
    virtual PyObject *__to_py__();
};

void __init();
PipelineEvaluatorBase *shedskin_PipelineEvaluatorBase(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_evaluator_base(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_evaluator_base(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_pipeline_evaluator_base_PipelineEvaluatorBaseObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *__to_ss(PyObject *p);
}
#endif
