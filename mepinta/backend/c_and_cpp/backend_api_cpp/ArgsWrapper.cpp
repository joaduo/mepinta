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

#if 0

//TODO: check better sprint
//TODO: rename to UserPropertiesManager<double>(last_index=args__getLastPropertyIndex(args))
//TODO: rename to DoubleUserPropertiesManager<str,double>(last_index=args__getLastPropertyIndex(args))
//TODO: rename to TripleUserPropertiesManager<str,double,mesh>(last_index=args__getLastPropertyIndex(args))
//TODO: concatenate UserPropertyManagers in a dispatch pattern or whatever
//only do collecting props
//std::vector<double> values = args_wrapper.inputs.getTypedProperties<double>()
//class ArgsWrapper_debug{
//public:
//
//private:
//};

//TypedPropertiesVector
//iTypedPropertiesCollector
#include <mepinta/sdk.h>
#include <string.h>

#include <vector>
#include <typeinfo>



//Collect properties of
template <typename prop_type>
class TypedPropertiesCollector:
  public iTypedPropertiesCollector
{
public:
  //We know the last_prop_index of the same type (efficient)
  TypedPropertiesCollector(MP_args* args, int in_out_id, const int last_prop_index=-1):
    args(args),in_out_id(in_out_id),first_prop_index(last_prop_index){
    if(last_prop_index == -1){
      this->first_prop_index = MP_previous_prop_index(args);
      log_debug("last_prop_index=-1, setting this->last_prop_index from args to: %d \n",this->first_prop_index);
    }
    char* prop_name;
    MP_next_prop(args,in_out_id,&lib_handle,&prop_name,&this->first_prop_index);
  }
  //This type of constructor needs work on MepintaArgsApi library
//  TypedPropertiesCollector(){
//    data_type_name = typeid(prop_type).name();
//  }
  //We know the data_type_name (using TO_STR(dtype)) (inefficient)
  TypedPropertiesCollector(const char* data_type_name):data_type_name(data_type_name) {}
  //We know the lib_handle (efficient)
  TypedPropertiesCollector(void* lib_handle):lib_handle(lib_handle) {}

  #define CAST_PROP_UNSAFE(data_type,value) (*(data_type*)value)

  //Stand-alone implementation (no need to use TypedCollectorManager)
  int collectProperties(){
    int collected_count = 0;
    ASSERT_RETURN(this->args != NULL, collected_count);

    int cur_index = first_prop_index+1;
    void** prop;
    //Gather inputs (only charp)
    while((prop = MP_next_prop_by_type_debug(args,in_out_id,lib_handle,NULL,&cur_index))
            != NULL){
      properties.push_back(CAST_PROP_UNSAFE(prop_type,prop));
    }
    log_debug("TypedPropertiesCollector lib_handle: %p collected_count: %d\n",lib_handle,collected_count);
    return collected_count;
  }

  int collectStep(void** prop, const char* prop_name,const void* lib_handle, const int cur_index){
    if(this->lib_handle == NULL){
      const char* data_type_name = MP_data_type_name(lib_handle);
      if(strcmp(data_type_name, this->data_type_name) == 0){
        this->lib_handle = (void*)lib_handle;
      }
    }
    int collected_count = 0;
    if(this->lib_handle == lib_handle && lib_handle != NULL){
      properties.push_back(CAST_PROP_UNSAFE(prop_type,prop));
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

private:
  std::vector<prop_type> properties;
  void* lib_handle;
  const char* data_type_name;
  MP_args* args;
  int in_out_id;
  int first_prop_index;
};

//class TypedCollectorManager:
//  public std::vector<iTypedPropertiesCollector*>
//{
//public:
//  ~TypedCollectorManager(){
//    for(unsigned int i; i < this->size(); ++i){
//        iTypedPropertiesCollector* collector = this->back();
//        delete collector;
//        this->pop_back();
//    }
//    //Is this necessary? Don't think so?
//    //delete (std::vector<iTypedPropertiesCollector*>*)this;
//  }
//
//  //Need args, IN or OUT properties, and the last index of the declared properties
//  TypedCollectorManager(MP_args* args, const int in_out_id, const int last_prop_index):
//    args(args),in_out_id(in_out_id),first_prop_index(last_prop_index) {}
//
//  //Append a Typed collector
//  template <typename prop_type>
//  void appendCollector(const char* data_type_name){
//    TypedPropertiesCollector<prop_type>* collector = new TypedPropertiesCollector<prop_type>(data_type_name);
//    this->push_back(collector);
//  }
//  int collectProperties();
//
//private:
//  //std::vector<iTypedPropertiesCollector*> collectors;
//  MP_args* args;
//  int in_out_id;
//  int first_prop_index;
//};
//int TypedCollectorManager::collectProperties(){
//  int collected_count = 0;
//  //We ask for the lib_hanlde in order to filter properties later
//  void* lib_handle;
//  //MP_next_prop(args,INPUT_PROPS,&lib_handle,NULL,&charp_index);
//
//  int cur_index = first_prop_index;
//  char* prop_name;
//  void** prop;
//  //Gather inputs (only charp)
//  while((prop = MP_next_prop(args,in_out_id,&lib_handle,&prop_name,&cur_index))
//          != NULL){
//    for(size_t i=0 ; i < this->size(); ++i){
//      collected_count += this->at(i)->collectStep(prop,prop_name,lib_handle,cur_index);
//    }
//    log_debug("TypedCollectorManager prop_name: %s, lib_handle: %p collected_count: %d\n",prop_name,lib_handle,collected_count);
//  }
//
//  return collected_count;
//}

class TypedCollectorManager{
public:
  //args: Mepinta args
  //in_out_id: INPUT_PROPS, OUTPUT_PROPS //TODO: INPUT_OUTPUT_PROPS
  //last_prop_index: the last_prop_index of the declared variables
  // if it's -1 it will get the one from args
  TypedCollectorManager(MP_args* args, const int in_out_id, const int last_prop_index=-1):
    args(args),in_out_id(in_out_id),last_prop_index(last_prop_index) {
    if(last_prop_index == -1){
      this->last_prop_index = MP_previous_prop_index(args);
      log_debug("last_prop_index=-1, setting this->last_prop_index from args to: %d \n",this->last_prop_index);
    }
  }

  void appendCollector(iTypedPropertiesCollector* collector);
  iTypedPropertiesCollector* popCollector();
  int collectProperties();
private:
  std::vector<iTypedPropertiesCollector*> collectors;
  MP_args* args;
  int in_out_id;
  int last_prop_index;
};

#endif
