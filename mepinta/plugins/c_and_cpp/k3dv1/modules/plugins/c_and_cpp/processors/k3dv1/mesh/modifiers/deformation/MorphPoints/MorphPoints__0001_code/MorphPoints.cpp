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
        Code based on the MorphPoints plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/SimpleDeformationModifierBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>
#include <mepintasdk/cpp/TypedPropertiesCollector.h>
#include <mepintasdk/cpp/TypedCollectorManager.h>


//Included Data Types
#include <data_types/mepinta/functum/functum.h>
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/c/builtin/double/double.h>

#include <boost/scoped_ptr.hpp>
#include <vector>

class MorphPoints:
  public k3d::MPExtension::plugins::processors::mesh::SimpleDeformationModifierBase
{
private:
  virtual int deformMesh(const k3d::mesh::points_t& InputPoints, const k3d::mesh::selection_t& PointSelection, k3d::mesh::points_t& OutputPoints){


    //Collect meshes
    INPUT(k3d::mesh*,target,args); TypedPropertiesCollector<k3d::mesh*> targets(args);
    targets.properties.push_back(target);

    //Collect multipliers
    INPUT(double,target_amount,args); TypedPropertiesCollector<double> amounts(args);
    amounts.properties.push_back(target_amount);

    //Need to declare the collector now to get the correct current index
    TypedCollectorManager collector_manager(args);
    collector_manager.appendCollector(&targets);
    collector_manager.appendCollector(&amounts);

    //Declare outputs
    OUTPUT_RENAME(k3d::mesh*,out_mesh,args,mesh);

    OutputPoints = InputPoints;

    //All properties exists, we can collect targets and amounts
    collector_manager.collectProperties();

    if(targets.properties.size() != amounts.properties.size())
    {
      log_error("Mismatch in number of morph inputs and amounts.\n");
      return EXIT_NORMAL;
    }

    const k3d::uint_t targets_begin = 0;
    const k3d::uint_t targets_end = targets_begin + targets.properties.size();

    for(k3d::uint_t target_index = targets_begin; target_index != targets_end; ++target_index)
    {
        const k3d::double_t amount = amounts.properties[target_index];
        if(amount != 0.0)
        {
          const k3d::mesh::points_t& target_points = *targets.properties[target_index]->points.get();

          const k3d::uint_t point_begin = 0;
          const k3d::uint_t point_end = point_begin + std::min(OutputPoints.size(), target_points.size());
          for(k3d::uint_t point = point_begin; point != point_end; ++point){
            OutputPoints[point] += PointSelection[point] * amount * (target_points[point] - InputPoints[point]);
          }
       }
    }
    return EXIT_NORMAL;
  }
};

EXPORT_METHOD(MorphPoints,demuxMeshSignal);
EXPORT_METHOD(MorphPoints,deformMesh);
