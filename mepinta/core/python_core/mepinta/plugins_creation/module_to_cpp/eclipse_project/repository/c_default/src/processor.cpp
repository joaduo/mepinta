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

#include <mepintasdk/sdk.h>

//Give a brief explanation for your function property and give it a proper name
EXPORTED_SYMBOL
int functionName(MP_args* args){
  /*
   * Declare your inputs and outputs.
   * For example:
   * INPUT(double,prop_name,args);
   * OUTPUT(char*,prop_name,args);
   */
  log_info("Printing from processFunctionName.\n");
  return EXIT_NORMAL;
}
