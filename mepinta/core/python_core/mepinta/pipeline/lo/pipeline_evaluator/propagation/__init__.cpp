#include "builtin.hpp"
#include "mepinta/pipeline/lo/pipeline_evaluator/propagation/__init__.hpp"

namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __pipeline_evaluator__ {
namespace __propagation__ {


str *__name__;



void __init() {
    __name__ = new str("propagation");

}

} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "mepinta/pipeline/lo/pipeline_evaluator/propagation/__init__.hpp"
#include <structmember.h>
#include "mepinta/pipeline/lo/pipeline_evaluator/propagation/__init__.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_propagation;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_evaluator__ { /* XXX */
namespace __propagation__ { /* XXX */
static PyNumberMethods Global_mepinta_pipeline_lo_pipeline_evaluator_propagation_as_number = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

static PyMethodDef Global_mepinta_pipeline_lo_pipeline_evaluator_propagationMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_evaluator_propagation(void) {

    __ss_mod_mepinta_pipeline_lo_pipeline_evaluator_propagation = Py_InitModule((char *)"propagation", Global_mepinta_pipeline_lo_pipeline_evaluator_propagationMethods);
    if(!__ss_mod_mepinta_pipeline_lo_pipeline_evaluator_propagation)
        return;



}

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_evaluator_propagation(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __pipeline_evaluator__

} // namespace __propagation__

} // extern "C"
