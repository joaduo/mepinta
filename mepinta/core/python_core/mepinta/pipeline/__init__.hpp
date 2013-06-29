#ifndef __MEPINTA_PIPELINE_HPP
#define __MEPINTA_PIPELINE_HPP

using namespace __shedskin__;
namespace __mepinta__ {
namespace __pipeline__ {



extern str *__name__;


void __init();

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline(void);

PyMODINIT_FUNC addmepinta_pipeline(void);

}
} // module namespace
} // module namespace
namespace __shedskin__ { /* XXX */

}
#endif
