//Mepinta
//Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar
//
// K-3D
// Copyright (c) 1995-2006, Timothy M. Shead
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

/** \file
        Code based on the TransformPoints plugin of the K-3D project
*/

#include <mepintasdk/sdk.h>
#include "k3dv1_Mesh.h"
#include "k3dv1_Matrix4.h"

//TODO: add selection weight
EXPORTED_SYMBOL
int on_deform_mesh(MP_args_p args){
  //Declare inputs
  INPUT(k3dv1_Matrix4*,matrix,args);
  //Declare outputs
  OUTPUT(k3dv1_Mesh*,mesh,args);

  k3d::mesh::points_t& OutputPoints = mesh->points.writable();

  const k3d::uint_t point_begin = 0;
  const k3d::uint_t point_end = point_begin + OutputPoints.size();
  for(k3d::uint_t point = point_begin; point != point_end; ++point)
  {
      OutputPoints[point] = OutputPoints[point]*(*matrix);
  }

//TODO
//  const k3d::matrix4& transformation = *matrix;
//  k3d::parallel::parallel_for(
//          k3d::parallel::blocked_range<k3d::uint_t>(0, OutputPoints.size(), k3d::parallel::grain_size()),
//          linear_transformation_worker(InputPoints, PointSelection, OutputPoints, transformation));

  return EXIT_NORMAL;
}
