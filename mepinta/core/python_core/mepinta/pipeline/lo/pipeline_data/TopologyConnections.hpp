#ifndef __MEPINTA_PIPELINE_LO_PIPELINE_DATA_TOPOLOGYCONNECTIONS_HPP
#define __MEPINTA_PIPELINE_LO_PIPELINE_DATA_TOPOLOGYCONNECTIONS_HPP

using namespace __shedskin__;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __generic_data__ { /* XXX */
namespace __BiDirectedGraph__ { /* XXX */
class BiDirectedGraph;
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
namespace __pipeline_data__ {
namespace __TopologyConnections__ {

extern str *const_0, *const_1;

class TopologyConnections;


extern str *__name__;


extern class_ *cl_TopologyConnections;
class TopologyConnections : public pyobj {
/**
Stores the Topology's Graph connections. (navigatable in both directions)

Since these connections can be arbitrary directed, this Object stores a second
copy of the Graph (self.navigation) with bidirectional information for each
connection, for navigation through the graph.
*/
public:
    __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *dpdents;
    __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *dpdencies;
    __mepinta__::__pipeline__::__lo__::__generic_data__::__BiDirectedGraph__::BiDirectedGraph *navigation;

    TopologyConnections() {}
    TopologyConnections(int __ss_init) {
        this->__class__ = cl_TopologyConnections;
        __init__();
    }
    void *disconnect(__ss_int dent_id, __ss_int dency_id);
    list<__ss_int> *disconnectAll(__ss_int prop_id);
    void *connectDency(__ss_int dent_id, __ss_int dency_id);
    str *__str__();
    __ss_int __len__();
    void *disconnectDpdencies(__ss_int dent_id);
    void *connect(__ss_int dent_id, __ss_int dency_id);
    list<__ss_int> *disconnectDpdents(__ss_int dency_id);
    void *connectDent(__ss_int dent_id, __ss_int dency_id);
    void *__init__();
    TopologyConnections *__deepcopy__(dict<void *, pyobj *> *memo);
    virtual PyObject *__to_py__();
};

void __init();
void *shedskin_TopologyConnections();

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_data_TopologyConnections(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_data_TopologyConnections(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_TopologyConnections_TopologyConnectionsObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__TopologyConnections__::TopologyConnections *__to_ss(PyObject *p);
}
#endif
