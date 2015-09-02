
#ifndef TYPEDNAMEDPROPERTIESCOLLECTOR_H_
#define TYPEDNAMEDPROPERTIESCOLLECTOR_H_

#include <mepintasdk/sdk.h>
#include "TypedPropertiesCollector.h"

template <typename prop_type>
class TypedNamedPropertiesCollector:
  public TypedPropertiesCollector<prop_type>
{
public:
  //
  TypedNamedPropertiesCollector(MP_args* args, int in_out_id=INPUT_PROPS, const int prop_index=-1)
    :TypedPropertiesCollector<prop_type>(args, in_out_id, prop_index) {}
  //
  TypedNamedPropertiesCollector(const char* data_type_name):
    TypedPropertiesCollector<prop_type>(data_type_name) {}
  //
  TypedNamedPropertiesCollector(void* lib_handle):
    TypedPropertiesCollector<prop_type>(lib_handle) {}

  std::vector<const char*> names;
  std::vector<int> indexes;
private:
  //What to do when the functions lib_handle matches
  inline void onMatch(void** prop, const char* prop_name,const void* lib_handle, const int cur_index){
    this->properties.push_back(CAST_PROP_UNSAFE(prop_type,prop));
    names.push_back(prop_name);
    indexes.push_back(cur_index);
    //TODO: Why is this warning here?
    #warning the function is not virtual!
  }

};

#endif /* TYPEDNAMEDPROPERTIESCOLLECTOR_H_ */
