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

#ifndef __PIPELINE_ABSLAYER_LOAD_UNLOAD_LIBRARY_HPP
#define __PIPELINE_ABSLAYER_LOAD_UNLOAD_LIBRARY_HPP

using namespace __shedskin__;
namespace __pipeline_backend__ {
namespace __load_unload_library__ {
namespace __load_unload_library__ {

extern str *__name__;

void __init();
void *loadLibrary(str *path, str *symbol);
__ss_int unloadLibrary(void *handle);

} // module namespace
} // module namespace
} // module namespace
#endif
