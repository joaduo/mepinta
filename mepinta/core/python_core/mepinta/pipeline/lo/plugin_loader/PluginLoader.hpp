#ifndef __MEPINTA_PIPELINE_LO_PLUGIN_LOADER_PLUGINLOADER_HPP
#define __MEPINTA_PIPELINE_LO_PLUGIN_LOADER_PLUGINLOADER_HPP

using namespace __shedskin__;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __context_lo__ { /* XXX */
namespace __ContextLo__ { /* XXX */
class ContextLo;
}
}
}
}
}
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */
class PropertyValuePointer;
class Pipeline;
class DataType;
class ProcessorFunction;
class Property;
class Topology;
}
}
}
}
}
namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __plugin_loader__ {
namespace __PluginLoader__ {

extern str *const_0, *const_1, *const_10, *const_11, *const_12, *const_13, *const_14, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;

class PluginLoader;


extern str *__name__;


extern class_ *cl_PluginLoader;
class PluginLoader : public pyobj {
/**
This library will do:
  -Check the correct symbols are in place
  -Get the functions pointer for those symbols
    -Update the table of functions pointers
*/
public:
    __mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo;

    PluginLoader() {}
    PluginLoader(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo) {
        this->__class__ = cl_PluginLoader;
        __init__(context_lo);
    }
    __ss_bool processorIsLoaded(str *path);
    void *loadProcessorLibrary(str *path, dict<str *, __ss_int> *func_dict);
    void *unloadDataTypeLibrary(str *path, __ss_int dtype_id);
    void *__init__(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo);
    void *unloadProcessorLibrary(str *path, list<__ss_int> *func_ids);
    __ss_bool dataTypeIsLoaded(str *path);
    void *loadDataTypeLibrary(str *path, str *data_type_name, __ss_int dtype_id);
    virtual PyObject *__to_py__();
};

void __init();
void *shedskin_PluginLoader(__mepinta__::__pipeline__::__lo__::__context_lo__::__ContextLo__::ContextLo *context_lo);
void *shedskin_test();

extern "C" {
PyMODINIT_FUNC initmepinta_pipeline_lo_plugin_loader_PluginLoader(void);

PyMODINIT_FUNC addmepinta_pipeline_lo_plugin_loader_PluginLoader(void);

}
} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace
extern PyTypeObject __ss_mepinta_pipeline_lo_plugin_loader_PluginLoader_PluginLoaderObjectType;
namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__plugin_loader__::__PluginLoader__::PluginLoader *__to_ss(PyObject *p);
}
#endif
