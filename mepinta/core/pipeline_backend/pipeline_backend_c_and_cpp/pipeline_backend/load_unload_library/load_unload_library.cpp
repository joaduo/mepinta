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

#include "builtin.hpp"
//#include "sys.hpp"
#include "pipeline_backend/load_unload_library/load_unload_library.hpp"

//MANUALLY EDITED:
#include "pipeline_backend_implementation/load_unload_library.h"

/**
Created on Sep 28, 2011

@author: jduo
*/

namespace __pipeline_backend__ {
namespace __load_unload_library__ {
namespace __load_unload_library__ {

str *__name__;

void *load_library(str *path, str *symbol) {
  LOAD_LIBRARY;
}

__ss_int unload_library(void *handle) {
  UNLOAD_LIBRARY;
}

void __init() {
    __name__ = new str("load_unload_library");

}

} // module namespace
} // module namespace
} // module namespace
