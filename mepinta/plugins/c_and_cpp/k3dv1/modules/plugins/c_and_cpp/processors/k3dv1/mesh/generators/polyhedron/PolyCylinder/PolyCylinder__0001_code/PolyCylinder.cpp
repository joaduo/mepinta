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
        Code based on the PolyCylinder plugin of the K-3D project.
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

class PolyCylinder:
  public k3d::MPExtension::plugins::processors::mesh::MeshSourceBase
{
private:
  //Called when creating vertices, edges and faces
  int updateMeshTopology(k3d::mesh& Output, k3d::imaterial* material){
    //Declare Inputs
    INPUT(k3d::int32_t,u_segments,args);
    INPUT(k3d::int32_t,v_segments,args);

    Output = k3d::mesh();

    boost::scoped_ptr<k3d::polyhedron::primitive> polyhedron(k3d::polyhedron::create(Output));

    polyhedron->shell_types.push_back(k3d::polyhedron::POLYGONS);
    k3d::polyhedron::add_cylinder(Output, *polyhedron, 0, v_segments, u_segments, material);

    updateMeshGeometryPrivate(Output,material,polyhedron);

    return EXIT_NORMAL;
  }
  
  int updateMeshGeometry(k3d::mesh& Output){
    log_debug("Right now all the suff is done on the 'updateMeshTopology' method.(I suppose a solvable technical reason)\n");
    return EXIT_NORMAL;
  }

  //Called when updating the vertices positions
  int updateMeshGeometryPrivate(k3d::mesh& Output, k3d::imaterial* material, boost::scoped_ptr<k3d::polyhedron::primitive>& polyhedron){
    //Declare Inputs
    INPUT(k3d::bool_t,bottom_cap,args);
    INPUT(k3d::int32_t,bottom_segments,args);
    INPUT(k3d::double_t,radius,args);
    INPUT(k3d::bool_t,top_cap,args);
    INPUT(k3d::int32_t,top_segments,args);
    INPUT(k3d::double_t,u_power,args);
    INPUT(k3d::int32_t,u_segments,args);
    INPUT(k3d::int32_t,v_segments,args);
    INPUT(k3d::double_t,z_max,args);
    INPUT(k3d::double_t,z_min,args);

    const k3d::double_t inv_u_power = u_power ? 1.0 / u_power : 1.0;

    k3d::mesh::points_t& points = Output.points.writable();
    k3d::mesh::selection_t& point_selection = Output.point_selection.writable();

    // Shape the cylinder points
    for(k3d::int32_t v = 0; v <= v_segments; ++v)
    {
      const k3d::double_t height = k3d::ratio(v, v_segments);

      for(k3d::int32_t u = 0; u != u_segments; ++u)
      {
        const k3d::double_t theta = k3d::pi_times_2() * k3d::ratio(u, u_segments);

        k3d::double_t x = cos(theta);
        k3d::double_t y = -sin(theta);
        k3d::double_t z = k3d::mix(z_max, z_min, height);

        x = radius * k3d::sign(x) * std::pow(std::abs(x), inv_u_power);
        y = radius * k3d::sign(y) * std::pow(std::abs(y), inv_u_power);

        points[v * u_segments + u] = k3d::point3(x, y, z);
      }
    }

    //const k3d::uint_t top_rim_offset = 0;
    const k3d::uint_t bottom_rim_offset = v_segments * u_segments;

    // Optionally cap the top_cap of the cylinder ...
    if(top_cap)
    {
      if(!top_segments)
      {
        polyhedron->face_shells.push_back(0);
        polyhedron->face_first_loops.push_back(polyhedron->loop_first_edges.size());
        polyhedron->face_loop_counts.push_back(1);
        polyhedron->face_selections.push_back(0);
        polyhedron->face_materials.push_back(material);

        polyhedron->loop_first_edges.push_back(polyhedron->clockwise_edges.size());

        for(k3d::int32_t u = 0; u != u_segments; ++u)
        {
          polyhedron->clockwise_edges.push_back(polyhedron->clockwise_edges.size() + 1);
          polyhedron->edge_selections.push_back(0);

          polyhedron->vertex_points.push_back((u_segments - u) % u_segments);
          polyhedron->vertex_selections.push_back(0);
        }
        polyhedron->clockwise_edges.back() = polyhedron->loop_first_edges.back();
      }
      else
      {
        const k3d::uint_t middle_point_index = points.size();
        const k3d::point3 middle_point(0, 0, z_max);
        points.push_back(middle_point);
        point_selection.push_back(0);

        // Create segment quads
        k3d::uint_t last_ring_point_offset = 0;
        k3d::uint_t current_ring_point_offset = 0;
        for(k3d::int32_t n = top_segments; n > 1; --n)
        {
          current_ring_point_offset = points.size();
          const k3d::double_t factor = k3d::ratio(n - 1, top_segments);
          for(k3d::int32_t u = 0; u < u_segments; ++u)
          {
            points.push_back(middle_point + factor * (points[u] - middle_point));
            point_selection.push_back(0);
          }

          for(k3d::int32_t u = 0; u < u_segments; ++u)
          {
            k3d::polyhedron::add_quadrilateral(
              Output,
              *polyhedron,
              0,
              last_ring_point_offset + (u + 1) % u_segments,
              last_ring_point_offset + (u + 0) % u_segments,
              current_ring_point_offset + (u + 0) % u_segments,
              current_ring_point_offset + (u + 1) % u_segments,
              material);
          }

          last_ring_point_offset = current_ring_point_offset;
        }

        // Create middle triangle fan
        for(k3d::int32_t u = 0; u != u_segments; ++u)
        {
          k3d::polyhedron::add_triangle(
            Output,
            *polyhedron,
            0,
            current_ring_point_offset + (u + 1) % u_segments,
            current_ring_point_offset + (u + 0) % u_segments,
            middle_point_index,
            material);
        }
      }
    }

    // Optionally cap the bottom_cap of the cylinder ...
    if(bottom_cap)
    {
      if(!bottom_segments)
      {
        polyhedron->face_shells.push_back(0);
        polyhedron->face_first_loops.push_back(polyhedron->loop_first_edges.size());
        polyhedron->face_loop_counts.push_back(1);
        polyhedron->face_selections.push_back(0);
        polyhedron->face_materials.push_back(material);

        polyhedron->loop_first_edges.push_back(polyhedron->clockwise_edges.size());

        for(k3d::int32_t u = 0; u != u_segments; ++u)
        {
          polyhedron->clockwise_edges.push_back(polyhedron->clockwise_edges.size() + 1);
          polyhedron->edge_selections.push_back(0);

          polyhedron->vertex_points.push_back(bottom_rim_offset + u);
          polyhedron->vertex_selections.push_back(0);
        }
        polyhedron->clockwise_edges.back() = polyhedron->loop_first_edges.back();
      }
      else
      {
        const k3d::uint_t middle_point_index = points.size();
        const k3d::point3 middle_point(0, 0, z_min);
        points.push_back(middle_point);
        point_selection.push_back(0);

        // Create segment quads
        k3d::uint_t last_ring_point_offset = v_segments * u_segments;
        k3d::uint_t current_ring_point_offset = v_segments * u_segments;
        for(k3d::int32_t n = bottom_segments; n > 1; --n)
        {
          current_ring_point_offset = points.size();
          const k3d::double_t factor = k3d::ratio(n - 1, bottom_segments);
          for(k3d::int32_t u = 0; u < u_segments; ++u)
          {
            points.push_back(middle_point + factor * (points[(v_segments * u_segments) + u] - middle_point));
            point_selection.push_back(0);
          }

          for(k3d::int32_t u = 0; u < u_segments; ++u)
          {
            k3d::polyhedron::add_quadrilateral(
              Output,
              *polyhedron,
              0,
              last_ring_point_offset + (u + 0) % u_segments,
              last_ring_point_offset + (u + 1) % u_segments,
              current_ring_point_offset + (u + 1) % u_segments,
              current_ring_point_offset + (u + 0) % u_segments,
              material);
          }

          last_ring_point_offset = current_ring_point_offset;
        }

        // Create middle triangle fan
        for(k3d::int32_t u = 0; u != u_segments; ++u)
        {
          k3d::polyhedron::add_triangle(
            Output,
            *polyhedron,
            0,
            current_ring_point_offset + (u + 0) % u_segments,
            current_ring_point_offset + (u + 1) % u_segments,
            middle_point_index,
            material);
        }
      }
    }

    return EXIT_NORMAL;
  }
};

EXPORT_METHOD(PolyCylinder,updateMeshTopology);
EXPORT_METHOD(PolyCylinder,updateMeshGeometry);
