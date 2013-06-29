#ifndef __MEPINTA_PIPELINE_LO_PIPELINE_EVALUATOR_PROCESSORARGSMANAGER_HPP
#define __MEPINTA_PIPELINE_LO_PIPELINE_EVALUATOR_PROCESSORARGSMANAGER_HPP

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
namespace __pipeline_data__ { /* XXX */
namespace __hidden_data_types__ { /* XXX */
class FunctumPropertyValue;
class FunctionPropertyValue;
}
}
}
}
}
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __pipeline_evaluator__ {
namespace __ProcessorArgsManager__ {

class ProcessorArgsManager;


extern __ss_int CUSTOM_INPUT_PROPS, CUSTOM_OUTPUT_PROPS, INPUT_PROPS, OUTPUT_PROPS;
extern str *__name__;


extern class_ *cl_ProcessorArgsManager;
class ProcessorArgsManager : public pyobj {
public:
    void *args;
    __ss_bool marked;
    __ss_int in_out_id;
    __ss_bool new_args;
    dict<__ss_int, __ss_int> *indexes;
    __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo;

    ProcessorArgsManager() {}
    ProcessorArgsManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *func_prop_value, __ss_int thread_id) {
        this->__class__ = cl_ProcessorArgsManager;
        __init__(context_lo, func_prop_value, thread_id);
    }
    void *unchangedValue();
    void *changedValue();
    void *createArgs(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *func_prop_value, __ss_int thread_id);
    set<__ss_int> *buildChangedSet();
    void *nextProp();
    __ss_int __getCurrentIndex();
    void *setInOut(__ss_int in_out_id);
    void *append(__ss_int prop_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop_real);
    void *__incrementCurrentIndex(__ss_int delta);
    void *getArgs();
    void *__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *func_prop_value, __ss_int thread_id);
    virtual PyObject *__to_py__();
};

void __init();
ProcessorArgsManager *shedskin_ProcessorArgsManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *func_prop_value, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_pipeline_evaluator_ProcessorArgsManager_ProcessorArgsManagerObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__ProcessorArgsManager__::ProcessorArgsManager *__to_ss(PyObject *p);
}
#endif
