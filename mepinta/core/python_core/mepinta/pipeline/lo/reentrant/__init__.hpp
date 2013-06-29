#ifndef __MEPINTA_PIPELINE_LO_REENTRANT_HPP
#define __MEPINTA_PIPELINE_LO_REENTRANT_HPP

using namespace __shedskin__;
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __reentrant__ {



extern str *__name__;


void __init();

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_reentrant(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_reentrant(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
namespace __shedskin__ { /* XXX */

}
#endif
