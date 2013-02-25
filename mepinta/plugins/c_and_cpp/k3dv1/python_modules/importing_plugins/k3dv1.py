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

from importing_plugins.base import createPackageImport, importDataTypes,\
  importProcessors

def import_data_types():
  #  k3d_data_types ="""k3dv1_Bitmap
  #k3dv1_Color
  #k3dv1_Material
  #k3dv1_Matrix4
  #k3dv1_Mesh
  #k3dv1_MeshSelection
  #k3dv1_Points
  #k3dv1_Polyhedron
  #k3dv1_Primitive"""
  eclipse_root = "/home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/k3dv1/DataTypes"
  k3d_data_types= {
                    "k3dv1": "bitmap color imaterial matrix4 mesh".split(),
                    "k3dv1.selection" : "set".split(),
                   }
  data_type_imports = [(k3d_data_types,eclipse_root)]
  importDataTypes(data_type_imports)

def import_processors():
  #  k3d_processors= { "k3dv1.Matrix4.modifiers" : ["inverse"],
  #                    "k3dv1.Mesh.input" : ["K3DMeshReader"],
  #                    "k3dv1.Mesh.modifiers" : ["FlipOrientation","MakeSDS","DeformationExpression", "extrude_faces", "QSlim","select_face_by_number"],
  #                    "k3dv1.Mesh.modifiers.deformation" : ["DeformationExpression","MorphPoints","TransformPoints"],
  #                    "k3dv1.Mesh.generators" : ["cube","sphere",],
  #                    "k3dv1.Mesh.output" : ["mesh_writer"],
  #                    "k3dv1.Mesh.selection" : ["SelectPointsExpression"],
  #                    "k3dv1.Mesh.output" : ["SimpleOpenGLOutput"],
  #                    "k3dv1.Bitmap.generators" : ["bitmap_checker", "blank_bitmap"]}
  eclipse_root = "/home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/k3dv1"
  k3d_processors= {"k3dv1.mesh.generators.polyhedron":
                   "PolyCone  PolyCube  PolyCylinder  PolySphere  PolyTorus".split(),
                    #"k3dv1.Mesh.modifiers.deformation" : ["DeformationTemporalExpression"],
                    #"k3dv1.Mesh.output" : ["OgreRenderOutput"],
                   }  
  processors_imports = [(k3d_processors,eclipse_root)]
  importProcessors(processors_imports)

if __name__ == "__main__":
  import_data_types()
#  import_processors()
