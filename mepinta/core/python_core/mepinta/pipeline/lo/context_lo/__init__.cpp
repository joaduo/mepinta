#include "builtin.hpp"
#include "mepinta/pipeline/lo/context_lo/__init__.hpp"

namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __context_lo__ {


str *__name__;



void __init() {
    __name__ = new str("context_lo");

}

} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "mepinta/pipeline/lo/context_lo/__init__.hpp"
#include <structmember.h>
#include "mepinta/pipeline/lo/context_lo/__init__.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_context_lo;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __context_lo__ { /* XXX */
static PyNumberMethods Global_mepinta_pipeline_lo_context_lo_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_context_loMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_context_lo(void) {

    __ss_mod_mepinta_pipeline_lo_context_lo = Py_InitModule((char *)"context_lo", Global_mepinta_pipeline_lo_context_loMethods);
    if(!__ss_mod_mepinta_pipeline_lo_context_lo)
        return;



}

PyMODINIT_FUNC addmepinta_pipeline_lo_context_lo(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __context_lo__

} // extern "C"
