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

#ifndef MESHSOURCE_H_
#define MESHSOURCE_H_

#include <k3dsdk/MPExtension/plugins/processors/base/ProcessorBase.h>
#include <mepintasdk/sdk.h>
#include <k3dsdk/mesh.h>
#include <k3dsdk/imaterial.h>

namespace k3d {
namespace MPExtension {
namespace plugins {
namespace processors {
namespace mesh {
  class MeshSourceBase:
    public k3d::MPExtension::plugins::processors::base::ProcessorBase
  {
  public:    
    //Unpacks args when creating vertices, edges and faces
    int updateMeshTopology_unpackAndRun(){
      OUTPUT(k3d::mesh*,mesh,args);
      INPUT(k3d::imaterial*,material,args);
      return updateMeshTopology(*mesh, material);
    }

    //Unpacks when updating the vertices positions
    int updateMeshGeometry_unpackAndRun(){
      OUTPUT(k3d::mesh*,mesh,args);
      return updateMeshGeometry(*mesh);
    }

  private:
    //Called when creating vertices, edges and faces
    virtual int updateMeshTopology(k3d::mesh& Output, k3d::imaterial* material) = 0;
    //Called when updating the vertices positions
    virtual int updateMeshGeometry(k3d::mesh& Output) = 0;
  };
}
}
}
}
}

#endif /* MESHSOURCE_H_ */
