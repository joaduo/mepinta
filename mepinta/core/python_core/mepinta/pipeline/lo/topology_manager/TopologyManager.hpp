#ifndef __MEPINTA_PIPELINE_LO_TOPOLOGY_MANAGER_TOPOLOGYMANAGER_HPP
#define __MEPINTA_PIPELINE_LO_TOPOLOGY_MANAGER_TOPOLOGYMANAGER_HPP

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
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __topology_manager__ {
namespace __TopologyManager__ {

extern str *const_0, *const_1, *const_2;

class TopologyManager;


extern str *__name__;


extern class_ *cl_TopologyManager;
class TopologyManager : public pyobj {
public:

    TopologyManager() {}
    TopologyManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
        this->__class__ = cl_TopologyManager;
        __init__(context_lo);
    }
    void *connectPropsDencies(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_dent_ids, list<__ss_int> *prop_dency_ids);
    void *addProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_ids);
    void *disconnectProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_dent_ids, list<__ss_int> *prop_dency_ids);
    void *enableCached(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *cached_ids);
    void *removeChanged(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_changed_ids);
    void *removeProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_ids);
    void *connectProperties(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_dent_ids, list<__ss_int> *prop_dency_ids);
    void *addChanged(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_changed_ids);
    void *disableCached(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *cached_ids);
    void *__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo);
    void *connectPropsDents(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, list<__ss_int> *prop_dent_ids, list<__ss_int> *prop_dency_ids);
    virtual PyObject *__to_py__();
};

extern list<__ss_int> * default_0;

void __init();
void *shedskin_TopologyManager(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo, __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo);

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_topology_manager_TopologyManager(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_topology_manager_TopologyManager(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_topology_manager_TopologyManager_TopologyManagerObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__topology_manager__::__TopologyManager__::TopologyManager *__to_ss(PyObject *p);
}
#endif
