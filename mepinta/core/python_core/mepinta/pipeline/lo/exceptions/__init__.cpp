#include "builtin.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"

namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __exceptions__ {


str *__name__;



void __init() {
    __name__ = new str("exceptions");

}

} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include <structmember.h>
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_exceptions;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __exceptions__ { /* XXX */
static PyNumberMethods Global_mepinta_pipeline_lo_exceptions_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_exceptionsMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_exceptions(void) {

    __ss_mod_mepinta_pipeline_lo_exceptions = Py_InitModule((char *)"exceptions", Global_mepinta_pipeline_lo_exceptionsMethods);
    if(!__ss_mod_mepinta_pipeline_lo_exceptions)
        return;



}

PyMODINIT_FUNC addmepinta_pipeline_lo_exceptions(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __exceptions__

} // extern "C"
