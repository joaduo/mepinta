#ifndef __MEPINTA_PIPELINE_LO_EXCEPTIONS_MEPINTALOERROR_HPP
#define __MEPINTA_PIPELINE_LO_EXCEPTIONS_MEPINTALOERROR_HPP

using namespace __shedskin__;
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __exceptions__ {
namespace __MepintaLoError__ {

class MepintaLoError;


extern str *__name__;


extern class_ *cl_MepintaLoError;
class MepintaLoError : public Exception {
public:
    str *msg;
    str *message;

    MepintaLoError() {}
    MepintaLoError(str *msg) {
        this->__class__ = cl_MepintaLoError;
        __init__(msg);
    }
    static void __static__();
};

extern str * default_0;

void __init();
void *shedskin_MepintaLoError();

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_exceptions_MepintaLoError(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_exceptions_MepintaLoError(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
namespace __shedskin__ { /* XXX */

}
#endif
