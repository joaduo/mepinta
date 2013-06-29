#include "builtin.hpp"
#include "mepinta/pipeline/lo/topology_manager/__init__.hpp"

namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __topology_manager__ {


str *__name__;



void __init() {
    __name__ = new str("topology_manager");

}

} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "mepinta/pipeline/lo/topology_manager/__init__.hpp"
#include <structmember.h>
#include "mepinta/pipeline/lo/topology_manager/__init__.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_topology_manager;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __topology_manager__ { /* XXX */
static PyNumberMethods Global_mepinta_pipeline_lo_topology_manager_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_topology_managerMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_topology_manager(void) {

    __ss_mod_mepinta_pipeline_lo_topology_manager = Py_InitModule((char *)"topology_manager", Global_mepinta_pipeline_lo_topology_managerMethods);
    if(!__ss_mod_mepinta_pipeline_lo_topology_manager)
        return;



}

PyMODINIT_FUNC addmepinta_pipeline_lo_topology_manager(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __topology_manager__

} // extern "C"
