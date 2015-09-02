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

#ifndef EXPRESSION_APPEND_VARIABLE_H_
#define EXPRESSION_APPEND_VARIABLE_H_

#include <mepintasdk/sdk.h>
#include <string>
#include <vector>
#include <string.h>

//Append a variable if the name was defined
inline unsigned int append_variable(char* name, std::string& variables, std::vector<double>& values, double value ){
  if( strcmp("",name) !=0 ){
    log_debug("Appending variable with name %s and value %lf.\n",name,value);
    variables += ",";
    variables += name;
    values.push_back(value);
    return 1;
  }
  else{
    log_debug("Ignoring unnamed variable with value %lf.\n",name);
  }
  return 0;
}

//Append a variable if the name was defined
inline unsigned int append_variable(char* name, std::string* variables, std::vector<double>* values, double value ){
  if( strcmp("",name) !=0 ){
    log_debug("Appending variable with name %s and value %lf.\n",name,value);
    *variables += ",";
    *variables += name;
    values->push_back(value);
    return 1;
  }
  else{
    log_debug("Ignoring unnamed variable with value %lf.\n",name);
  }
  return 0;
}

//Append a variable if the name was defined
inline unsigned int append_variable(const std::string& name, std::string& variables, std::vector<double>& values, double value ){
  if( name.length() !=0 ){
    log_debug("Appending variable with name %s and value %lf.\n",name.c_str(),value);
    variables += ",";
    variables += name;
    values.push_back(value);
    return 1;
  }
  else{
    log_debug("Ignoring unnamed variable with value %lf.\n",value);
  }
  return 0;
}

#endif /* EXPRESSION_APPEND_VARIABLE_H_ */
