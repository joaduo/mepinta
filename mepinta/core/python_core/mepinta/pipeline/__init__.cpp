#include "builtin.hpp"
#include "mepinta/pipeline/__init__.hpp"

namespace __mepinta__ {
namespace __pipeline__ {


str *__name__;



void __init() {
    __name__ = new str("pipeline");

}

} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "mepinta/pipeline/__init__.hpp"
#include <structmember.h>
#include "mepinta/pipeline/__init__.hpp"

PyObject *__ss_mod_mepinta_pipeline;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
static PyNumberMethods Global_mepinta_pipeline_as_number = {
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

static PyMethodDef Global_mepinta_pipelineMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline(void) {

    __ss_mod_mepinta_pipeline = Py_InitModule((char *)"pipeline", Global_mepinta_pipelineMethods);
    if(!__ss_mod_mepinta_pipeline)
        return;



}

PyMODINIT_FUNC addmepinta_pipeline(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // extern "C"
