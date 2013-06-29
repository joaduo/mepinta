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
 * mepinta_logging.c
 *
 *  Created on: Oct 1, 2011
 *      Author: jduo
 */

#ifndef MEPINTA_LOG_H_
#define MEPINTA_LOG_H_

#include "config.h"

#define LOG_MEPINTA_NO_OUTPUT 0
#define LOG_MEPINTA_CRITICAL 1
#define LOG_MEPINTA_ERROR 10
#define LOG_MEPINTA_WARNING 20
#define LOG_MEPINTA_INFO 30
#define LOG_MEPINTA_VERBOSE 40
#define LOG_MEPINTA_DEBUG 50
#define LOG_MEPINTA_DEBUG_TRACE 60
#define LOG_MEPINTA_DEBUG_VERBOSE 70
#define LOG_MEPINTA_DEBUG_WARNING 80
#define LOG_MEPINTA_FUNNY 200

#ifndef PIPELINE_ABSLAYER_LOGGING
  #ifdef MEPINTA_DEBUG
    #define PRINT_FORMAT(level,fmt) #level,level,__FILE__,__LINE__,fmt
    #define log_critical(fmt, ...) MP_printLog(PRINT_FORMAT(LOG_MEPINTA_CRITICAL,fmt),##__VA_ARGS__)
    #define log_error(fmt, ...) MP_printLog(PRINT_FORMAT(LOG_MEPINTA_ERROR,fmt),##__VA_ARGS__)
    #define log_warning(fmt, ...) MP_printLog(PRINT_FORMAT(LOG_MEPINTA_WARNING,fmt),##__VA_ARGS__)
    #define log_info(fmt, ...) MP_printLog(PRINT_FORMAT(LOG_MEPINTA_INFO,fmt),##__VA_ARGS__)
    #define log_verbose(fmt, ...) MP_printLog(PRINT_FORMAT(LOG_MEPINTA_VERBOSE,fmt),##__VA_ARGS__)
    #define log_debug(fmt, ...) MP_printLog(PRINT_FORMAT(LOG_MEPINTA_DEBUG,fmt),##__VA_ARGS__)
    //TODO: print __FILE__ and __LINE__
    #define log_trace(fmt, ...) MP_printLog(PRINT_FORMAT(LOG_MEPINTA_DEBUG_TRACE,fmt),##__VA_ARGS__)
    //TODO: delete both functions below?
    #define log_debug_verbose(fmt, ...) MP_printLog(PRINT_FORMAT(LOG_MEPINTA_DEBUG_VERBOSE,fmt),##__VA_ARGS__)
    #define log_debug_warning(fmt, ...) MP_printLog(PRINT_FORMAT(LOG_MEPINTA_DEBUG_WARNING,fmt),##__VA_ARGS__)
    #define log_funny(fmt, ...) MP_printLog(PRINT_FORMAT(LOG_MEPINTA_FUNNY,fmt),##__VA_ARGS__)
  #else
  //  #define log_critical(fmt, ...) MP_print_log(LOG_MEPINTA_CRITICAL,fmt,##__VA_ARGS__)
  //  #define log_error(fmt, ...) MP_print_log(LOG_MEPINTA_ERROR,fmt,##__VA_ARGS__)
  //  #define log_warning(fmt, ...) MP_print_log(LOG_MEPINTA_WARNING,fmt,##__VA_ARGS__)
  //  #define log_info(fmt, ...) MP_print_log(LOG_MEPINTA_INFO,fmt,##__VA_ARGS__)
  //  #define log_verbose(fmt, ...) MP_print_log(LOG_MEPINTA_VERBOSE,fmt,##__VA_ARGS__)
  //  #define log_debug(fmt, ...) MP_print_log(LOG_MEPINTA_DEBUG,fmt,##__VA_ARGS__)
  //  //TODO: print __FILE__ and __LINE__
  //  #define log_trace(fmt, ...) MP_print_log(LOG_MEPINTA_DEBUG_TRACE,fmt,##__VA_ARGS__)
  //  //TODO: delete both functions below?
  //  #define log_debug_verbose(fmt, ...) MP_print_log(LOG_MEPINTA_DEBUG_VERBOSE,fmt,##__VA_ARGS__)
  //  #define log_debug_warning(fmt, ...) MP_print_log(LOG_MEPINTA_DEBUG_WARNING,fmt,##__VA_ARGS__)
  //  #define log_funny(fmt, ...) MP_print_log(LOG_MEPINTA_FUNNY,fmt,##__VA_ARGS__)
  #endif
#endif

//Aliases
#define logError log_error

#ifdef __cplusplus
extern "C" {
#endif

//extern int mepinta_set_log_level_from_args(MP_args_p args);
EXPORTED_SYMBOL int MP_set_log_level(int level);
EXPORTED_SYMBOL int MP_get_log_level();
EXPORTED_SYMBOL int MP_print_log(int level, const char* format, ...);
EXPORTED_SYMBOL int MP_printLog(const char* level_name, int level, const char* file_path, const int line, const char* format, ...);
#ifdef __cplusplus
}
#endif

#endif /* MEPINTA_LOG_H_ */
