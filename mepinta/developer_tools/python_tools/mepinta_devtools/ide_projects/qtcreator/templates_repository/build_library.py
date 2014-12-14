#!/usr/bin/python
# -*- coding: utf-8 -*-
'''
Mepinta
'''
import subprocess
import shlex
import os
import sys


def logInfo(msg):
    print(msg)


def logError(msg):
    sys.stderr.write(msg + '\n')


def main(argv):
    os.chdir(os.path.dirname(__file__))
    target = '${TARGET}'
    logInfo('Building %s ...' % target)
    for cmd in ('qmake %s.pro' % target, 'make'):
        cmd_split = shlex.split(cmd)
        p = subprocess.Popen(
            cmd_split, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        r_value = p.wait()
        stderr = p.stderr.read()
        stdout = p.stdout.read()
        if r_value != 0:
            logError('There was an error building %s.so cmd=%r.' %
                     (target, cmd))
            logError(stderr)
            logError(stdout)
            sys.exit(r_value)
    logInfo('Done building %s.' % target)

if __name__ == "__main__":
    main(None)
