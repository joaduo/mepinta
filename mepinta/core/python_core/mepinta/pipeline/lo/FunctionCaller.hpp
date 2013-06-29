#ifndef __MEPINTA_PIPELINE_LO_FUNCTIONCALLER_HPP
#define __MEPINTA_PIPELINE_LO_FUNCTIONCALLER_HPP

using namespace __shedskin__;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __exceptions__ { /* XXX */
namespace __MepintaLoError__ { /* XXX */
class MepintaLoError;
}
}
}
}
}
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __FunctionCaller__ {

extern str *const_0, *const_1, *const_2, *const_3, *const_4, *const_5, *const_6;

class FunctionCaller;


extern __ss_int PROCESSOR_FUNC_NULL;
extern str *__name__;


extern class_ *cl_FunctionCaller;
class FunctionCaller : public pyobj {
public:

    FunctionCaller() { this->__class__ = cl_FunctionCaller; }
    void *callCopyToFunc(void *func_ptr, void *to_ptr, void *from_ptr);
    void *callFuncNoArgs(void *func_ptr);
    __ss_int callIntFuncVoidp(void *func_ptr, void *voidp);
    void *callFunc(void *func_ptr, void *func_args);
    __ss_int callProcessorFunc(void *func_ptr, void *args);
    virtual PyObject *__to_py__();
};

void __init();
void *shedskin_FunctionCaller();

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_FunctionCaller(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_FunctionCaller(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_FunctionCaller_FunctionCallerObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *__to_ss(PyObject *p);
}
#endif
