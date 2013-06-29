#ifndef __MEPINTA_PIPELINE_LO_VALUE_MANAGER_DEBUGPROPERTYVALUEMANAGER_HPP
#define __MEPINTA_PIPELINE_LO_VALUE_MANAGER_DEBUGPROPERTYVALUEMANAGER_HPP

using namespace __shedskin__;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __exceptions__ { /* XXX */
namespace __MepintaLoError__ { /* XXX */
class MepintaLoError;
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
namespace __value_manager__ { /* XXX */
namespace __PropertyValueManager__ { /* XXX */
class PropertyValueManager;
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
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __value_manager__ {
namespace __DebugPropertyValueManager__ {

extern str *const_0, *const_1, *const_2;

class DebugPropertyValueManager;


extern str *__name__;


extern class_ *cl_DebugPropertyValueManager;
class DebugPropertyValueManager : public pyobj {
/**
This version of PropertyValueManager makes sure the data_type's invariants are
consistent across copying and initialization of properties values. (inside value pointers)
Invariant checking is provided by the checkRepr function in the data type.
*/
public:
    __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *func_caller;
    __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo;
    __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *prop_value_mngr;

    DebugPropertyValueManager() {}
    DebugPropertyValueManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
        this->__class__ = cl_DebugPropertyValueManager;
        __init__(context_lo);
    }
    void *replacePropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, void *value);
    void *deletePropsValues(list<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *> *props);
    void *copyPropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *value_ptr);
    void *__getCheckReprFunction(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);
    void *__checkValueRepr(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, void *value);
    void *initPropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);
    void *setPropValuePointer(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *value_ptr);
    void *__checkRepr(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);
    void *__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo);
    virtual PyObject *__to_py__();
};

void __init();
void *shedskin_DebugPropertyValueManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *prop);

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_value_manager_DebugPropertyValueManager(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_value_manager_DebugPropertyValueManager(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_value_manager_DebugPropertyValueManager_DebugPropertyValueManagerObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__value_manager__::__DebugPropertyValueManager__::DebugPropertyValueManager *__to_ss(PyObject *p);
}
#endif
