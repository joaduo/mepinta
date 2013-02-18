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
        Code based on the MakeSDS plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/MeshModifierBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/c/builtin/int/int.h>
#include <data_types/mepinta/functum/functum.h>
#include <data_types/k3dv1/mesh/mesh.h>

#include <k3dsdk/polyhedron.h>
#include <boost/scoped_ptr.hpp>

class MakeSDS:
  public k3d::MPExtension::plugins::processors::mesh::MeshModifierBase
{
private:
  ///Recreating the mesh topology
  int createMesh(k3d::mesh& Input, k3d::mesh& Output ){
    //Inputs
    INPUT(k3d::bool_t,interpolate_boundary,args);

    //Copy input into output
    Output=Input;

    //Iterate over the primiteves to convert only the polyhedron into SDS
    for(k3d::mesh::primitives_t::iterator primitive = Output.primitives.begin(); primitive != Output.primitives.end(); ++primitive)
    {
            boost::scoped_ptr<k3d::polyhedron::primitive> polyhedron(k3d::polyhedron::validate(Output, *primitive));
            if(!polyhedron)
                    continue;

            std::fill(polyhedron->shell_types.begin(), polyhedron->shell_types.end(), k3d::polyhedron::CATMULL_CLARK);

            if(interpolate_boundary)
                    polyhedron->constant_attributes.create("interpolateboundary", new k3d::typed_array<k3d::string_t>(polyhedron->shell_types.size(), "interpolateboundary"));
    }
    return EXIT_NORMAL;
  }

  ///Updating the mesh geometry
  int updateMesh(k3d::mesh& Input, k3d::mesh& Output ){
    //This is not used
    return EXIT_NORMAL;
  }

};

EXPORT_METHOD(MakeSDS,demuxMeshSignal);
EXPORT_METHOD(MakeSDS,createMesh);
EXPORT_METHOD(MakeSDS,updateMesh);
