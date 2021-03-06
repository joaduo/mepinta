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

from common.abstract.FrameworkBase import FrameworkBase
from mepinta.pipeline.hi.FactoryLo import FactoryLo, unwrapLo
from common.abstract.FrameworkObject import FrameworkObject
from mepinta.abstract.MepintaError import MepintaError
import inspect

# TODO: clean code in this module and add tests


class SafeCheckWrapper(FrameworkObject):

    def __init__(self, function, function_safe):
        self.function = function
        self.function_safe = function_safe

    def __call__(self, *a, **ad):
        checkings = self.function_safe(*a, **ad)
        if isinstance(checkings, dict):
            for filterFunc, list_ in checkings.items():
                self.safeCheck(filterFunc, list_)
        return self.function(*a, **ad)

    def safeCheck(self, filterFunc, list_):
        if len(list(filter(filterFunc, list_))) != 0:
            raise MepintaError('Safe check function %r for function %r failed ' % (
                inspect.getsource(filterFunc), self.function))


class HiBase(FrameworkBase):

    '''
      Base class for classes on pipeline.hi
        Classes inheriting this class should a companion class
        in mepinta.pipeline.lo
    '''

    def __post_init__(self):
        self.factory_lo = FactoryLo(context=self.context)

    def _getWrappedClass(self, class_name=None, *a, **ad):
        if class_name == None:
            class_name = self.__class__.__name__
        return self.factory_lo.getClass(class_name)

    def _getLo(self):
        return self.wrapped

    def _hasattr(self, instance, name):
        try:
            FrameworkBase.__getattribute__(instance, name)
            return True
        except AttributeError:
            return False
    # TODO: Review recursive conditions

    def __getattribute__(self, name):
        if name in ['_hasattr']:  # chicken-egg solver
            return FrameworkBase.__getattribute__(self, name)
        elif self._hasattr(self, '_%s_safe' % name):
            function_safe = getattr(self, '_%s_safe' % name)
            function = FrameworkBase.__getattribute__(self, name)
            return SafeCheckWrapper(function, function_safe)
        else:
            return FrameworkBase.__getattribute__(self, name)

    def __getattr__(self, name):
        # chicken-egg solver (when wrapped is not declared)
        if name in ['wrapped']:
            return FrameworkBase.__getattribute__(self, name)
        if hasattr(self.wrapped, name):
            loattr = object.__getattribute__(self.wrapped, name)
            if callable(loattr):
                return LoAttrWrapper(loattr)
            else:
                return loattr
        else:
            return self.__getattribute__(name)

    def __wrapped_lo__(self):
        return self._getLo()


class LoAttrWrapper(object):

    def __init__(self, wrapped):
        self.wrapped = wrapped

    def __call__(self, *a, **ad):
        args = [unwrapLo(arg) for arg in a]
        kwargs = dict((name, unwrapLo(value)) for name, value in ad.items())
        return self.wrapped(*args, **kwargs)

    def __getattr__(self, name):
        return getattr(self.wrapped, name)

    def __repr__(self):
        return repr(self.wrapped)

    def __str__(self):
        return str(self.wrapped)


class HiAutoBase(HiBase):

    def __post_init__(self):
        self.wrapped = self._getWrappedClass()(
            context_lo=unwrapLo(self.context.context_lo))


def unwrapArgsKwargs(a, ad):
    args = [unwrapLo(arg) for arg in a]
    kwargs = dict((name, unwrapLo(value)) for name, value in ad.items())
    return args, kwargs


def unwrap_decorator(method):
    def methodWrapper(self, *a, **ad):
        args, kwargs = unwrapArgsKwargs(a, ad)
        return method(self, *args, **kwargs)
    return methodWrapper
