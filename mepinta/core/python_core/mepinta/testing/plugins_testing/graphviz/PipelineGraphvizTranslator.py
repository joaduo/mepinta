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
from mepinta.pipeline.lo.constants import NULL_UID

class PipelineGraphvizTranslator(FrameworkBase):
  def __getNodesStr(self, pline):
    topo = pline.get_topology()
    nodes_str = ''
    for p_id in topo.properties:
      nodes_str += '  %s [label="%s\\n%s"] \n' % (p_id, p_id, pline.all_properties[p_id])
    return nodes_str

  def __getConnectionsStr(self, pline):
    connections_str = ''
    topo = pline.get_topology()
    dpdencies_iterator = topo.connections.dpdencies.get_ss_iterator()
    p_id_dent, p_id_dency = dpdencies_iterator.next()
    while p_id_dent != NULL_UID:
      connections_str += '  %s -> %s \n' % (p_id_dent, p_id_dency)
      p_id_dent, p_id_dency = dpdencies_iterator.next()
    return connections_str

  def translate(self, pline):
    graphviz_str = 'digraph {\n%s\n%s} ' % (self.__getNodesStr(pline), self.__getConnectionsStr(pline))
    return graphviz_str

  def renderAscii(self, pline):
    pass

def test_module():
  from getDefaultContext import getDefaultContext
  context = getDefaultContext()

if __name__ == "__main__":
  test_module()
