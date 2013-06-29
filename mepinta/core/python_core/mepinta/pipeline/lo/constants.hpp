#ifndef __MEPINTA_PIPELINE_LO_CONSTANTS_HPP
#define __MEPINTA_PIPELINE_LO_CONSTANTS_HPP

using namespace __shedskin__;
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __constants__ {

extern str *const_0;



extern __ss_int CUSTOM_INPUT_OUTPUT_PROPS, CUSTOM_INPUT_PROPS, CUSTOM_OUTPUT_PROPS, CUSTOM_PROPERTY_FLAG, C_EXIT_FAILURE, C_EXIT_SUCCESS, FUNCTION_PROPERTY_FLAG, FUNCTUM_PROPERTY_FLAG, INPUT_OUTPUT_PROPS, INPUT_PROPERTY_FLAG, INPUT_PROPS, INTERNAL_PROPERTY_FLAG, NULL_UID, OUTPUT_PROPERTY_FLAG, OUTPUT_PROPS, PROCESSOR_EXIT_FAILURE, PROCESSOR_EXIT_NORMAL, PROCESSOR_FUNC_NULL;
extern str *MEPINTA_C_NAMESPACE_PREFIX, *__name__;


void __init();
__ss_bool hasFlags(__ss_int prop_type, __ss_int flags);

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_constants(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_constants(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
namespace __shedskin__ { /* XXX */

}
#endif
