//Mepinta
//Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar
//
// K-3D
// Copyright (c) 1995-2011, Timothy M. Shead
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

#ifndef K3D_PARSE_EXPRESSION_H_
#define K3D_PARSE_EXPRESSION_H_

#include <k3dsdk/expression/parser.h>

bool parse_expression(k3d::string_t component_name, k3d::expression::parser& parser, k3d::string_t function, k3d::string_t& variables ){
  bool succes=true;
  if(!parser.parse(function, variables)){
    k3d::log() << error << ": function parsing for '"<< component_name <<"' component failed: " << parser.last_parse_error() << std::endl;
    succes=false;
  }
  return succes;
}

#endif /* K3D_PARSE_EXPRESSION_H_ */
