//Mepinta
//Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar
//
//This file is part of Mepinta.
//
//Mepinta is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//Mepinta is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Mepinta. If not, see <http://www.gnu.org/licenses/>.

#ifndef K3DPROCESSORBASE_H_
#define K3DPROCESSORBASE_H_

#include <string>
#include <typeinfo>

#include <data_types/mepinta/functum/functum.h>
#include <data_types/mepinta/internal_any/internal_any.h>
#include <mepintasdk/sdk.h>

namespace k3d {
namespace MPExtension {
namespace plugins {
namespace processors {
namespace base {

  template <typename hidden_t>
  void* deleteInternalAny(void* internal){
    delete (hidden_t*)internal;
    return NULL;
  }

  class ProcessorBase
  {
  public:
    void registerArgs(MP_args* args){
      this->args = args;
    }

  protected:
    bool previousPropChanged(int in_out_id=INPUT_PROPS, int previous_index=-1){
      if(previous_index == -1){
          previous_index = MP_previous_prop_index(args);
      }
      return MP_has_changed(args,in_out_id,previous_index);
    }

    int callFunctum(mepinta::functum* functum, MP_args* args=NULL){
      return MP_call_functum(functum,args);
    }

    template <typename hidden_t>
    hidden_t& getInternal(const char* prop_name, int in_out_id=INPUT_PROPS){
      mepinta::internal_any* internal_prop = getInternalAnyProp(prop_name, in_out_id);
      initInternalAny<hidden_t>(internal_prop);
      return *(hidden_t*)internal_prop->data;
    }

    template <typename prop_t>
    prop_t getProp(const char* prop_name, int in_out_id=INPUT_PROPS){
      const char* type_name = typeid(prop_t).name();
      prop_t prop_value;
      if (MP_declare_prop_debug(type_name, sizeof(prop_t),(void**)&prop_value
             , args, in_out_id, prop_name) == EXIT_FAILURE ) {
        log_error("Type checking error o non-existence for property value: %s"
                  "with type '%s'. Stopping processor.\n",prop_name,type_name);
        return (prop_t)0;
      }
      return prop_value;
    }

    mepinta::internal_any* getInternalAnyProp(const char* prop_name, int in_out_id=INPUT_PROPS){
      mepinta::internal_any* internal_prop;
      if (MP_declare_prop_debug("mepinta::internal_any*", sizeof(mepinta::internal_any*),(void**)&internal_prop
             , args, in_out_id, prop_name) == EXIT_FAILURE ) {
        log_error("Type checking error o non-existence for property value: %s"
                  "with type 'mepinta::internal_any*'. Stopping processor.\n",prop_name);
        return NULL;
      }
      return internal_prop;
    }


    template <typename hidden_t>
    void initInternalAny(mepinta::internal_any* internal_prop){
      if(internal_prop and internal_prop->data == NULL){
        internal_prop->data = (void*)new hidden_t;
        internal_prop->delete_function = deleteInternalAny<hidden_t>;
      }
    }

    MP_args* args;
  };


}
}
}
}
}

#endif /* PROCESSORBASE_H_ */
