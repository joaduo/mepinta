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
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"

//MANUALLY EDITED:
#include "pipeline_backend_implementation/solve_symbol.h"

/**
Created on Sep 13, 2011

@author: jduo
*/

namespace __pipeline_backend__ {
namespace __solve_symbol__ {
namespace __solve_symbol__ {


str *__name__;


void *solve_symbol(void *handle, str *__ss_namespace, str *symbol) {
    str *complete_symbol;

    complete_symbol = (__ss_namespace)->__add__(symbol);
    //MANUALLY EDITED:
    SHEDSKIN_SOLVE_SYMBOL;
}

void __init() {
    __name__ = new str("solve_symbol");

}

} // module namespace
} // module namespace
} // module namespace

