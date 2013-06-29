#ifndef __MEPINTA_PIPELINE_LO_PIPELINE_DATA_HIDDEN_DATA_TYPES_HPP
#define __MEPINTA_PIPELINE_LO_PIPELINE_DATA_HIDDEN_DATA_TYPES_HPP

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
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __pipeline_data__ {
namespace __hidden_data_types__ {

extern str *const_0;

class FunctionPropertyValue;
class FunctumPropertyValue;


extern str *__name__;


extern class_ *cl_FunctionPropertyValue;
class FunctionPropertyValue : public pyobj {
public:

    void *args;
    __ss_int func_id;

    FunctionPropertyValue() {}
    FunctionPropertyValue(__ss_int func_id) {
        this->__class__ = cl_FunctionPropertyValue;
        __init__(func_id);
    }
    void *__init__(__ss_int func_id);
    virtual PyObject *__to_py__();
};

extern class_ *cl_FunctumPropertyValue;
class FunctumPropertyValue : public FunctionPropertyValue {
public:
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *functum_prop;

    FunctumPropertyValue() {}
    FunctumPropertyValue(__ss_int func_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *functum_prop) {
        this->__class__ = cl_FunctumPropertyValue;
        __init__(func_id, functum_prop);
    }
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *getFunctumProp();
    void *setFunctumProp(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *functum_prop);
    void *__init__(__ss_int func_id, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *functum_prop);
    virtual PyObject *__to_py__();
};

void __init();
FunctionPropertyValue *shedskin_hidden_data_types(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_data_hidden_data_types(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_data_hidden_data_types(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctionPropertyValueObjectType;
extern PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_hidden_data_types_FunctumPropertyValueObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctionPropertyValue *__to_ss(PyObject *p);
template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__hidden_data_types__::FunctumPropertyValue *__to_ss(PyObject *p);
}
#endif
