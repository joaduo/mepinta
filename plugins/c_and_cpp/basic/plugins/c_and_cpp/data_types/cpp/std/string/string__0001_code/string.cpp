#include <mepintasdk/sdk.h>
#include <mepintasdk/log.h>
#include "string.h"

//DECLARE_MEMORY_MNGMNT_FUNCTIONS();

//This function is never published in the header, although it needs to be exported
extern "C" EXPORTED_SYMBOL
const char * MP_get_data_type_name(void){
  return _STR(std::string*);
}

void * MP_cpp_std_string_new(void){
  return new std::string;
}

void * MP_cpp_std_string_delete(void* string_v){
  if(string_v != NULL){
    //log_error("Should delete std::string at %p. (but won't do it because of of Boehm GC)\n",string_v);
    delete (std::string*)string_v;
  }
  return NULL; //Return NULL on success
}

void * MP_cpp_std_string_copy(void* string_v){
  //TODO:
  //log_warning("Check if copy of string is correct: new std::string(*(std::string*)string_v)\n");
  return new std::string(*(std::string*)string_v);
}

size_t MP_cpp_std_string_data_type_size(void){
  return sizeof(std::string);
}

size_t MP_cpp_std_string_mem_size(void* string_v){
  return ((std::string*)string_v)->length() + MP_cpp_std_string_data_type_size();
}

passing_t MP_cpp_std_string_variable_passing(void){
  return by_reference;
}
