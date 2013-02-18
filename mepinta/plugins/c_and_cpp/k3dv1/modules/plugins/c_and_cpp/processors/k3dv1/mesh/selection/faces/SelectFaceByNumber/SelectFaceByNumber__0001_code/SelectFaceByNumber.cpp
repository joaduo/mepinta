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
        Code based on the SelectFaceByNumber plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/selection/SimpleMeshSelectionModifierBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/c/builtin/int/int.h>

#include <k3dsdk/polyhedron.h>

#include <boost/scoped_ptr.hpp>

class SelectFaceByNumber:
  public k3d::MPExtension::plugins::processors::mesh::selection::SimpleMeshSelectionModifierBase
{
private:
  int updateSelection(k3d::mesh& Input, k3d::mesh& Output ){
    //Declare Inputs
    INPUT(k3d::int32_t,face_index,args);
    INPUT(k3d::int32_t,primitive_number,args);

    if(primitive_number >= Output.primitives.size())
            return EXIT_NORMAL;

    boost::scoped_ptr<k3d::polyhedron::primitive> polyhedron(k3d::polyhedron::validate(Output, Output.primitives[primitive_number]));
    if(!polyhedron)
            return EXIT_NORMAL;

    std::fill(polyhedron->face_selections.begin(), polyhedron->face_selections.end(), 0.0);

    if(face_index < polyhedron->face_selections.size())
      polyhedron->face_selections[face_index] = 1.0;


    return EXIT_NORMAL;
  }
};

EXPORT_METHOD(SelectFaceByNumber,updateSelection);
