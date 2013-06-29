#ifndef __MEPINTA_PIPELINE_LO_CONTEXT_LO_CONTEXTLO_HPP
#define __MEPINTA_PIPELINE_LO_CONTEXT_LO_CONTEXTLO_HPP

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
namespace __context_lo__ {
namespace __ContextLo__ {

extern str *const_0, *const_1, *const_2, *const_3;

class ContextLo;


extern str *__name__;


extern class_ *cl_ContextLo;
class ContextLo : public pyobj {
public:
    dict<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction *> *functions;
    dict<str *, void *> *processors_paths;
    dict<__ss_int, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *> *data_types;
    dict<str *, list<str *> *> *data_type_aliases;
    dict<str *, void *> *data_types_paths;

    ContextLo() {}
    ContextLo(int __ss_init) {
        this->__class__ = cl_ContextLo;
        __init__();
    }
    void *__init__();
    void *appendDataTypeAlias(str *data_type_name, str *data_type_alias);
    virtual PyObject *__to_py__();
};

void __init();
ContextLo *shedskin_ContextLo();

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_context_lo_ContextLo(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_context_lo_ContextLo(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_context_lo_ContextLo_ContextLoObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *__to_ss(PyObject *p);
}
#endif
