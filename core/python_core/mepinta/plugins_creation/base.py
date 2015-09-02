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
import os
from mepinta.plugins_creation.templates.base import DictionaryBasedTranslator, \
    TemplateTranslatorBase
from common.path import joinPath


class PluginCreatorBase(FrameworkBase):

    def _pathExists(self, path, package=False):
        if os.access(path, os.W_OK):
            if package and not os.access("%s/__init__.py" % path, os.W_OK):
                self.log.warning("The package path %r exist but there is no %r file." % (
                    path, "%s/__init__.py" % path))
            self.log.debug("Exists: %r" % path)
            return True
        self.log.debug("Doesn't exist: %r" % path)
        return False

    def _saveFile(self, path, content, overwrite):
        '''
          Once the content is generated, save the file.
          overwrite=True, will overwrite the file if exists.
        '''
        self.log('Writing %r with overwrite:%s' % (path, overwrite))
        if not self._pathExists(path) or overwrite:
            target_file = open(path, 'w')
            target_file.write(content)
            target_file.close()

    def _getOverwritePolicy(self, template):
        if isinstance(template, TemplateTranslatorBase):
            return template.getOverwritePolicy()
        else:
            return False


class GenericProjectCreatorBase(PluginCreatorBase):

    def _getTargetPath(self, eclipse_root):
        '''Get the path of the created project.'''
        raise NotImplementedError('Implement in children!')

    def _createProjectDir(self, target_root):
        '''Create the project's new directory (and src).'''
        path = joinPath(target_root, 'src')  # ,'properties')
        if not self._pathExists(path):
            os.makedirs(path)

    def _updateTranslationDict(self, translation_dict):
        return translation_dict

    def create(self, projects_root, translation_dict={}, overwrite=False, **kwargs):
        '''
          Public function to create a project from a given plugin manifest.
          translation_dict, add user based translation for every template
          overwrite=True, will overwrite the file if exists.
        '''
        target_root = self._getTargetPath(projects_root, **kwargs)
#    translation_dict.update(dict(projectDirectory=target_root, pluginName=plugin_manifest.__class__.__name__))
        self._createProjectDir(target_root)
        templates = self._getTemplates(target_root, **kwargs)
        self._updateTranslationDict(translation_dict)
        for template, target_path in templates.items():
            content = DictionaryBasedTranslator(
                self.context, template=template, translation_dict=translation_dict).getContent()
            self._saveFile(
                target_path, content, overwrite | self._getOverwritePolicy(template))

# TODO: add support for PluginStorageConfig and create
# %sName__%sMinoversion paths


class ProjectCreatorBase(GenericProjectCreatorBase):  # TODO: rename PluginProjectCreatorBase

    def _getTargetPath(self, eclipse_root, plugin_manifest=None):
        '''Get the path of the created project.'''
        return joinPath(eclipse_root, plugin_manifest.getName())

    def create(self, plugin_manifest, projects_root, translation_dict={}, overwrite=False):
        '''
          Public function to create a project from a given plugin manifest.
          translation_dict, add user based translation for every template
          overwrite=True, will overwrite the file if exists.
        '''
        target_root = self._getTargetPath(
            projects_root, plugin_manifest=plugin_manifest)
        translation_dict.update(
            dict(projectDirectory=target_root, pluginName=plugin_manifest.__class__.__name__))
        GenericProjectCreatorBase.create(
            self, projects_root, translation_dict, overwrite, plugin_manifest=plugin_manifest)
