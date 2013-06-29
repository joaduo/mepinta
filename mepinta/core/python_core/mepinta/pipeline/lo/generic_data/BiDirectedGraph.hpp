#ifndef __MEPINTA_PIPELINE_LO_GENERIC_DATA_BIDIRECTEDGRAPH_HPP
#define __MEPINTA_PIPELINE_LO_GENERIC_DATA_BIDIRECTEDGRAPH_HPP

using namespace __shedskin__;

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
namespace __generic_data__ {
namespace __BiDirectedGraph__ {

extern str *const_0;

class BiDirectedGraph;


extern str *__name__;


extern class_ *cl_BiDirectedGraph;
class BiDirectedGraph : public pyobj {
public:
    __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *dpdents;
    __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *dpdencies;

    BiDirectedGraph() {}
    BiDirectedGraph(int __ss_init) {
        this->__class__ = cl_BiDirectedGraph;
        __init__();
    }
    void *disconnect(__ss_int dent_id, __ss_int dency_id);
    list<__ss_int> *disconnectAll(__ss_int prop_id);
    str *__str__();
    __ss_int __len__();
    void *disconnectDpdencies(__ss_int dent_id);
    void *connect(__ss_int dent_id, __ss_int dency_id);
    list<__ss_int> *disconnectDpdents(__ss_int dency_id);
    void *__init__();
    BiDirectedGraph *__deepcopy__(dict<void *, pyobj *> *memo);
    virtual PyObject *__to_py__();
};

void __init();
void *shedskin_BiDirectedGraph();

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_generic_data_BiDirectedGraph(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_generic_data_BiDirectedGraph(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_generic_data_BiDirectedGraph_BiDirectedGraphObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__generic_data__::__BiDirectedGraph__::BiDirectedGraph *__to_ss(PyObject *p);
}
#endif
