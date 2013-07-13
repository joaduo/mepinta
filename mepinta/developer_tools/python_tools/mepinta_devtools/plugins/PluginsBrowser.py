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
import pkgutil
from mepinta.plugins_manifest import PluginManifestBase

class PluginsBrowser(FrameworkBase):
  def getAllManifests(self, plugins_package):
    manifests = []  # Collected manifests
    for _, modname, ispkg in pkgutil.iter_modules(plugins_package.__path__, "%s." % plugins_package.__name__):
      if modname.split('.')[-1] != 'base':
        if ispkg:  # Its a package, then get all the subpackages/submodules manifests
          sub_plugins_package = __import__(modname, fromlist='dummy')
          manifests += self.getAllManifests(sub_plugins_package)
        else:  # Its a module
          if self.context.minor_version_separator in modname:  # Has the '__' separator, probably its a plugin.
            plugin_module = __import__(modname, fromlist='dummy')
            if hasattr(plugin_module, 'manifest'):  # Has the manifest declared
              manifest = plugin_module.manifest
              if issubclass(manifest, PluginManifestBase):  # The manifest is inheriting from the correct class
                manifests.append(manifest)
              else:  # Inheriting from incorrect class.
                self.log.warning('Manifest %r does not inherit from %r. Ignoring it.' % (manifest, PluginManifestBase))
            elif hasattr(plugin_module, 'data_type_description'):
              self.log.warning('Should migrate %s to correct manifest.' % modname)
            else:  # There is no manifest in the module.
              self.log.warning('Module %r has no manifest' % modname)
          else:  # The module hasn't the '__' separator.
            self.log.warning('Ignored module %r' % modname)
    return manifests

#def testModule():
#  from getDefaultContext import getDefaultContext
#  context = getDefaultContext()
#  psb = PluginsBrowser(context)
##  import plugins.c_and_cpp.processors.k3dv1 as k3dv1
#  import plugins.c_and_cpp.processors as k3dv1
#  for manifest in psb.getAllManifests(k3dv1):
#    context.log(manifest.__name__)
#
#
#if __name__ == "__main__":
#  testModule()
