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

/*
 * log.c
 *
 *  Created on: Oct 1, 2011
 *      Author: jduo
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "log.h"
#include "sdk.h"

#define PRINT_FILES 1

int log_level=LOG_MEPINTA_DEBUG; //LOG_MEPINTA_DEBUG by default
int log_format=PRINT_FILES;

int MP_set_log_level(int level){
  log_level = level;
  MP_print_log(LOG_MEPINTA_DEBUG,"Setting log_level=%d\n",level);
  return EXIT_SUCCESS;
}

int MP_get_log_level(){
  return log_level;
}

int MP_print_log(int level, const char* format, ...){
  va_list arguments;
  va_start ( arguments, format );
  if(log_level >= level){
    int return_v;
    //TODO: review coloring and output
    if(LOG_MEPINTA_WARNING >= level){
      return_v = vfprintf(stderr,format,arguments);
    }
    else{
      return_v = vfprintf(stdout,format,arguments);
    }
    if (log_level >= LOG_MEPINTA_DEBUG){
      fflush(stdout); fflush(stderr);//We flush, so we don't miss anything
    }
    return return_v;
  }
  else{
    return EXIT_SUCCESS;
  }
}

//Get the file name from a path
inline const char* _getFileName(const char* file_path){
  int length = strlen(file_path);
  if(length > LOGGING_LENGTH_PATH_TRESHOLD ){
    int char_index;
    for(char_index=length; char_index != -1; --char_index ){
      if(file_path[char_index] == OS_PATH_SEP){
        break;
      }
    }
    if(char_index != -1){
      return file_path+char_index+1;
    }
  }
  return file_path;
}

//Printing log, with filename and line support
int MP_printLog(const char* level_name, int level, const char* file_path, const int line, const char* format, ...){
  va_list arguments;
  va_start ( arguments, format );
  if(log_level >= level){
    int return_v;
    //TODO: review coloring and output
    if(LOG_MEPINTA_WARNING >= level){
      if(log_format & PRINT_FILES){
          fprintf(stderr,"%s:%s:%d: ",level_name,_getFileName(file_path),line);
      }
      return_v = vfprintf(stderr,format,arguments);
    }
    else{
      if(log_format & PRINT_FILES){
          fprintf(stdout,"%s:%d: ",_getFileName(file_path),line);
      }
      return_v = vfprintf(stdout,format,arguments);
    }
    if (log_level >= LOG_MEPINTA_DEBUG){
      fflush(stdout); fflush(stderr);//We flush, so we don't miss anything
    }
    return return_v;
  }
  else{
    return EXIT_SUCCESS;
  }
}
