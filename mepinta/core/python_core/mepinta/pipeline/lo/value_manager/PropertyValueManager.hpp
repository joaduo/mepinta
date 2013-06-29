#ifndef __MEPINTA_PIPELINE_LO_VALUE_MANAGER_PROPERTYVALUEMANAGER_HPP
#define __MEPINTA_PIPELINE_LO_VALUE_MANAGER_PROPERTYVALUEMANAGER_HPP

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
namespace __FunctionCaller__ { /* XXX */
class FunctionCaller;
}
}
}
}
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __value_manager__ {
namespace __PropertyValueManager__ {

extern str *const_0, *const_1, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;

class PropertyValueManager;


extern __ss_int FUNCTION_PROPERTY_FLAG;
extern str *__name__;


extern class_ *cl_PropertyValueManager;
class PropertyValueManager : public pyobj {
public:
    __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *func_caller;
    __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo;

    PropertyValueManager() {}
    PropertyValueManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
        this->__class__ = cl_PropertyValueManager;
        __init__(context_lo);
    }
    void *replacePropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, void *value);
    void *copyPropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *value_ptr);
    void *setPropValuePointer(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *value_ptr);
    void *initPropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);
    void *deletePropsValues(list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *props);
    void *__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo);
    virtual PyObject *__to_py__();
};

void __init();
void *shedskin_PropertyValueManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_value_manager_PropertyValueManager(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_value_manager_PropertyValueManager(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_value_manager_PropertyValueManager_PropertyValueManagerObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *__to_ss(PyObject *p);
}
#endif
