#ifndef __MEPINTA_PIPELINE_LO_PLUGIN_LOADER_HPP
#define __MEPINTA_PIPELINE_LO_PLUGIN_LOADER_HPP

using namespace __shedskin__;
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __plugin_loader__ {



extern str *__name__;


void __init();

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_plugin_loader(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_plugin_loader(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
namespace __shedskin__ { /* XXX */

}
#endif
