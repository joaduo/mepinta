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

#ifndef MEPINTA_ARGS_H_
#define MEPINTA_ARGS_H_

#include "types.h"
#include "commondef.h"

CPP_EXTERN_START

//{ mepinta_args
  EXPORTED_SYMBOL mepinta_args* mepinta_args_new(int in_size, int out_size);
  EXPORTED_SYMBOL int mepinta_args_set_capacities(mepinta_args* args,
                                                     int in_size, int out_size);
  EXPORTED_SYMBOL int mepinta_args_delete(mepinta_args* args);
  EXPORTED_SYMBOL int mepinta_args_set_thread_id(mepinta_args* args, int thread_id);
  EXPORTED_SYMBOL int mepinta_args_reset_sizes(mepinta_args* args);
//} mepinta_args

//{ functum
  EXPORTED_SYMBOL functum_st* functum_new(void* function_ptr, mepinta_args* args);
  EXPORTED_SYMBOL int functum_delete(functum_st* functum);
//} functum

CPP_EXTERN_END

#endif /* MEPINTA_ARGS_H_ */
