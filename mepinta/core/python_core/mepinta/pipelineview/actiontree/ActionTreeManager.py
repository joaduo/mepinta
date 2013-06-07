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

class ActionTreeManager(object):
  def getTransitionPath(self, tree, to_tree_node, from_tree_node):
    to_path, frm_path = self.__getPathsToCommonNode(tree, to_tree_node, from_tree_node)
    return frm_path + list(reversed(to_path))

  def __getPathsToCommonNode(self, tree, to_tree_node, from_tree_node):
    frm = from_tree_node
    to = to_tree_node
    frm_visited = set()
    to_visited = set()
    frm_path = []
    to_path = []

    #go up to the parents until we reach a common node or the root of the tree
    while frm.parent != None and \
          to.parent != None and \
          frm not in to_visited and \
          to not in frm_visited:
      frm_visited.add(frm)
      to_visited.add(to)
      frm_path.append(frm)
      to_path.append(to)
      frm = frm.parent
      to = to.parent

    if frm.parent == None: #frm_path reached the root
      to = self.__keepGoing(to, to_path, frm_visited)
      del frm_path[frm_path.index(to) + 1:] #Remove path to the root and keep the to node
    elif to.parent == None: #to_path reached the root
      frm = self.__keepGoing(frm, frm_path, to_visited)
      del to_path[to_path.index(frm) + 1:] #Remove path to the root and keep the frm node
    elif to in frm_visited and to in to_visited:
      #equivalent to "if frm in to_visited and frm in frm_visited:"
      #Both reached the same node at the same time.
      to_path.pop() #delete the last node in common with frm_path (means to=frm)
    elif to in frm_visited: #but frm is not in frm_visited
      #to is on fmr_path, but fmr is not in to_path
      del frm_path[frm_path.index(to) + 1:] #remove tail to the root and keep the to node
    elif frm in to_visited: #but to is not in to_visited
      #frm is on to_path, but to is not in frm_path
      del to_path[to_path.index(frm) + 1:] #remove tail to the root and keep the frm node
    return to_path, frm_path

  def __keepGoing(self, node, node_path, visited_set):
    while node.parent != None and node not in visited_set:
      node_path.append(node)
      node = node.parent
    if node.parent == None:
      raise RuntimeError('To and From node shouldn\'t have None as common node')
    return node

  def initTree(self, tree):
    pass
  def appendAction(self, tree, processor):
    pass
  def appendFutureAction(self, tree, tree_node, processor):
    pass
  def setCurrentAction(self, tree, node):
    pass
  def setActionPropValue(self, tree, prop):
    pass

