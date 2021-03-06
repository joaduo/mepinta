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
import sys
import os


def joinPath(path, *path_list):
    if isinstance(path, list) or isinstance(path, tuple):
        joint_path = os.path.join(*map(joinPath, path))
    else:
        joint_path = path
    if len(path_list):
        joint_path = os.path.join(joint_path, joinPath(path_list))
    return joint_path


class PythonPathManager(object):

    def __getInitialDict(self):
        paths = {'mepinta': joinPath('core', 'python_core'),
                 'mepinta_devtools': joinPath('developer_tools'),
                 'common': joinPath('libs', 'python', 'python_common'),
                 'pipeline_backend':
                 joinPath(
                     'core', 'pipeline_backend', 'pipeline_backend_python'),
                 }
        return paths

    def appendInitial(self, mepinta_src):
        self.appendMepintaPaths(mepinta_src)
        self.appendPlugins(mepinta_src, 'dummy', 'python')

    def appendMepintaPaths(self, mepinta_src):
        for path in self.__getInitialDict().values():
            self.appendPath(mepinta_src, path)

    def appendPath(self, *args):
        path = joinPath(args)
        if path not in sys.path:
            sys.path.append(path)

    def removePath(self, *args):
        path = joinPath(args)
        if path in sys.path:
            sys.path.remove(path)

    def cleanPlugins(self, mepinta_src):
        # Clean plugins paths
        prefix = joinPath(mepinta_src, 'plugins')
        prefix = os.path.realpath(prefix)
        for path in sys.path:
            if os.path.realpath(path).startswith(prefix):
                sys.path.remove(path)

    def appendPlugins(self, mepinta_src, plugins_set, backend):
        rel_path = joinPath('plugins', backend, plugins_set)
        self.appendPath(mepinta_src, rel_path)

    def removePlugins(self, mepinta_src, plugins_set, backend):
        rel_path = joinPath('plugins', backend, plugins_set)
        self.removePath(mepinta_src, rel_path)


def smokeTestModule():
    from common.log.debugPrint import debugPrint
    PythonPathManager().appendInitial('./')
    import sys
    debugPrint(sys.path)


if __name__ == "__main__":
    smokeTestModule()
