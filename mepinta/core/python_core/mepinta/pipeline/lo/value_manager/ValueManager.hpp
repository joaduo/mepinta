#ifndef __MEPINTA_PIPELINE_LO_VALUE_MANAGER_VALUEMANAGER_HPP
#define __MEPINTA_PIPELINE_LO_VALUE_MANAGER_VALUEMANAGER_HPP

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
namespace __value_manager__ {
namespace __ValueManager__ {

extern str *const_0, *const_1, *const_2, *const_3, *const_4, *const_5, *const_6;

class ValueManager;


extern str *__name__;


extern class_ *cl_ValueManager;
class ValueManager : public pyobj {
public:
    __mepinta__::__pipeline__::__lo__::__value_manager__::__PropertyValueManager__::PropertyValueManager *p_value_mngr;
    __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo;

    ValueManager() {}
    ValueManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
        this->__class__ = cl_ValueManager;
        __init__(context_lo);
    }
    void *markChangeSetChangedProps(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids);
    list<__ss_int> *getInts(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids);
    list<void *> *getUntypedPropsValues(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids);
    list<str *> *getCharps(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids);
    list<str *> *getStdStrings(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids);
    void *setUntypedPropsValues(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids, list<void *> *prop_values);
    void *markChangedProps(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids);
    void *__setPropValue(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id, void *value);
    void *setDoubles(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids, list<double> *prop_values);
    void *setCharps(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids, list<str *> *prop_values);
    list<double> *getDoubles(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids);
    void *setStdStrings(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids, list<str *> *prop_values);
    void *__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo);
    void *setInts(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, list<__ss_int> *prop_ids, list<__ss_int> *prop_values);
    virtual PyObject *__to_py__();
};

void __init();
void *shedskin_ValueManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __ss_int prop_id);

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_value_manager_ValueManager(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_value_manager_ValueManager(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_value_manager_ValueManager_ValueManagerObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__value_manager__::__ValueManager__::ValueManager *__to_ss(PyObject *p);
}
#endif
