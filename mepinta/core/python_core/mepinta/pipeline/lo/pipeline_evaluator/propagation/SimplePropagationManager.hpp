#ifndef __MEPINTA_PIPELINE_LO_PIPELINE_EVALUATOR_PROPAGATION_SIMPLEPROPAGATIONMANAGER_HPP
#define __MEPINTA_PIPELINE_LO_PIPELINE_EVALUATOR_PROPAGATION_SIMPLEPROPAGATIONMANAGER_HPP

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
namespace __pipeline_evaluator__ { /* XXX */
namespace __base__ { /* XXX */
class PipelineEvaluatorBase;
}
}
}
}
}
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __pipeline_evaluator__ {
namespace __propagation__ {
namespace __SimplePropagationManager__ {

class SimplePropagationManager;


extern str *__name__;


extern class_ *cl_SimplePropagationManager;
class SimplePropagationManager : public pyobj {
/**
The properties affected by operations on the topo graph are registered on the
  "topo.changed_primary" set. (changing topology and changing properties' values)
After registering all changes for operations on the topo graph we propagate
  this changes to all the dependents affected by them.
  Then they are stored in the set "topo.changed_secondary"
Now we can keep track of the properties affected by the set of operations on a first order topo.
These means that when we move on the second order topo (action tree),
  we know which Node have changed_primary after applying or undoing a set
  of operations. Those changes are stored in "topo.changed_track"
When we evaluate properties, we check if the property is in "changed_track" set.
  Evaluating it and then removing it.
When we move on the second order pipeline, we add the changes on "topo.changed_primary" to the
  "changed_track" from the node we go by. (supposing we are crossing severals nodes until we reach
  a new working node in the action tree).
*/
public:

    SimplePropagationManager() {}
    SimplePropagationManager(__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *pline_evaluator) {
        this->__class__ = cl_SimplePropagationManager;
        __init__(pline_evaluator);
    }
    void *propagateChanges(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline);
    void *__propagate(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, set<__ss_int> *changed, set<__ss_int> *changed_ppgation);
    void *__propagateOneChange(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *topo, __ss_int prop_id, set<__ss_int> *affected_props);
    void *__init__(__mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *pline_evaluator);
    virtual PyObject *__to_py__();
};

void __init();
void *shedskin_SimplePropagationManager(__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *pline, __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__base__::PipelineEvaluatorBase *pline_evaluator);

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_pipeline_evaluator_propagation_SimplePropagationManager_SimplePropagationManagerObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_evaluator__::__propagation__::__SimplePropagationManager__::SimplePropagationManager *__to_ss(PyObject *p);
}
#endif
