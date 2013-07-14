//Mepinta
//Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar
//
// K-3D
// Copyright (c) 1995-2011, Timothy M. Shead
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

#ifndef SIMPLEDEFORMATIONMODIFIER_H_
#define SIMPLEDEFORMATIONMODIFIER_H_

#include <k3dsdk/MPExtension/plugins/processors/base/ProcessorBase.h>
#include <k3dsdk/MPExtension/MPExtension.h>
#include <mepintasdk/sdk.h>
#include <k3dsdk/mesh.h>
#include <k3dsdk/imaterial.h>
#include <data_types/mepinta/functum/functum.h>

namespace k3d {
namespace MPExtension {
namespace plugins {
namespace processors {
namespace mesh {
  class SimpleDeformationModifierBase:
    public k3d::MPExtension::plugins::processors::base::ProcessorBase
  {
  public:
    //Unpacks args when creating vertices, edges and faces
    int demuxMeshSignal_unpackAndRun(){
      //Inputs
      INPUT_RENAME(k3d::mesh*,in_mesh,args,mesh);
      int in_mesh_changed = MP_has_changed(args,INPUT_PROPS,MP_previous_prop_index(args));
      INPUT_RENAME(functum_st*,deform_mesh,args,deformMesh);
      int deform_mesh_changed = MP_has_changed(args,INPUT_PROPS,MP_previous_prop_index(args));
      //Outputs
      OUTPUT_RENAME(k3d::mesh*,out_mesh,args,mesh);
      k3d::mesh& Input = *in_mesh;
      k3d::mesh& Output = *out_mesh;

      //Sync mesh and call functum
      if(in_mesh_changed){
        log_debug("Input mesh has changed. Demuxing its signals.\n");
        k3d::UpdateTopologyGeometry update_reset_mesh;
        update_reset_mesh.update_reset_output(*in_mesh,*out_mesh);
      }

      //Do we need to call the functum?
      if(deform_mesh_changed or in_mesh_changed){
        log_debug("Calling deform_mesh functum.\n");
        ASSERT_RETURN(Input.points->size() == Output.points->size(),EXIT_FAILURE);
        ASSERT_RETURN(Output.point_selection, EXIT_FAILURE);
        ASSERT_RETURN(Output.point_selection->size() == Output.points->size(), EXIT_FAILURE);
        return MP_call_functum(deform_mesh,NULL);
      }

      return EXIT_NORMAL;
    }

    //Unpacks args when calling deformMesh function
    int deformMesh_unpackAndRun(){
      INPUT_RENAME(k3d::mesh*,in_mesh,args,mesh);
      OUTPUT_RENAME(k3d::mesh*,out_mesh,args,mesh);
      //Names/aliases
      const k3d::mesh::points_t& InputPoints = *in_mesh->points.get();
      k3d::mesh::points_t& OutputPoints = out_mesh->points.writable();
      const k3d::mesh::selection_t& PointSelection = *out_mesh->point_selection;

      return deformMesh(InputPoints, PointSelection, OutputPoints);
    }

  private:
    /// Implement this method in derived classes and deform the output mesh using its input points and selection.
    virtual int deformMesh(const k3d::mesh::points_t& InputPoints, const k3d::mesh::selection_t& PointSelection, k3d::mesh::points_t& OutputPoints) = 0;
  };
}
}
}
}
}

#endif /* SIMPLEDEFORMATIONMODIFIER_H_ */
