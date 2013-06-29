#include "builtin.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"

/**
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo

This file is part of Mepinta.

Mepinta is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Mepinta is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Mepinta. If not, see <http://www.gnu.org/licenses/>.
*/

namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __exceptions__ {
namespace __MepintaLoError__ {


str *__name__;


str * default_0;


/**
class MepintaLoError
*/

class_ *cl_MepintaLoError;

void MepintaLoError::__static__() {
}

void *shedskin_MepintaLoError() {
    MepintaLoError *e;

    e = (new MepintaLoError());
    return NULL;
}

void __init() {
    __name__ = new str("MepintaLoError");

    cl_MepintaLoError = new class_("MepintaLoError");
    MepintaLoError::__static__();
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include <structmember.h>
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_exceptions_MepintaLoError;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __exceptions__ { /* XXX */
namespace __MepintaLoError__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_exceptions_MepintaLoError_shedskin_MepintaLoError(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(__MepintaLoError__::shedskin_MepintaLoError());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_exceptions_MepintaLoError_as_number = {
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

static PyMethodDef Global_mepinta_pipeline_lo_exceptions_MepintaLoErrorMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_MepintaLoError", (PyCFunction)Global_mepinta_pipeline_lo_exceptions_MepintaLoError_shedskin_MepintaLoError, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_exceptions_MepintaLoError(void) {

    __ss_mod_mepinta_pipeline_lo_exceptions_MepintaLoError = Py_InitModule((char *)"MepintaLoError", Global_mepinta_pipeline_lo_exceptions_MepintaLoErrorMethods);
    if(!__ss_mod_mepinta_pipeline_lo_exceptions_MepintaLoError)
        return;



}

PyMODINIT_FUNC addmepinta_pipeline_lo_exceptions_MepintaLoError(void) {

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __exceptions__

} // namespace __MepintaLoError__

} // extern "C"
