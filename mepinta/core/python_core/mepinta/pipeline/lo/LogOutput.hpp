#ifndef __MEPINTA_PIPELINE_LO_LOGOUTPUT_HPP
#define __MEPINTA_PIPELINE_LO_LOGOUTPUT_HPP

using namespace __shedskin__;
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __LogOutput__ {

extern str *const_0;

class LogOutput;


extern str *__name__;


extern class_ *cl_LogOutput;
class LogOutput : public pyobj {
public:

    LogOutput() { this->__class__ = cl_LogOutput; }
    void *info(str *msg);
    void *verbose(str *msg);
    void *setLevel(__ss_int level);
    void *critical(str *msg);
    void *error(str *msg);
    void *debug(str *msg);
    void *warning(str *msg);
    virtual PyObject *__to_py__();
};

void __init();
void *shedskin_LogOutput();

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_LogOutput(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_LogOutput(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_LogOutput_LogOutputObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__LogOutput__::LogOutput *__to_ss(PyObject *p);
}
#endif
