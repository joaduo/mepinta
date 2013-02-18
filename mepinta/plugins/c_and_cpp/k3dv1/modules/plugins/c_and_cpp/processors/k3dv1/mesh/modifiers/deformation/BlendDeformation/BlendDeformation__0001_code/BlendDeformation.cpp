/* Mepinta
  Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

  K-3D
  Copyright (c) 1995-2006, Timothy M. Shead

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
  along with Mepinta. If not, see <http:www.gnu.org/licenses/>. */

/** \file
        Code based on the BlendDeformation plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/SimpleDeformationModifierBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/mepinta/functum/functum.h>
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/c/builtin/double/double.h>


class BlendDeformation:
  public k3d::MPExtension::plugins::processors::mesh::SimpleDeformationModifierBase
{
private:
  virtual int deformMesh(const k3d::mesh::points_t& InputPoints, const k3d::mesh::selection_t& PointSelection, k3d::mesh::points_t& OutputPoints){
    //Declare Inputs
    INPUT(k3d::double_t,blend_amount,args);
    INPUT(k3d::mesh*,original_mesh,args);

    const k3d::mesh::points_t& OriginalInputPoints = *original_mesh->points.get();


    //Copy mesh
    if(blend_amount ==  1.0){ //complete blending, directly copying
      OutputPoints = InputPoints;
    }
    else if(blend_amount == 0.0 && OutputPoints.size() == OriginalInputPoints.size()){ //there will be a blending if amount != 0.0 between original mesh and new mesh
      OutputPoints = OriginalInputPoints;
    }
    else{ //There is a blending to do
      OutputPoints = InputPoints;
      const k3d::uint_t point_begin = 0;
      const k3d::uint_t point_end = point_begin + std::min(InputPoints.size(),OriginalInputPoints.size());
      for(k3d::uint_t point = point_begin; point != point_end; ++point){
        const double selection_weight = PointSelection[point];
        if(selection_weight != 0.0){
          k3d::point3 original_point = OriginalInputPoints[point];
          OutputPoints[point] = original_point + selection_weight * blend_amount * (InputPoints[point] - original_point);
        }
      }
    }

    return EXIT_NORMAL;
  }
};

/*

//Give a brief explanation for your function property.
EXPORTED_SYMBOL
int demuxMeshSignal(MP_args* args){
  //Declare Inputs
  INPUT(MP_functum*,deformMesh,args);
  INPUT(k3d::mesh*,mesh,args);

  //Declare Outputs
  //OUTPUT(k3d::mesh*,mesh,args);


  log_info("Printing from demuxMeshSignal.\n");

  return EXIT_NORMAL;
}

//Give a brief explanation for your function property.
EXPORTED_SYMBOL
int deformMesh(MP_args* args){
  //Declare Inputs
  INPUT(k3d::double_t,blend_amount,args);
  INPUT(k3d::mesh*,original_mesh,args);

  //Declare Outputs
  //OUTPUT(k3d::mesh*,mesh,args);


  log_info("Printing from deformMesh.\n");

  return EXIT_NORMAL;
}

*/

EXPORT_METHOD(BlendDeformation,demuxMeshSignal);
EXPORT_METHOD(BlendDeformation,deformMesh);
