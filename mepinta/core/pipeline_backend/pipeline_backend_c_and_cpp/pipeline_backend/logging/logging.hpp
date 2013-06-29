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

#ifndef __PIPELINE_ABSLAYER_LOGGING_HPP
#define __PIPELINE_ABSLAYER_LOGGING_HPP

using namespace __shedskin__;
namespace __pipeline_backend__ {
namespace __logging__ {
namespace __logging__ {

extern str *const_0; //, *const_1, *const_2, *const_3, *const_4;



//extern __ss_int LOG_ALL_TRACE, LOG_CRITICAL, LOG_DEBUG, LOG_DEBUG_TRACE, LOG_ERROR, LOG_INFO, LOG_VERBOSE, LOG_WARNING, log_level;
extern str *__name__;


//extern void * default_0;

void __init();
void *setLogLevel(__ss_int level);
void *printLog(__ss_int level, str *msg);
void *logCritical(str *msg);
void *logError(str *msg);
void *logWarning(str *msg);
void *logInfo(str *msg);
void *logVerbose(str *msg);
void *logDebug(str *msg);
void *shedskin_logging();

} // module namespace
} // module namespace
} // module namespace
#endif
