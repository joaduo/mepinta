#include "builtin.hpp"
#include "mepinta/pipeline/lo/reentrant/__init__.hpp"

namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __reentrant__ {


str *__name__;



void __init() {
    __name__ = new str("reentrant");

}

} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "mepinta/pipeline/lo/reentrant/__init__.hpp"
#include <structmember.h>
#include "mepinta/pipeline/lo/reentrant/__init__.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_reentrant;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __reentrant__ { /* XXX */
static PyNumberMethods Global_mepinta_pipeline_lo_reentrant_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_reentrantMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_reentrant(void) {

    __ss_mod_mepinta_pipeline_lo_reentrant = Py_InitModule((char *)"reentrant", Global_mepinta_pipeline_lo_reentrantMethods);
    if(!__ss_mod_mepinta_pipeline_lo_reentrant)
        return;



}

PyMODINIT_FUNC addmepinta_pipeline_lo_reentrant(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __reentrant__

} // extern "C"
