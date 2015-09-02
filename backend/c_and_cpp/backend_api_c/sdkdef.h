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

#ifndef MEPINTA_SDKDEF_H_
#define MEPINTA_SDKDEF_H_

#include "config.h"
#include "commondef.h"

//{ Constants
//Plugin exit values
//TODO: Should only report exit or success?? Last error messages displayed?
//TODO: sucess, warning, error and critical? So the system knows what to do?
  #define EXIT_NORMAL EXIT_SUCCESS
  #define EXIT_NOT_IMPLEMENTED 51
  #define EXIT_SAFETY_CHECK 52
  #define EXIT_ERROR_MISSING_PROPERTY 101
  #define EXIT_ERROR_PROPERTY_TYPE_ERROR 102
  #define EXIT_ERROR_MISSING_ARGS 103
  #define EXIT_ERROR_PROPERTY_INVALID 104
  #define EXIT_ERROR_UNHANDLED_EXCEPTION 105
  #define EXIT_ERROR_CRITICAL 201


  #define MEPINTA_PLUGIN_C_NAMESPACE "MP_"
  //{ Identify args props, inputs, outputs or both
  //TODO: Rename this? Need to sync this with lo.constants
  #define INPUT_PROPS 1
  #define OUTPUT_PROPS 2
  #define INPUT_OUTPUT_PROPS 3
  #define CUSTOM_INPUT_PROPS 101
  #define CUSTOM_OUTPUT_PROPS 102
  #define CUSTOM_INPUT_OUTPUT_PROPS 103
  //}
  #define GET_DATA_TYPE_NAME_SYMBOL "MP_get_data_type_name"
//} Constants

#endif /* MEPINTA_SDKDEF_H_ */
