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
import pyglet
from pyglet.app import BaseEventLoop
from pyglet.window.xlib import xlib
import select

displays = pyglet.app.displays
windows = pyglet.app.windows

# TODO: Win32 and Mac support


class PygletXlibEventLoop(BaseEventLoop):

    '''Modified copy of XlibEventLoop from pyglet.
    This version supports coexistence with an 'InotifyActionManager' through the
    select function. (posix)
    '''

    def __init__(self, inotify_mngr):
        BaseEventLoop.__init__(self)
        self.inotify_mngr = inotify_mngr

    def select(self, rlist, wlist, xlist, timeout):
        rlist.append(self.inotify_mngr.fd)
        rlist, wlist, xlist = select.select(rlist, wlist, xlist, timeout)
        if self.inotify_mngr.fd in rlist:
            rlist.remove(self.inotify_mngr.fd)
            self.inotify_mngr.dispatchEvents()
        return rlist, wlist, xlist

    def run(self):
        self._setup()

        e = xlib.XEvent()
        #t = 0
        sleep_time = 0.

        self.dispatch_event('on_enter')

        while not self.has_exit:
            # Check for already pending events
            for display in displays:
                if xlib.XPending(display._display):
                    pending_displays = (display,)
                    break
            else:
                # None found; select on all file descriptors or timeout
                iwtd = self.getSelectFiles()
                pending_displays, _, _ = self.select(iwtd, (), (), sleep_time)

            # Dispatch platform events
            for display in pending_displays:
                while xlib.XPending(display._display):
                    xlib.XNextEvent(display._display, e)

                    # Key events are filtered by the xlib window event
                    # handler so they get a shot at the prefiltered event.
                    if e.xany.type not in (xlib.KeyPress, xlib.KeyRelease):
                        if xlib.XFilterEvent(e, e.xany.window):
                            continue
                    try:
                        window = display._window_map[e.xany.window]
                    except KeyError:
                        continue

                    window.dispatch_platform_event(e)

            # Dispatch resize events
            for window in windows:
                if window._needs_resize:
                    window.switch_to()
                    window.dispatch_event('on_resize',
                                          window._width, window._height)
                    window.dispatch_event('on_expose')
                    window._needs_resize = False

            sleep_time = self.idle()

        self.dispatch_event('on_exit')

    def getSelectFiles(self):
        return list(displays)
