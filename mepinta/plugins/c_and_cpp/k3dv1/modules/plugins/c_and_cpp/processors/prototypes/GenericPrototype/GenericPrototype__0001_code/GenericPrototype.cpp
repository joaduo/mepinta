//Mepinta
//Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar
//
// K-3D
// Copyright (c) 1995-2006, Timothy M. Shead
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

/** \file
        Code based on the GenericPrototype plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>

//Included Data Types
#include <data_types/cpp/std/string/string.h>
#include <data_types/c/builtin/int/int.h>

#include <string>

//Give a brief explanation for your function property.
EXPORTED_SYMBOL
int fooFunction(MP_args* args){
  //Declare Inputs
  INPUT(int,count,args);
  INPUT(std::string*,phrase,args);
  //INPUT(int,new_value,args);

  //Declare Outputs

  log_info("Its gonna blow up!.\n");
  if(count != 0)
    log_info("DIvide by cero: %d",1/count);
  log_info("args %p.\n",args);
  log_info("string is '%s'.\n",phrase->c_str());
  log_info("Printing aaasssaa from fooFunction.\n");
  log_info(".\n");

  return EXIT_NORMAL;
}
