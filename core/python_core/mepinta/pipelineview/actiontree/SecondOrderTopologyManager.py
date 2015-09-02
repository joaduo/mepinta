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
'''
Created on Sep 17, 2011

@author: jduo
'''
from mepinta.abstract.FrameworkBase import FrameworkBase
from mepinta.pipeline.lo.pipeline_data.data_model import Pipeline
from copy import deepcopy, copy
from mepinta.pipeline.hi.topology_manager.TopologyManager import TopologyManager

#
# Crear un 2pline
# agregarle un nodo
# cada modificador debe
  #"copiar" el pline
    # cambiarle el id
    # borrarle el primary y secondary changed
# if processor tiene inputs.pline y outputs.pline
# Me puedo mover en el árbol de 2pline
  # Diciendo el id?
  # Diciendo los pasos relativos a mi posición?
  # No importa ambos valen
# Primero implementar el movimiento lineal
  # dar los nodos por los que me quiero mover
  # en cada nodo sumar changed_ppgation al changed_track
    # siempre que nos movamos hacia atrás en una rama
# cuando evaluamos un nodo de 1pline
   # lo sacamos de changed_track
 # Luego el movimiento dentro de un árbol

# TODO: move this class to lower_level?


class PipelineCopier(object):

    ''' 
      First Order Pipeline Copier. 
        Needed when when copying from one node to the other on the Second Order Pipeline.
      We put this in a class, since we don't know how this will be handled later 
    '''

    def copyPline(self, pline):
        new_pline = pline.copy(Pipeline(init=False))
        return new_pline


class Pipeline2ndOrderManager(FrameworkBase):

    '''
      Using a pline for handling another pline.
        This way we get a very smart undo/redo tool.
        Also we reuse lot of code
      The restriction of this second order pline, is that it can grow as a tree.
        It can't be any kind of graph, because of the nature of data beneath.
    '''

    def __post_init__(self, *a, **ad):
        self.pline_copier = PipelineCopier()
        self.working_node = None
        # A 1st order (aka:"common") pline manager wrapped to manage the 2nd
        # order pline
        self.wrapped_pline_mnger = TopologyManager(context=self.context)

    def appendNodeToBranch(self, pline_2order, processor_name, processor_version=None):
        # processor_name should have only one dot
        # We append FirstOrderPipeline_v_0_0_1
        # connect inputs.pline and outputs.pline
        node = None
        return node

    def evalNode(self, pline_2order, node):
        # The default property is always the 1st order pline
        pline_1order = None
        return pline_1order

    def copyPline(self, pline_2order):
        # before copying we need to propagate changes!!
        pass
#  def undo_redo_action(self, pline_2order, nodes_path):
#    pline = None
#    return pline

    def addArbitraryNode(self, pline_2order, in_node, out_node):
        #"Massive" node re-evaluation? No needed
        pline = None
        return pline
