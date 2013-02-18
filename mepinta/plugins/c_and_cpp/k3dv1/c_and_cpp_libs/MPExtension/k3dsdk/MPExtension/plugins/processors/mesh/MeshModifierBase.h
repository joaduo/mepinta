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

#ifndef MESHMODIFIER_H_
#define MESHMODIFIER_H_

#include <k3dsdk/MPExtension/plugins/processors/base/ProcessorBase.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/signal/MeshSignalDemuxer.h>
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
  class MeshModifierBase:
    public k3d::MPExtension::plugins::processors::base::ProcessorBase
  {
  public:
    //Unpacks args when creating vertices, edges and faces
    int demuxMeshSignal_unpackAndRun(){
      //Inputs
      INPUT_RENAME(k3d::mesh*,in_mesh,args,mesh);
      k3d::bool_t in_mesh_changed = previousPropChanged();
      INPUT_RENAME(functum_st*,create_mesh,args,createMesh);
      k3d::bool_t create_mesh_changed = previousPropChanged();
      INPUT_RENAME(functum_st*,update_mesh,args,updateMesh);
      k3d::bool_t update_mesh_changed = previousPropChanged();

      //If the mesh changed its topology or one fo the createMesh paramaters changed
      if( create_mesh_changed or
          (in_mesh_changed and topology_changed == MeshSignalDemuxer().demuxSignal(*in_mesh))
        ){
        log_debug("Calling createMesh and updateMesh.\n");
        return callFunctum(create_mesh) | callFunctum(update_mesh);
      }
      //The mesh changed only its geometry or one of the updateMesh paramaters changed
      else if(in_mesh_changed or update_mesh_changed){
        log_debug("Calling updateMesh.\n");
        return callFunctum(update_mesh);
      }
      //Nothing happened
      return EXIT_NORMAL;
    }

    //Unpacks args when calling createMesh function
    int createMesh_unpackAndRun(){
      INPUT_RENAME(k3d::mesh*,in_mesh,args,mesh);
      OUTPUT_RENAME(k3d::mesh*,out_mesh,args,mesh);

      return createMesh(*in_mesh, *out_mesh);
    }

    //Unpacks args when calling createMesh function
    int updateMesh_unpackAndRun(){
      INPUT_RENAME(k3d::mesh*,in_mesh,args,mesh);
      OUTPUT_RENAME(k3d::mesh*,out_mesh,args,mesh);

      return updateMesh(*in_mesh, *out_mesh);
    }

  private:
    ///Recreating the mesh topology
    virtual int createMesh(k3d::mesh& Input, k3d::mesh& Output ) = 0;
    ///Updating the mesh geometry
    virtual int updateMesh(k3d::mesh& Input, k3d::mesh& Output ) = 0;
  };
}
}
}
}
}

#endif /* MESHMODIFIER_H_ */
