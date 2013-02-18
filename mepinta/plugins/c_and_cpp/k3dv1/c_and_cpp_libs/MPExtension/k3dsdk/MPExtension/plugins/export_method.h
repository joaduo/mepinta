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

#ifndef EXPORT_FUNCTION_H_
#define EXPORT_FUNCTION_H_

#define EXPORT_METHOD(Unpacker,functionName)            \
EXPORTED_SYMBOL                                         \
int functionName(MP_args* args){                        \
  Unpacker unpacker;                                    \
  unpacker.registerArgs(args);                          \
  return unpacker.functionName##_unpackAndRun();    \
} //

#endif /* EXPORT_FUNCTION_H_ */
