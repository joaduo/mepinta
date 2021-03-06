# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo

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
from mepinta.testing.plugins_testing.ProcessorPluginTestRunner import ProcessorPluginTestRunner
from getDefaultContext import getDefaultContext
from pipeline_backend.logging.logging import LOG_INFO, LOG_DEBUG
from mepinta.testing.plugins_testing.test_pipeline.InotifySimpleTestPipeline import InotifySimpleTestPipeline

if __name__ == "__main__":
    #  context = getDefaultContext(LOG_DEBUG)
    context = getDefaultContext(LOG_INFO)
    import plugins_tests.inotify_tests.MorphPoints_test as MorphPoints

    ptr = ProcessorPluginTestRunner(context)
    ptr.blockListeningEvents(MorphPoints)
    #ptr.blockListeningEvents(MorphPoints, gui=False)
