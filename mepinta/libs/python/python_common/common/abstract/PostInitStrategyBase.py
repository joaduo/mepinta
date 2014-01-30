# -*- coding: utf-8 -*-
'''
Mepinta
Copyright (c) 2011-2013, Joaquin G. Duo

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
from common.python3 import portableGetArgspec
import traceback
import inspect
import sys

class PostInitStrategyBase(object):
  '''
    Adds the "__post_init__" capabilities to a class.
    Arguments received on "__post_init__" should always be passed as keywords,
      if not a TypeError exception will be Raised.
    There is no need to declare arguments as keywords in the method but you need
      to provide them as keywords in the class initialization.
    This class is not meant to be inherited by concrete class, but by
      superclasses.
    Classes inheriting this class must call the _initChildren method in order
      to call all __post_init__ methods.
  '''
  def __init__(self, context):
    '''
    :param context: Unused in the future we could change the strategy algorithm
      depending on the context.
    '''

  def _initChildren(self, args, kwargs):
    '''
    Gets the list of "__pre_init__" and "__post_init__" method for this class.
      Then calls the method in this this order
          __post_init__ (Eldest class in hierarchy)
        __post_init__
      __post_init__  (Concrete class in hierarchy)
      This way each concrete class can make a call before all initializations or after

    '''
    if len(args) > 0:
      raise TypeError('You should provide all "__post_init__" arguments as keywords.')
    # get the list of __post_init__ from lower classes to upper
    posts = []
    self.__getInitLists(self.__class__, posts, set())
    #call the list of __post_init__ (reverse to its discovery)
    self.__callInits(list(reversed(posts)), kwargs)

  def __callInits(self, funcs, kwargs):
    '''
    Iterate functions and pass existing arguments.
    It will inspect each __post_init__ function and pass those arguments from
    kwargs. If non kwargument is missing it will raise a TypeError exception
    with a nice output pointing to the original __post_init__ source.

    :param funcs: list of functions to be called (in that order)
    :param kwargs: kwargs passed to class initialization (except context)
    '''
    for class_, func in funcs:
      args = portableGetArgspec(func)[0]
      #filter those arguments that this __post_init__ receives
      func_kwargs = dict(filter(lambda x: x[0] in args, kwargs.items()))
      try:
        #call the __post_init__ function
        func(self, **func_kwargs)
      except TypeError as error:
        # Extract the traceback of the exception
        tb_list = traceback.extract_tb(sys.exc_info()[2])
        # File where the error occurred
        error_file = self.__cleanPycExt(tb_list[-1][0])
        # if the error was calling func, then report accordingly.
        if error_file == self.__cleanPycExt(__file__):
          # The problems is calling func.
          # Get this traceback
          tb_list = traceback.extract_stack()
          # Create proper message to report the __post_init__ location.
          new_message = self.__reportLocalError(tb_list, class_, func, error)
        else:
          # The problem is not calling func.
          # Format the message so that the location is not lost in the report.
          new_message = self.__reportOutsideError(tb_list, class_, error)
        raise TypeError(new_message)

  def __cleanPycExt(self, file_name):
    '''
    Get rid of .pyc at the end of file name to point to the source .py
    :param file_name:
    '''
    if file_name.endswith('.pyc'):
      return file_name[:-1]
    return file_name

  def __reportOutsideError(self, tb_list, class_, error):
    '''
    Create a report of an error while calling a __post_init__ method and the
    error is thrown outside this module. (class)

    Makes easier to find where the code to be fixed is.

    :param tb_list: traceback list of the error
    :param class_: visited class that produced the error
    :param error: error (exception) thrown while calling func
    '''
    tb_list = traceback.format_list(tb_list)
    msg = '\nTraceback: \n'
    msg += ''.join(tb_list)
    msg += '%s' % error.message
    return msg

  def __reportLocalError(self, tb_list, class_, func, error):
    '''
    Create a report of an error while calling a __post_init__ method and the
    error is thrown within this module. (class)

    Errors are probably argument type errors, so we want to point to the
    declaration of the __post_init__ function that generated the exception

    :param tb_list: traceback list of the error
    :param class_: visited class that produced the error
    :param func: method of the class that produced the error
    :param error: error (exception) thrown while calling func
    '''
    tb_list = traceback.format_list(tb_list[:-3])
    msg = '\nTraceback: \n'
    msg += ''.join(tb_list)
    msg += '%s' % error.message
    # create traceback friendly report
    filename = inspect.getsourcefile(func)
    lines, lineno = inspect.getsourcelines(func)
    line = lines[0]
    name = func.__name__
    extracted_list = [(filename, lineno, name, line)]
    # Print the report
    func_hint = ''.join(traceback.format_list(extracted_list))
    msg += '\n\n%s' % (func_hint)
    msg += '      Remember that %r \n      only accepts keywords arguments in' \
                  ' the constructor.' % class_
    return msg

  def __getInitLists(self, class_, posts, already_added):
    '''
     Visit the inheritance line to gather all the __post_init__ methods
    :param class_: class for methods to be gathered
    :param posts: list of post init functions to be returned (due to recursion)
    :param already_added: set of already visited methods
    '''

    if class_ == PostInitStrategyBase:
      #Its this class we can stop recursion
      return
    #Is a subclass, the check if __post_init__exists
    if issubclass(class_, PostInitStrategyBase):
      if hasattr(class_, '__post_init__') and class_.__post_init__ not in already_added:
        #__post_init__ exists and we haven't add it yet
        posts.append((class_, class_.__post_init__))
        #remember it
        already_added.add(class_.__post_init__)
      #visit superclasses
      self.__getInitLists(class_.__base__, posts, already_added)
    else:
      #We end up in a superclass that is not this class. Consider it an error
      raise TypeError('InitStrategyBase should be on the main inheritance line.')


def smokeTestModule():
  class ExtendedBase(PostInitStrategyBase):
    def __post_init__(self, value, value1, test1=1, tat1=20):
      self.post_init_var1 = value1

  class ConcreteClass(ExtendedBase):
    def __post_init__(self, value, too, test=1, tat=20):
      self.post_init_var = value

  from common.context.Context import Context
  ctx = Context('python')
  cc = ConcreteClass(context=ctx)
  cc._initChildren([], dict(context=ctx, too=2, something=2312, value1=231, other_value=20, value=100, test=2))
  # print(cc.post_init_var, cc.post_init_var1)

if __name__ == '__main__':
  smokeTestModule()



