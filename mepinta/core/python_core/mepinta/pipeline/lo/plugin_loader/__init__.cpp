#include "builtin.hpp"
#include "mepinta/pipeline/lo/plugin_loader/__init__.hpp"

namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __plugin_loader__ {


str *__name__;



void __init() {
    __name__ = new str("plugin_loader");

}

} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "mepinta/pipeline/lo/plugin_loader/__init__.hpp"
#include <structmember.h>
#include "mepinta/pipeline/lo/plugin_loader/__init__.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_plugin_loader;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __plugin_loader__ { /* XXX */
static PyNumberMethods Global_mepinta_pipeline_lo_plugin_loader_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_plugin_loaderMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_plugin_loader(void) {

    __ss_mod_mepinta_pipeline_lo_plugin_loader = Py_InitModule((char *)"plugin_loader", Global_mepinta_pipeline_lo_plugin_loaderMethods);
    if(!__ss_mod_mepinta_pipeline_lo_plugin_loader)
        return;



}

PyMODINIT_FUNC addmepinta_pipeline_lo_plugin_loader(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __plugin_loader__

} // extern "C"
