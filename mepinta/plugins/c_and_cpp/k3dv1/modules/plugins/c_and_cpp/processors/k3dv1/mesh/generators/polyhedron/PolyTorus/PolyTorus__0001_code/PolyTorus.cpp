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
        Code based on the PolyTorus plugin of the K-3D project.
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

class PolyTorus:
  public k3d::MPExtension::plugins::processors::mesh::MeshSourceBase
{
private:
  //Called when creating vertices, edges and faces
  inline int updateMeshTopology(k3d::mesh& Output, k3d::imaterial* material){
    //Declare Inputs
    INPUT(k3d::int32_t,u_segments,args);
    INPUT(k3d::int32_t,v_segments,args);

    Output = k3d::mesh();

    boost::scoped_ptr<k3d::polyhedron::primitive> polyhedron(k3d::polyhedron::create(Output));

    polyhedron->shell_types.push_back(k3d::polyhedron::POLYGONS);
    k3d::polyhedron::add_torus(Output, *polyhedron, 0, v_segments, u_segments, material);

    return EXIT_NORMAL;
  }
  //Called when updating the vertices positions
  inline int updateMeshGeometry(k3d::mesh& Output){
    //Declare Inputs
    INPUT(k3d::double_t,major_radius,args);
    INPUT(k3d::double_t,minor_radius,args);
    INPUT(k3d::double_t,u_power,args);
    INPUT(k3d::int32_t,u_segments,args);
    INPUT(k3d::double_t,v_power,args);
    INPUT(k3d::int32_t,v_segments,args);

    const k3d::double_t inv_u_power = u_power ? 1.0 / u_power : 1.0;
    const k3d::double_t inv_v_power = v_power ? 1.0 / v_power : 1.0;

    k3d::mesh::points_t& points = Output.points.writable();

    // Shape the torus points
    for(k3d::int32_t v = 0; v != v_segments; ++v)
    {
            const k3d::double_t phi = k3d::pi_times_2() * k3d::ratio(v, v_segments);
            k3d::double_t minor_x = cos(phi);
            k3d::double_t minor_y = sin(phi);
            minor_x = k3d::sign(minor_x) * std::pow(std::abs(minor_x), inv_v_power);
            minor_y = k3d::sign(minor_y) * std::pow(std::abs(minor_y), inv_v_power);

            const k3d::double_t radius = major_radius - (minor_radius * minor_x);

            for(k3d::int32_t u = 0; u != u_segments; ++u)
            {
                    const k3d::double_t theta = k3d::pi_times_2() * k3d::ratio(u, u_segments);

                    k3d::double_t x = -sin(theta);
                    k3d::double_t y = -cos(theta);
                    k3d::double_t z = minor_radius * minor_y;

                    x = radius * k3d::sign(x) * std::pow(std::abs(x), inv_u_power);
                    y = radius * k3d::sign(y) * std::pow(std::abs(y), inv_u_power);

                    points[v * u_segments + u] = k3d::point3(x, y, z);
            }
    }

    return EXIT_NORMAL;
  }
};

EXPORT_METHOD(PolyTorus,updateMeshTopology);
EXPORT_METHOD(PolyTorus,updateMeshGeometry);
