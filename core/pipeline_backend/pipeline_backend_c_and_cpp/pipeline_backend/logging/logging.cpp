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
#include "sys.hpp"
#include "pipeline_backend/logging/logging.hpp"

//MANUALLY EDITED:
#define PIPELINE_ABSLAYER_LOGGING
#include "pipeline_backend_implementation/log.h"

#define LOG_NO_OUTPUT LOG_MEPINTA_NO_OUTPUT
#define LOG_CRITICAL LOG_MEPINTA_CRITICAL
#define LOG_ERROR LOG_MEPINTA_ERROR
#define LOG_WARNING LOG_MEPINTA_WARNING
#define LOG_INFO LOG_MEPINTA_INFO
#define LOG_VERBOSE LOG_MEPINTA_VERBOSE
#define LOG_DEBUG LOG_MEPINTA_DEBUG
#define LOG_DEBUG_TRACE LOG_MEPINTA_DEBUG_TRACE
#define LOG_DEBUG_VERBOSE LOG_MEPINTA_DEBUG_VERBOSE
#define LOG_DEBUG_WARNING LOG_MEPINTA_DEBUG_WARNING
#define LOG_FUNNY LOG_MEPINTA_FUNNY

/**
Created on Sep 15, 2011

@author: jduo
*/

namespace __pipeline_backend__ {
namespace __logging__ {
namespace __logging__ {

str *const_0; //, *const_1, *const_2, *const_3, *const_4;


str *__name__;
//__ss_int LOG_ALL_TRACE, LOG_CRITICAL, LOG_DEBUG, LOG_DEBUG_TRACE, LOG_ERROR, LOG_INFO, LOG_VERBOSE, LOG_WARNING, log_level;


//void * default_0;


void *setLogLevel(__ss_int level) {

  //MANUALLY EDITED:
  MP_set_log_level(level);
  return NULL;
}

void *printLog(__ss_int level, str *msg) {
  //MANUALLY EDITED:
  MP_print_log(level,"%s\n",msg->unit.c_str());

  return NULL;
}

void *logCritical(str *msg) {
    
    printLog(LOG_CRITICAL, msg);
    return NULL;
}

void *logError(str *msg) {
    
    printLog(LOG_ERROR, msg);
    return NULL;
}

void *logWarning(str *msg) {
    
    printLog(LOG_WARNING, msg);
    return NULL;
}

void *logInfo(str *msg) {
    
    printLog(LOG_INFO, msg);
    return NULL;
}

void *logVerbose(str *msg) {
    
    printLog(LOG_VERBOSE, msg);
    return NULL;
}

void *logDebug(str *msg) {
    
    printLog(LOG_DEBUG, msg);
    return NULL;
}

void *shedskin_logging() {
//    str *msg;
//
//    msg = const_0;
//    logCritical(msg);
//    logError(msg);
//    logWarning(msg);
//    logInfo(msg);
//    logVerbose(msg);
//    logDebug(msg);
    return NULL;
}

void __init() {
//    const_0 = new str("Something to log");
//    const_1 = new str("__main__");
//    const_2 = new str("Info shouldn't be printed");
//    const_3 = new str("Info should be printed");
//    const_4 = new str("REALLY VERBOSE");

    __name__ = new str("logging");

//    LOG_CRITICAL = 1;
//    LOG_ERROR = 10;
//    LOG_WARNING = 20;
//    LOG_INFO = 30;
//    LOG_VERBOSE = 40;
//    LOG_DEBUG = 50;
//    LOG_DEBUG_TRACE = 60;
//    LOG_ALL_TRACE = 70;
//    log_level = LOG_INFO;
//    if (__eq(__name__, const_1)) {
//        setLogLevel(LOG_ERROR);
//        logInfo(const_2);
//        setLogLevel(LOG_INFO);
//        logInfo(const_3);
//        setLogLevel(LOG_ALL_TRACE);
//        logInfo(const_4);
//    }
}

} // module namespace
} // module namespace
} // module namespace

