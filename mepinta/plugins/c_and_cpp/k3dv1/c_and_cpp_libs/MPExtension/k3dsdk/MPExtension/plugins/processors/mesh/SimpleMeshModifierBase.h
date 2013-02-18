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

#ifndef SIMPLEMESHMODIFIER_H_
#define SIMPLEMESHMODIFIER_H_

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
  class SimpleMeshModifierBase:
    public k3d::MPExtension::plugins::processors::base::ProcessorBase
  {
  public:

    //Unpacks args when calling createMesh function
    int createMesh_unpackAndRun(){
      INPUT_RENAME(k3d::mesh*,in_mesh,args,mesh);
      OUTPUT_RENAME(k3d::mesh*,out_mesh,args,mesh);

      return createMesh(*in_mesh, *out_mesh);
    }

  private:
    ///Recreating the mesh topology
    virtual int createMesh(k3d::mesh& Input, k3d::mesh& Output ) = 0;
  };
}
}
}
}
}

#endif /* SIMPLEMESHMODIFIER_H_ */
