# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

This file is part of Mepinta.

Mepinta is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Mepinta is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Mepinta. If not, see <http://www.gnu.org/licenses/>.
'''
'''
Created on Sep 15, 2011

@author: jduo
'''
import sys

LOG_CRITICAL = 1
LOG_ERROR = 10
LOG_WARNING = 20
LOG_INFO = 30
LOG_VERBOSE = 40
LOG_DEBUG = 50
LOG_DEBUG_TRACE = 60
LOG_ALL_TRACE = 70

log_level = LOG_INFO


def setLogLevel(level):
    global log_level
    log_level = level


def printLog(level, msg):
    pass


def printTrace(output=''):
    pass


def logCritical(msg):
    printLog(LOG_CRITICAL, msg)


def logError(msg):
    printLog(LOG_ERROR, msg)


def logWarning(msg):
    printLog(LOG_WARNING, msg)


def logInfo(msg):
    printLog(LOG_INFO, msg)


def logVerbose(msg):
    printLog(LOG_VERBOSE, msg)


def logDebug(msg):
    printLog(LOG_DEBUG, msg)


def shedskin_logging():
    msg = 'Something to log'
    logCritical(msg)
    logError(msg)
    logWarning(msg)
    logInfo(msg)
    logVerbose(msg)
    logDebug(msg)

if __name__ == '__main__':
    setLogLevel(LOG_ERROR)
    logInfo('Info shouldn\'t be printed')
    setLogLevel(LOG_INFO)
    logInfo('Info should be printed')
    setLogLevel(LOG_ALL_TRACE)
    logInfo('REALLY VERBOSE')
