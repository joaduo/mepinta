#ifndef __MEPINTA_PIPELINE_LO_GENERIC_DATA_DIRECTEDGRAPH_HPP
#define __MEPINTA_PIPELINE_LO_GENERIC_DATA_DIRECTEDGRAPH_HPP

using namespace __shedskin__;
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __generic_data__ {
namespace __DirectedGraph__ {

extern str *const_0, *const_1, *const_2, *const_3, *const_4;

class DirectedGraphIterator;
class DirectedGraph;


extern __ss_int NULL_UID;
extern str *__name__;


extern class_ *cl_DirectedGraphIterator;
class DirectedGraphIterator : public pyobj {
public:
    list<__ss_int> *__keys;
    list<__ss_int> *__values;
    __ss_int current;

    DirectedGraphIterator() {}
    DirectedGraphIterator(list<__ss_int> *keys, list<__ss_int> *values) {
        this->__class__ = cl_DirectedGraphIterator;
        __init__(keys, values);
    }
    tuple2<__ss_int, __ss_int> *next();
    void *__init__(list<__ss_int> *keys, list<__ss_int> *values);
    virtual PyObject *__to_py__();
};

extern class_ *cl_DirectedGraph;
class DirectedGraph : public pyobj {
public:
    list<__ss_int> *__keys;
    list<__ss_int> *_DirectedGraph__keys;
    list<__ss_int> *__values;
    list<__ss_int> *_DirectedGraph__values;

    DirectedGraph() {}
    DirectedGraph(int __ss_init) {
        this->__class__ = cl_DirectedGraph;
        __init__();
    }
    list<__ss_int> *__getslice__(__ss_int id_1, __ss_int id_2);
    str *__str__();
    __ss_int bisectRight(list<__ss_int> *a, __ss_int x, __ss_int lo, __ss_int hi);
    void *__init__();
    __ss_int index(__ss_int item_id);
    void *__delslice__(__ss_int id_1, __ss_int id_2);
    __ss_bool __contains__(__ss_int item_id);
    void *add(__ss_int item_id, __ss_int value);
    __ss_int getFirst(__ss_int item_id);
    __ss_bool has(__ss_int item_id, __ss_int value);
    __ss_int __len__();
    list<__ss_int> *__getitem__(__ss_int item_id);
    void *__setitem__(__ss_int item_id, __ss_int value);
    list<__ss_int> *__slice__(__ss_int id_1, __ss_int id_2);
    DirectedGraphIterator *getSsIterator();
    tuple2<__ss_int, __ss_int> *bisectLeftRight(list<__ss_int> *a, __ss_int x, __ss_int lo, __ss_int hi);
    __ss_int count(__ss_int item_id);
    void *__delitem__(__ss_int item_id);
    __ss_int bisect_left(list<__ss_int> *a, __ss_int x, __ss_int lo, __ss_int hi);
    void *remove(__ss_int item_id, __ss_int value);
    DirectedGraph *__deepcopy__(dict<void *, pyobj *> *memo);
    virtual PyObject *__to_py__();
};

void __init();
void *shedskin_DirectedGraph();
void *shedskin_test();

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_generic_data_DirectedGraph(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_generic_data_DirectedGraph(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphIteratorObjectType;
extern PyTypeObject __ss_mepinta_pipeline_lo_generic_data_DirectedGraph_DirectedGraphObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraphIterator *__to_ss(PyObject *p);
template<> __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *__to_ss(PyObject *p);
}
#endif
