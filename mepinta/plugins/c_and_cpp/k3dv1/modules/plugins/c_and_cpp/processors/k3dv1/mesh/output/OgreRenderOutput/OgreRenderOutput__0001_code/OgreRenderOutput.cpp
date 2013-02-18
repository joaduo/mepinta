//Mepinta
//Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar
//
//This file is part of Mepinta.
//
//Mepinta is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//Mepinta is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Mepinta. If not, see <http://www.gnu.org/licenses/>.

#include <mepintasdk/sdk.h>
#include "k3dv1_Mesh.h"
#include <internal_any.h>

#include <k3dsdk/gl.h>
#include <k3dsdk/mesh_painter_gl.h>
#include <k3dsdk/polyhedron.h>
#include <k3dsdk/triangulator.h>

#include <boost/scoped_ptr.hpp>

#include "SampleApp.h"

#include "K3dMeshToOgreMesh.h"

#if 0
int initOpenGLContext(int width, int height){
  //Init SDL
  //Init gl
  return EXIT_SUCCESS;
}
#endif

SampleApp* initOgreContext(int width, int height){
  SampleApp* sample_app = new SampleApp();
  sample_app->setupPublic();
  //Init a whole new window?
  return sample_app;
}

//int convertMeshToOgre(k3d::mesh* mesh){
//  return EXIT_SUCCESS;
//}

EXPORTED_SYMBOL
int renderMesh(MP_args* args){
  //TODO: should be alphabetically?
  //INPUT(char*,node_name,args);
  INPUT(internal_any*,opengl_context,args);
  INPUT(internal_any*,ogre_context,args);
  INPUT(k3dv1_Mesh*,mesh,args);
  INPUT(int,width,args);
  INPUT(int,height,args);
  INPUT(double,position_x,args)
  INPUT(double,position_y,args)
  INPUT(double,position_z,args)

  if(ogre_context->data == NULL)
    ogre_context->data = (void*)initOgreContext(width,height);
  //Init contexts
//  if(opengl_context->data == NULL)
//    opengl_context->data = (void*)

  SampleApp* sample_app = (SampleApp*)ogre_context->data;

  K3dMeshToOgreMesh k3d_to_ogre;
  //Ogre::Mesh* ogre_mesh =
//  if(opengl_context->data == NULL){
//    Ogre::MeshPtr ogre_mesh_ptr = k3d_to_ogre.createOgreMesh("bla");
//    opengl_context->data = (void*)&ogre_mesh_ptr;
//    sample_app->createOgreNode(ogre_mesh_ptr);
//  }
  k3d_to_ogre.convertMesh(*mesh, sample_app->getManualObject("K3dMesh"));
  //sample_app->operationNinja(position_x,position_y,position_z);
  //sample_app->createManualObject();
  sample_app->renderOneFrame();
  //Triangulate and convert to Ogre
  //convertMeshToOgre(mesh);

  //setOgreNode(ogre_mesh);
  //
  //renderOgreFrame(ogre_context);
  return EXIT_NORMAL;
}
