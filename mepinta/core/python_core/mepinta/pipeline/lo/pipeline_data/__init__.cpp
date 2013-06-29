#include "builtin.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"

namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __pipeline_data__ {


str *__name__;



void __init() {
    __name__ = new str("pipeline_data");

}

} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include <structmember.h>
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_pipeline_data;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
static PyNumberMethods Global_mepinta_pipeline_lo_pipeline_data_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_pipeline_dataMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_data(void) {

    __ss_mod_mepinta_pipeline_lo_pipeline_data = Py_InitModule((char *)"pipeline_data", Global_mepinta_pipeline_lo_pipeline_dataMethods);
    if(!__ss_mod_mepinta_pipeline_lo_pipeline_data)
        return;



}

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_data(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __pipeline_data__

} // extern "C"
