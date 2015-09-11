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
from mepinta.pipeline.hi.pipeline_data.data_model import Pipeline
from mepinta.pipelineview.graph.GraphManager import GraphManager
from mepinta.plugins_manager.PluginsManager import PluginsManager
from mepinta.pipelineview.graph.GraphTopologyManager import GraphTopologyManager
from mepinta.pipelineview.graph.data_model import Graph
from mepinta.testing.plugins_testing.base import ModuleAutoTesterBase
from mepinta.testing.plugins_testing.graphviz.PipelineGraphvizTranslator import PipelineGraphvizTranslator
from mepinta_devtools.ide_projects.FileManager import FileManager
from common.shellcmds.CommandRunner import CommandRunner
import os


class PluginManifestAutoTester(ModuleAutoTesterBase):

    def __init__(self, context=None):
        ModuleAutoTesterBase.__init__(self, context)

    def __createNode(self, plugin_manifest):
        graph = Graph(Pipeline(context=self.context))
        # pline.grow()
        graph.pline.startNewTopology()
        plinmngr = PluginsManager(context=self.context)
        plugin_package, minor_version = self._getPackageAndMinorVersion(
            plugin_manifest)
        processor_metadata = plinmngr.loadProcessor(
            plugin_package, minor_version)
        gm = GraphManager(context=self.context)
        node = gm.createNode(graph, processor_metadata)
        self.logPline(graph.pline)
        return graph.pline, node

    def logPline(self, pline):
        self.log.debug(pline.all_properties)
        self.log.debug(pline.getTopology())

    def __getPline(self, plugin_manifest_class):
        plugin_manifest = plugin_manifest_class(self.context)
        pline, _ = self.__createNode(plugin_manifest)
        return pline

    def visualizeXdot(self, plugin_manifest_class):
        pline = self.__getPline(plugin_manifest_class)
        graphviz_translator = PipelineGraphvizTranslator(self.context)
        graphviz_str = graphviz_translator.translate(pline)
        path = './pipeline.dot'
        FileManager(self.context).saveTextFile(
            path, graphviz_str, overwrite=True)
        CommandRunner(self.context).run('xdot %s' % path)
        os.remove(path)

    def test(self, plugin_manifest_class, gui=True):
        pline = self.__getPline(plugin_manifest_class)
        if gui:
            # import here to avoid unnecessary memory use and delays
            from mepinta.testing.plugins_testing.nodebox.NodeBoxSimplePipelineOutput import NodeBoxSimplePipelineOutput
            NodeBoxSimplePipelineOutput(pline, 600, 600).run()

if __name__ == "__main__":
    #import ftest
    pass
