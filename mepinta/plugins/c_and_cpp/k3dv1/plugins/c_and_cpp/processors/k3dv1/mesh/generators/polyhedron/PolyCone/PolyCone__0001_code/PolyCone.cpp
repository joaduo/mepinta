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
        Code based on the PolyCone plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/MeshSourceBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/k3dv1/imaterial/imaterial.h>
#include <data_types/c/builtin/int/int.h>
#include <data_types/c/builtin/double/double.h>

#include <k3dsdk/imaterial.h>
#include <k3dsdk/polyhedron.h>

#include <boost/scoped_ptr.hpp>

class PolyCone:
  public k3d::MPExtension::plugins::processors::mesh::MeshSourceBase
{
public:
  //Called when creating vertices, edges and faces
  int updateMeshTopology(k3d::mesh& Output, k3d::imaterial* material){
    //Declare Inputs
    INPUT(k3d::bool_t,bottom_cap,args);
    INPUT(k3d::int32_t,u_segments,args);
    INPUT(k3d::int32_t,v_segments,args);

    Output = k3d::mesh();

    // Create the cone topology ...
    boost::scoped_ptr<k3d::polyhedron::primitive> polyhedron(k3d::polyhedron::create(Output));

    polyhedron->shell_types.push_back(k3d::polyhedron::POLYGONS);
    k3d::polyhedron::add_cylinder(Output, *polyhedron, 0, v_segments, u_segments, material);

    // Ensure that the top of the cone is "closed" topologically ...
    polyhedron->face_shells.push_back(0);
    polyhedron->face_first_loops.push_back(polyhedron->loop_first_edges.size());
    polyhedron->face_loop_counts.push_back(1);
    polyhedron->face_selections.push_back(0);
    polyhedron->face_materials.push_back(material);
    polyhedron->loop_first_edges.push_back(polyhedron->clockwise_edges.size());

    for(k3d::int32_t u = u_segments; u != 0; --u)
    {
      polyhedron->clockwise_edges.push_back(polyhedron->clockwise_edges.size() + 1);
      polyhedron->edge_selections.push_back(0);
      polyhedron->vertex_points.push_back(u % u_segments);
      polyhedron->vertex_selections.push_back(0);
    }
    polyhedron->clockwise_edges.back() = polyhedron->loop_first_edges.back();

    // Optionally close the bottom_cap of the cone ...
    if(bottom_cap)
    {
      polyhedron->face_shells.push_back(0);
      polyhedron->face_first_loops.push_back(polyhedron->loop_first_edges.size());
      polyhedron->face_loop_counts.push_back(1);
      polyhedron->face_selections.push_back(0);
      polyhedron->face_materials.push_back(material);
      polyhedron->loop_first_edges.push_back(polyhedron->clockwise_edges.size());

      const k3d::uint_t offset = v_segments * u_segments;
      for(k3d::int32_t u = 0; u != u_segments; ++u)
      {
        polyhedron->clockwise_edges.push_back(polyhedron->clockwise_edges.size() + 1);
        polyhedron->edge_selections.push_back(0);
        polyhedron->vertex_points.push_back(offset + u);
        polyhedron->vertex_selections.push_back(0);
      }
      polyhedron->clockwise_edges.back() = polyhedron->loop_first_edges.back();
    }
    return EXIT_NORMAL;
  }

  int updateMeshGeometry(k3d::mesh& Output){
    //Declare Inputs
    INPUT(k3d::double_t,height,args);
    INPUT(k3d::double_t,radius,args);
    INPUT(k3d::double_t,u_power,args);
    INPUT(k3d::int32_t,u_segments,args);
    INPUT(k3d::double_t,v_power,args);
    INPUT(k3d::int32_t,v_segments,args);


    const k3d::double_t inv_u_power = u_power ? 1.0 / u_power : 1.0;

    const k3d::int32_t point_u_segments = u_segments;
    const k3d::int32_t point_v_segments = v_segments + 1;

    k3d::mesh::points_t& points = Output.points.writable();

    k3d::uint_t point = 0;
    for(k3d::int32_t v = 0; v != point_v_segments; ++v)
    {
      const k3d::double_t percent = k3d::ratio(v, point_v_segments - 1);
      const k3d::double_t varying_radius = k3d::mix(0.001 * radius, radius, percent);

      for(k3d::int32_t u = 0; u != point_u_segments; ++u, ++point)
      {
        const k3d::double_t theta = k3d::pi_times_2() * k3d::ratio(u, point_u_segments);

        k3d::double_t x = cos(theta);
        k3d::double_t y = -sin(theta);
        k3d::double_t z = k3d::mix(height, 0.0, std::pow(percent, v_power));

        x = varying_radius * k3d::sign(x) * std::pow(std::abs(x), inv_u_power);
        y = varying_radius * k3d::sign(y) * std::pow(std::abs(y), inv_u_power);

        points[point] = k3d::point3(x, y, z);
      }
    }
    return EXIT_NORMAL;
  }
};

EXPORT_METHOD(PolyCone,updateMeshTopology);
EXPORT_METHOD(PolyCone,updateMeshGeometry);
