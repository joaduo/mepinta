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
from common.abstract.FrameworkBase import FrameworkBase
from inotifyx import init, add_watch, rm_watch, get_events, IN_ALL_EVENTS, \
 IN_CREATE, IN_IGNORED, IN_CREATE, IN_DELETE_SELF, IN_DELETE, IN_CLOSE_WRITE, \
 constants, IN_ATTRIB
from getDefaultContext import getDefaultContext

class InotifyActionManager(FrameworkBase):
  #TODO: Looks like a Dispatch pattern since not all action are notified in each change. Unlike an Observer.
  def __post_init__(self):
    self.__wd_action = {}
    self.__post_events_functions = []
    self.skip_post_functions = False

  def get_fd(self):
    if not hasattr(self, '_fd'):
      self._fd = init()
    return self._fd

  def actionWdDict(self):
    return dict((action, wd) for wd, action in self.__wd_action.items())

  def __maskStr(self, mask):
    flags_list = []
    for name, value in constants.items():
      if value & mask and name != 'IN_ALL_EVENTS':
        flags_list.append(name)
    return '|'.join(flags_list)

  def __watchPath(self, path, mask):
    self.log.debug('Adding for fd:%s with flags:%s and path:%s' % (self.fd, self.__maskStr(mask), path))
    wd = add_watch(self.fd, path, mask)
    self.log.debug('Sucessfully added with wd:%s' % wd)
    return wd

  def __removeWatch(self, wd):
    self.log.debug('Removing wd:%s from fd:%s' % (wd, self.fd))
    try:
      rm_watch(self.fd, wd)
    except IOError as error:
      self.log.debug('Ignoring rm_watch IOError %s' % error)
      pass

  def appendPostEventsFunction(self, function):
    if function in self.__post_events_functions:
      raise RuntimeError('Function %r already in post events functions' % function)
    self.__post_events_functions.append(function)

  def removePostEventsFunction(self, function):
    if function in self.__post_events_functions:
      self.__post_events_functions.remove(function)

  def registerAction(self, action):
    self.removeAction(action)
    self.__addAction(action)

  def removeAction(self, action):
    action_wd = self.actionWdDict()
    if action in action_wd:
      wd = action_wd[action]
      self.__removeWatch(wd)
      del self.__wd_action[wd]

  def __addAction(self, action):
    wd = self.__watchPath(action.path, action.mask)
    self.__wd_action[wd] = action

  fd = property(get_fd, None, None, None)

  def __getEvents(self, timeout):
    if timeout == None:
      events = get_events(self.fd)
    else:
      events = get_events(self.fd, timeout)
    return events

  def dispatchEvents(self, timeout=0.0):
    events = self.__getEvents(timeout)
    for event in events:
      if event.wd in self.__wd_action:
        self.log.debug('Got event %s ' % event)
        action = self.__wd_action[event.wd]
        action(event, manager=self)
      elif event.mask & IN_IGNORED:
        self.log.debug('Ignored remove watch event %s' % event)
      else:
        self.log.warning('Unhandled event %s' % event)
    #If there was an event, then run the post functions
    self.__runPostEventsFunctions(len(events))
    return len(events)

  def __runPostEventsFunctions(self, events_count):
    if not self.skip_post_functions and events_count:
      for function in self.__post_events_functions:
        function(manager=self)
    else:
      #Next time won't skip them
      self.skip_post_functions = False

  def blockListeningEvents(self, timeout=None):
    #check that the manager won't block
    if not timeout and not len(self.__wd_action):
      raise RuntimeWarning('There is no event to listen to.')
    self.log.debug('Listening file events.')
    while len(self.__wd_action) > 0:
      self.dispatchEvents(timeout)

if __name__ == '__main__':
  from common.inotify.actions.PathAction import PathAction
  context = getDefaultContext()
  manager = InotifyActionManager(context)

  def actionFunction(event, action, manager):
    action.log('Event: %s' % event)

  path = '/home/jduo/output'
  action = PathAction(context, path=path, mask=IN_ALL_EVENTS)
  action.appendFunction(actionFunction)
  manager.registerAction(action)
  manager.blockListeningEvents()


