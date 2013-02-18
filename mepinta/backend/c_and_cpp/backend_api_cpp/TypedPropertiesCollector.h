/*Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

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
along with Mepinta. If not, see <http://www.gnu.org/licenses/>.*/

#ifndef TYPEDPROPERTIESCOLLECTOR_H_
#define TYPEDPROPERTIESCOLLECTOR_H_

#include <mepintasdk/sdk.h>
#include <mepintasdk/cpp/type_checking/demangleTypeName.h>

#include "iTypedPropertiesCollector.h"
#include <vector>
#include <string.h>

//Collect properties of
template <typename prop_type>
class TypedPropertiesCollector:
  public iTypedPropertiesCollector
{
public:
  //We know the last_prop_index of the same type (efficient)
  //If the index is not specified the previously declared property is used
  //TODO: fix this later
  TypedPropertiesCollector(MP_args* args, const int in_out_id=CUSTOM_INPUT_PROPS, int prop_index=-1):
    m_data_type_name(NULL),args(args),m_in_out_id(in_out_id){
    //No index is provided, then use the previous property declared
    if(prop_index == -1){
      prop_index = MP_previous_prop_index(args);
    }
    //Get the correct in_out_id for getting the lib_handle (it's always supposed to be taken from the fixed properties
    int in_out_id_temp = 0;
    if(in_out_id == CUSTOM_INPUT_PROPS)
      in_out_id_temp = INPUT_PROPS;
    else if(in_out_id == CUSTOM_OUTPUT_PROPS)
      in_out_id_temp = OUTPUT_PROPS;

    //Getting the lib_handle value calling MP_next_prop
    //(also need to pass a char** to get the next prop name)
    //Set this->lib_handle according
    char* prop_name;
    if( MP_next_prop(args,in_out_id_temp,&m_lib_handle,&prop_name,&prop_index)!=NULL){
      log_debug("Collecting properties like '%s' of type '%s' .\n",prop_name,MP_full_data_type_name(m_lib_handle));
      this->init();
    }
    else{
      this->init();
      log_warning("Couldn't find a property at index %d for type %s\n",--prop_index,m_data_type_alias);
    }
    //TODO: check if demangled name is correct
  }
  //We know the data_type_name (using TO_STR(dtype)) (kind of inefficient)
  TypedPropertiesCollector(const char* data_type_name):m_data_type_name(data_type_name) {this->init();}
  //We know the lib_handle (efficient)
  TypedPropertiesCollector(void* lib_handle):m_lib_handle(lib_handle) {this->init();}

  ~TypedPropertiesCollector(){
    free((void*)m_data_type_alias);
  }

  #define CAST_PROP_UNSAFE(data_type,value) (*(data_type*)value)

  //Stand-alone implementation (no need to use TypedCollectorManager)
  int collectProperties(){
    int collected_count = 0;
    ASSERT_RETURN(args != NULL, collected_count);
    ASSERT_RETURN(m_lib_handle != NULL || m_data_type_name != NULL , collected_count);

    int cur_index = 0;
    void** prop;
    //No handle defined, search through the properties to find a correct handle
    if(m_lib_handle == NULL){
      void* lib_handle;
      char* prop_name;
      do{
        prop = MP_next_prop_release(args,m_in_out_id,&lib_handle,&prop_name,&cur_index);
      }while(strcmp(m_data_type_name,MP_data_type_name(lib_handle)) != 0 || prop != NULL);

      m_lib_handle = lib_handle;
      if(prop == NULL){
        log_debug("Couldn't find any property of data_type_name:%s",m_data_type_name);
        return collected_count;
      }
      else{
        log_debug("Found a property '%s' of type '%s' with handle at %p.\n",prop_name,m_data_type_name,m_lib_handle);
      }
    }
    //Gather inputs
    while((prop = MP_next_prop_by_type_debug(args,m_in_out_id,m_lib_handle,NULL,&cur_index))
            != NULL){
      properties.push_back(CAST_PROP_UNSAFE(prop_type,prop));
    }
    log_debug("TypedPropertiesCollector lib_handle: %p collected_count: %d\n",m_lib_handle,collected_count);

    return collected_count;
  }

  //To be used by the TypedCollectorManager
  int collectStep(void** prop, const char* prop_name,const void* lib_handle, const int cur_index){
    //If the m_lib_handle is null, then check type by data_type_name (and caching lib_handle for next matching
    if(m_lib_handle == NULL){
      if(strcmp(MP_data_type_name(lib_handle), m_data_type_name) == 0){
        m_lib_handle = (void*)lib_handle;
      }
    }
    else if(m_data_type_name == NULL){
      m_data_type_name = MP_full_data_type_name(m_lib_handle);
      if(strcmp(m_data_type_name, m_data_type_alias) != 0)
        log_warning("Casting '%s' to '%s'.\n",m_data_type_name, m_data_type_alias);
    }

    int collected_count = 0;
    if(m_lib_handle == lib_handle && lib_handle != NULL){
      onMatch(prop,prop_name,lib_handle,cur_index);
      ++collected_count;
    }
    return collected_count;
  }

  //Get a reference of the collected properties
  std::vector<prop_type>* getPropertiesRef(){
    return &properties;
  }
  //Get a copy of the collected properties
  std::vector<prop_type> getProperties(){
    return properties;
  }

  std::vector<prop_type> properties;
private:
  void init(){
    //Demangle from the passed type in the template (will be an alias)
    m_data_type_alias = MP_demangleTypeName(typeid(prop_type).name());
    //We have the lib_handle, we can get the name
    if(m_lib_handle != NULL){
      m_data_type_name = MP_full_data_type_name(m_lib_handle);
      log_debug("Collecting data type name: %s", m_data_type_name);
    }
    //We have the name, we can compare with the alias
    if(m_data_type_name != NULL){
      if(strcmp(m_data_type_name, m_data_type_alias) != 0)
        log_warning("Casting '%s' to '%s'.\n",m_data_type_name, m_data_type_alias);
    }
  }

  //What to do when the functions lib_handle matches
  inline void onMatch(void** prop, const char* prop_name,const void* lib_handle, const int cur_index){
    properties.push_back(CAST_PROP_UNSAFE(prop_type,prop));
    log_debug("Adding prop %s at %p with lib_handle %p and cur_index %d.\n", prop_name, prop, lib_handle, cur_index);
  }

  void* m_lib_handle;
  const char* m_data_type_name;
  const char* m_data_type_alias;
  //args cannot start with m_ to work with declaring MACROS
  MP_args* args;
  int m_in_out_id;
};

#endif /* TYPEDPROPERTIESCOLLECTOR_H_ */
