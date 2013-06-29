#ifndef __MEPINTA_PIPELINE_LO_PIPELINE_DATA_DATA_MODEL_HPP
#define __MEPINTA_PIPELINE_LO_PIPELINE_DATA_DATA_MODEL_HPP

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
namespace __TopologyConnections__ { /* XXX */
class TopologyConnections;
}
}
}
}
}
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __pipeline_data__ {
namespace __data_model__ {

extern str *const_0, *const_1, *const_10, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;

class DataType;
class ProcessorFunction;
class PropertyValuePointer;
class Property;
class Topology;
class Pipeline;


extern __ss_int FUNCTION_PROPERTY_FLAG, NULL_UID;
extern str *MEPINTA_C_NAMESPACE_PREFIX, *__name__;


extern class_ *cl_DataType;
class DataType : public pyobj {
public:
    str *name;
    dict<str *, void *> *symbols;
    void *lib_handle;

    DataType() {}
    DataType(str *name, void *lib_handle) {
        this->__class__ = cl_DataType;
        __init__(name, lib_handle);
    }
    void *updateHandle(void *lib_handle);
    str *__str__();
    void *getFuncPtr(str *name);
    void *solve_symbol(str *name);
    void *__init__(str *name, void *lib_handle);
    virtual PyObject *__to_py__();
};

extern class_ *cl_ProcessorFunction;
class ProcessorFunction : public pyobj {
public:
    str *name;
    void *func_pointer;

    ProcessorFunction() {}
    ProcessorFunction(str *name, void *func_pointer) {
        this->__class__ = cl_ProcessorFunction;
        __init__(name, func_pointer);
    }
    void *getFuncPointer();
    void *updateFuncPointer(void *func_pointer);
    void *__init__(str *name, void *func_pointer);
    virtual PyObject *__to_py__();
};

extern class_ *cl_PropertyValuePointer;
class PropertyValuePointer : public pyobj {
public:
    __ss_int count;
    void *value;
    __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *function_caller;

    PropertyValuePointer() {}
    PropertyValuePointer(void *value) {
        this->__class__ = cl_PropertyValuePointer;
        __init__(value);
    }
    void *decrementReferenceCount(void *func_ptr_del);
    void *incrementReferenceCount();
    __ss_bool notReferenced();
    void *freeValue(void *func_ptr_del);
    void *getValue();
    void *__init__(void *value);
    void *replaceValue(void *value, void *func_ptr_del);
    virtual PyObject *__to_py__();
};

extern class_ *cl_Property;
class Property : public pyobj {
public:
    __ss_int dtype_id;
    PropertyValuePointer *value_ptr;
    __ss_int type;
    str *name;

    Property() {}
    Property(__ss_int prop_type, str *name, __ss_int dtype_id) {
        this->__class__ = cl_Property;
        __init__(prop_type, name, dtype_id);
    }
    PropertyValuePointer *getValuePtr();
    str *__str__();
    void *setValuePtr(PropertyValuePointer *value_ptr, void *func_ptr_del);
    void *getValue();
    void *__init__(__ss_int prop_type, str *name, __ss_int dtype_id);
    virtual PyObject *__to_py__();
};

extern class_ *cl_Topology;
class Topology : public pyobj {
public:
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__TopologyConnections__::TopologyConnections *connections;
    set<__ss_int> *changed_primary;
    set<__ss_int> *properties;
    set<__ss_int> *cached;

    Topology() {}
    Topology(Topology *copied) {
        this->__class__ = cl_Topology;
        __init__(copied);
    }
    void *disconnect(__ss_int dent_id, __ss_int dency_id);
    void *disconnectAll(__ss_int prop_id);
    void *connectDency(__ss_int dent_id, __ss_int dency_id);
    void *addPropId(__ss_int prop_id);
    str *__str__();
    void *removePropId(__ss_int prop_id);
    void *disconnectDpdencies(__ss_int dent_id);
    void *connect(__ss_int dent_id, __ss_int dency_id);
    void *copyFrom(Topology *copied_topo);
    void *connectDent(__ss_int dent_id, __ss_int dency_id);
    void *__initValues();
    void *__init__(Topology *copied);
    void *__removeFromSet(__ss_int prop_id, set<__ss_int> *set_);
    virtual PyObject *__to_py__();
};

extern class_ *cl_Pipeline;
class Pipeline : public pyobj {
public:
    set<__ss_int> *changed_primary;
    __ss_int property_id_count;
    set<__ss_int> *marked_outputs;
    dict<__ss_int, Property *> *all_properties;
    __ss_int current_topolgy_id;
    set<__ss_int> *changed_track;
    dict<__ss_int, Topology *> *topologies;
    __ss_int topology_id_count;
    str *name;
    __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *cached_link;

    Pipeline() {}
    Pipeline(str *name) {
        this->__class__ = cl_Pipeline;
        __init__(name);
    }
    Topology *getTopology(__ss_int topo_id);
    __ss_bool pendingChanges();
    __ss_int startTopologyChangeSet();
    __ss_int addProperty(Property *prop);
    Topology *popTopology(__ss_int topo_id);
    __ss_int __newTopologyId();
    __ss_int getCurrentTopologyId();
    void *setCurrentTopologyId(__ss_int topo_id);
    Property *deleteProperty(__ss_int prop_id);
    void *__initTopo();
    __ss_int __newPropertyId();
    void *__init__(str *name);
    virtual PyObject *__to_py__();
};

extern str * default_3;
extern void * default_1;
extern void * default_0;
extern __ss_int  default_4;
extern Topology * default_2;

void __init();
tuple2<Pipeline *, __ss_int> *shedskin_pipeline_data_model();

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_data_data_model(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_data_data_model(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObjectType;
extern PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObjectType;
extern PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObjectType;
extern PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObjectType;
extern PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObjectType;
extern PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *__to_ss(PyObject *p);
template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction *__to_ss(PyObject *p);
template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *__to_ss(PyObject *p);
template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *__to_ss(PyObject *p);
template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *__to_ss(PyObject *p);
template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *__to_ss(PyObject *p);
}
#endif
