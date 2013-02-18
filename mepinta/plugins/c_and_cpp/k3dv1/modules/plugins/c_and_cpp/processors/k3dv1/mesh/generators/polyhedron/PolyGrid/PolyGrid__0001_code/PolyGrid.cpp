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
        Code based on the PolyGrid plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/MeshSourceBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/k3dv1/imaterial/imaterial.h>
#include <data_types/c/builtin/int/int.h>
#include <data_types/c/builtin/double/double.h>

#include <k3dsdk/polyhedron.h>
#include <boost/scoped_ptr.hpp>

namespace k3d{
  //Generic enum orientation_t
  typedef enum
  {
    NX=0,
    PX=1,
    NY=2,
    PY=3,
    NZ=4,
    PZ=5
  } orientation_t;
}

class PolyGrid:
  public k3d::MPExtension::plugins::processors::mesh::MeshSourceBase
{
private:
    //Called when creating vertices, edges and faces
    int updateMeshTopology(k3d::mesh& Output, k3d::imaterial* material){
      //Declare Inputs
      INPUT(k3d::int32_t,columns,args);
      INPUT(k3d::int32_t,rows,args);

      Output = k3d::mesh();
      boost::scoped_ptr<k3d::polyhedron::primitive> polyhedron(k3d::polyhedron::create(Output));
      polyhedron->shell_types.push_back(k3d::polyhedron::POLYGONS);
      k3d::polyhedron::add_grid(Output, *polyhedron, 0, rows, columns, material);

      return EXIT_NORMAL;
    }

    int updateMeshGeometry(k3d::mesh& Output){
      //Declare Inputs
      INPUT(k3d::int32_t,columns,args);
      INPUT(k3d::double_t,height,args);
      INPUT(k3d::orientation_t,orientation,args);
      INPUT(k3d::int32_t,rows,args);
      INPUT(k3d::double_t,width,args);

      const k3d::int32_t point_rows = rows + 1;
      const k3d::int32_t point_columns = columns + 1;
      k3d::vector3 x, y;
      switch(orientation)
      {
        case k3d::PX:
                x = k3d::vector3(0, -width, 0);
                y = k3d::vector3(0, 0, height);
                break;
        case k3d::NX:
                x = k3d::vector3(0, width, 0);
                y = k3d::vector3(0, 0, height);
                break;
        case k3d::NY:
                x = k3d::vector3(-width, 0, 0);
                y = k3d::vector3(0, 0, height);
                break;
        case k3d::PY:
                x = k3d::vector3(width, 0, 0);
                y = k3d::vector3(0, 0, height);
                break;
        case k3d::PZ:
                x = k3d::vector3(-width, 0, 0);
                y = k3d::vector3(0, height, 0);
                break;
        case k3d::NZ:
                x = k3d::vector3(width, 0, 0);
                y = k3d::vector3(0, height, 0);
                break;
      }

      k3d::mesh::points_t::iterator point = const_cast<k3d::mesh::points_t&>(*Output.points).begin();
      for(k3d::int32_t row = 0; row != point_rows; ++row)
      {
          const k3d::double_t row_percent = 0.5 - k3d::ratio(row, point_rows-1);

          for(k3d::int32_t column = 0; column != point_columns; ++column)
          {
                  const k3d::double_t column_percent = k3d::ratio(column, point_columns-1) - 0.5;

                  *point++ = k3d::to_point((column_percent * x) + (row_percent * y));
          }
      }
      return EXIT_NORMAL;
    }
};

EXPORT_METHOD(PolyGrid,updateMeshTopology);
EXPORT_METHOD(PolyGrid,updateMeshGeometry);
