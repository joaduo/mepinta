#ifndef __MEPINTA_PIPELINE_LO_PIPELINE_EVALUATOR_PIPELINEEVALUATORFUNCTUM_HPP
#define __MEPINTA_PIPELINE_LO_PIPELINE_EVALUATOR_PIPELINEEVALUATORFUNCTUM_HPP

using namespace __shedskin__;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __TopologyConnections__ { /* XXX */
class TopologyConnections;
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
namespace __generic_data__ { /* XXX */
namespace __DirectedGraph__ { /* XXX */
class DirectedGraph;
class DirectedGraphIterator;
}
}
}
}
}
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __ProcessorArgsManager__ { /* XXX */
class ProcessorArgsManager;
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
namespace __hidden_data_types__ { /* XXX */
class FunctumPropertyValue;
class FunctionPropertyValue;
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
namespace __PipelineEvaluatorFunctum__ {

extern str *const_0, *const_1, *const_10, *const_11, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;

class PipelineEvaluatorFunctum;


extern __ss_int CUSTOM_INPUT_PROPS, CUSTOM_OUTPUT_PROPS, CUSTOM_PROPERTY_FLAG, FUNCTION_PROPERTY_FLAG, FUNCTUM_PROPERTY_FLAG, INPUT_PROPS, OUTPUT_PROPS, PROCESSOR_EXIT_NORMAL;
extern str *__name__;


extern class_ *cl_PipelineEvaluatorFunctum;
class PipelineEvaluatorFunctum : public __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase {
/**
Evaluates a Pipeline (from lo package) given a property.
This means it visits all dependencies in the graph recursively until evaluated
 the desired property.
It stops evaluating a recursion branch when there are no more changed
  dependencies or it founds a cyclic connection.
If the Property is not marked as changed, it won't be evaluated. (also its
  dependencies)
*/
public:

    PipelineEvaluatorFunctum() {}
    PipelineEvaluatorFunctum(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
        this->__class__ = cl_PipelineEvaluatorFunctum;
        __init__(context_lo);
    }
    tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *__evalFunctumOrDependency(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);
    void *__outputValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int out_id, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *args_mngr);
    tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *evaluateProp(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id);
    set<__ss_int> *__evalFunction(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);
    set<__ss_int> *__callProcessor(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *func_prop_value, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *args_mngr);
    tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *__evaleDataProperty(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);
    void *__solveNonCached(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int out_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *out_prop);
    tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *__evalProperty(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);
    __ss_int __inputValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int input_id, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *args_mngr);
    void *__stealInput(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int out_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *out_prop, __ss_int input_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *input_prop);
    tuple2<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *__evalFunctum(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);
    virtual PyObject *__to_py__();
};

void __init();
void *shedskin_PipelineEvaluatorFunctum(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *args_mngr);

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_pipeline_evaluator_PipelineEvaluatorFunctum_PipelineEvaluatorFunctumObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__PipelineEvaluatorFunctum__::PipelineEvaluatorFunctum *__to_ss(PyObject *p);
}
#endif
