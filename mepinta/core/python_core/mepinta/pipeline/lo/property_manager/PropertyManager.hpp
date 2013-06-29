#ifndef __MEPINTA_PIPELINE_LO_PROPERTY_MANAGER_PROPERTYMANAGER_HPP
#define __MEPINTA_PIPELINE_LO_PROPERTY_MANAGER_PROPERTYMANAGER_HPP

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
namespace __generic_data__ { /* XXX */
namespace __DirectedGraph__ { /* XXX */
class DirectedGraph;
class DirectedGraphIterator;
}
}
}
}
}
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __property_manager__ {
namespace __PropertyManager__ {

extern str *const_0, *const_1, *const_2, *const_3, *const_4, *const_5, *const_6;

class PropertyManager;


extern __ss_int FUNCTION_PROPERTY_FLAG, FUNCTUM_PROPERTY_FLAG, INPUT_PROPERTY_FLAG, NULL_UID;
extern str *__name__;


extern class_ *cl_PropertyManager;
class PropertyManager : public pyobj {
public:
    __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *p_value_mngr;
    __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo;

    PropertyManager() {}
    PropertyManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
        this->__class__ = cl_PropertyManager;
        __init__(context_lo);
    }
    list<__ss_int> *createFuncProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<str *> *prop_names, list<__ss_int> *func_ptr_ids);
    void *removeFilters(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids);
    void *deleteProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids);
    void *addNonCached(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *dent_ids, list<__ss_int> *dency_ids);
    list<__ss_int> *createProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<str *> *prop_names, list<__ss_int> *dtype_ids, __ss_int prop_flags);
    void *addFilters(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids);
    list<__ss_int> *createFunctumProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<str *> *prop_names, list<__ss_int> *func_ptr_ids, list<__ss_int> *dtype_ids, __ss_int prop_flags);
    void *removeNonCached(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *dent_ids);
    void *__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo);
    virtual PyObject *__to_py__();
};

void __init();
void *shedskin_PropertyManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id);

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_property_manager_PropertyManager(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_property_manager_PropertyManager(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_property_manager_PropertyManager_PropertyManagerObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__property_manager__::__PropertyManager__::PropertyManager *__to_ss(PyObject *p);
}
#endif
