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
from mepinta.plugins_manager.data_model import DataTypeMetadata
from common.path import joinPath
from mepinta.plugins_manifest import ProcessorManifestBase
from mepinta.plugins_manager.plugins_manager_detail.PluginImportError import PluginImportError

class MetadataWrapperBase(FrameworkBase):
  def __post_init__(self, meta_data):
    self._meta_data = meta_data
    self.refresh()

  def refresh(self):
    self._module = None
    self._package = None
    self._manifest = None

  def _hasAttr(self, name):
    return name in dir(self)

  def __getattr__(self, name):
    if name.startswith('_') or self._hasAttr(name):
      return  FrameworkBase.__getattribute__(self, name)
    else:
      #self.log.d('Looking up attr name=%r in metadata' % name)
      return getattr(self._meta_data, name)

  def _getImplemetationPath(self, package, build_name):
    #Get base path from the deployment
    base_path = self.context.deployment_config.deployment_path
    base_path = joinPath(base_path, 'build', 'plugins_build')
    #Get path list from package namespace
    path_list = package.__name__.split('.')
    path_list = path_list[path_list.index(self.context.backend_name):]
    plugin_path = joinPath(base_path, path_list)
    library_path = joinPath(plugin_path, 'lib%s.so' % build_name)
    return library_path

  @property
  def library_path(self):
    if self.context.backend_name == 'python':
      #On python the plugin module is the plugin itself
      library_path = self.module
    else: #then its shedskin. We still need to load the shared library
      library_path = self._getImplemetationPath(self.package, self.build_name)
    return library_path

  @property
  def module(self):
      if not self._module:
        self._module = self._pkg_mngr.getRevisionModule(self.name,
                                                        self.build_name)
      module = reload(self._module)
      return module

  @property
  def package(self):
    if not self._package:
      self._package = self._pkg_mngr.python2x3xImport(self.name)
    return self._package

  def runPreLoad(self):
    return self._runPrePostLoad('preLoadPlugin')

  def runPostUnload(self):
    return self._runPrePostLoad('postUnloadPlugin')

  def _runPrePostLoad(self, func_name):
    if hasattr(self.manifest, 'getPreLoadPostUnload'):
      functions = self.manifest.getPreLoadPostUnload()
    else:
      functions = {}
    for pkg_name in sorted(functions.keys()):
      functions[pkg_name][func_name](self.context, self)

  def getManifest(self):
    if not self._manifest:
      module = self.module
      if hasattr(module, 'manifest'):
        manifest = module.manifest
        manifest_type = self.getManifestType()
        if not issubclass(manifest, manifest_type):
          msg = ('The manifest is not a subclass of %r. Instead it is %r' %
                 (manifest_type, manifest))
          raise PluginImportError(msg)
      else:
        raise PluginImportError('There is no definition on the module: %r.' %
                                  (module))
      self._manifest = manifest(self.context)
    return self._manifest

  manifest = property(getManifest)


def smokeTestModule():
  from mepinta.context.MepintaContext import MepintaContext
  meta_data = DataTypeMetadata(name='A', build_name='A__001', version=1, package=None)
  context = MepintaContext('python')
  wrapper = MetadataWrapperBase(context, meta_data=meta_data)
  log = context.log.d
  log(wrapper.name)
  log(wrapper.build_name)
  for name in ['foo', '_foo']:
    exception = False
    try:
      log(getattr(wrapper, name))
    except AttributeError as e:
      exception = True
      log(e)
    finally:
      assert exception
  wrapper.method = 'bar'


if __name__ == "__main__":
  smokeTestModule()
