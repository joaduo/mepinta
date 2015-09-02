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
        Code based on the PolySphere plugin of the K-3D project.
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

/// Enumerates supported primitive types
typedef enum
{
  SPHERE=0,
  QUAD_ONLY_SPHERE=1,
  SPHEREIZED_CYLINDER=2
} primitive_t;

class PolySphere:
  public k3d::MPExtension::plugins::processors::mesh::MeshSourceBase
{
  //Called when creating vertices, edges and faces
  int updateMeshTopology(k3d::mesh& Output, k3d::imaterial* material){
    //Declare Inputs
    INPUT(primitive_t,primitive,args);
    INPUT_VALIDATED_DEFAULT(k3d::int32_t,u_segments,args, u_segments >= 3, 3);
    INPUT_VALIDATED_DEFAULT(k3d::int32_t,v_segments,args, v_segments >= 3, 3);

    Output = k3d::mesh();

    k3d::mesh::points_t& points = Output.points.create();
    k3d::mesh::selection_t& point_selection = Output.point_selection.create();

    switch(primitive)
    {
      case SPHERE:
      {
              boost::scoped_ptr<k3d::polyhedron::primitive> polyhedron(k3d::polyhedron::create(Output));
              polyhedron->shell_types.push_back(k3d::polyhedron::POLYGONS);

              // Cap the top of the cylinder with a triangle fan ...
              points.push_back(k3d::point3());
              point_selection.push_back(0);

              for(k3d::int32_t u = 0; u != u_segments; ++u)
              {
                      k3d::polyhedron::add_triangle(
                              Output,
                              *polyhedron,
                              0,
                              ((u + 1) % u_segments) + 1,
                              ((u + 0) % u_segments) + 1,
                              0,
                              material
                              );
              }

              // Create a cylinder ...
              k3d::polyhedron::add_cylinder(Output, *polyhedron, 0, v_segments - 2, u_segments, material);

              // Cap the bottom of the cylinder with a triangle fan ...
              points.push_back(k3d::point3());
              point_selection.push_back(0);

              for(k3d::int32_t u = 0; u != u_segments; ++u)
              {
                      k3d::polyhedron::add_triangle(
                              Output,
                              *polyhedron,
                              0,
                              (((v_segments - 2) * u_segments) + (u + 0) % u_segments) + 1,
                              (((v_segments - 2) * u_segments) + (u + 1) % u_segments) + 1,
                              points.size() - 1,
                              material
                              );
              }

              break;
      }
      case QUAD_ONLY_SPHERE:
      {
              boost::scoped_ptr<k3d::polyhedron::primitive> polyhedron(k3d::polyhedron::create(Output));
              polyhedron->shell_types.push_back(k3d::polyhedron::POLYGONS);

              // Cap the top of the cylinder with quads / a triangle fan ...
              points.push_back(k3d::point3());
              point_selection.push_back(0);

              if(u_segments & 1)
              {
                      for(k3d::int32_t u = 0; u != u_segments; ++u)
                      {
                              k3d::polyhedron::add_triangle(
                                      Output,
                                      *polyhedron,
                                      0,
                                      ((u + 1) % u_segments) + 1,
                                      ((u + 0) % u_segments) + 1,
                                      0,
                                      material
                                      );
                      }
              }
              else
              {
                      for(k3d::int32_t u = 0; u != u_segments; u += 2)
                      {
                              k3d::polyhedron::add_quadrilateral(
                                      Output,
                                      *polyhedron,
                                      0,
                                      ((u + 2) % u_segments) + 1,
                                      ((u + 1) % u_segments) + 1,
                                      ((u + 0) % u_segments) + 1,
                                      0,
                                      material
                                      );
                      }
              }

              // Create a cylinder ...
              k3d::polyhedron::add_cylinder(Output, *polyhedron, 0, v_segments - 2, u_segments, material);

              // Cap the bottom of the cylinder with quads / a triangle fan ...
              points.push_back(k3d::point3());
              point_selection.push_back(0);

              if(u_segments & 1)
              {
                      for(k3d::int32_t u = 0; u != u_segments; ++u)
                      {
                              k3d::polyhedron::add_triangle(
                                      Output,
                                      *polyhedron,
                                      0,
                                      (((v_segments - 2) * u_segments) + (u + 0) % u_segments) + 1,
                                      (((v_segments - 2) * u_segments) + (u + 1) % u_segments) + 1,
                                      points.size() - 1,
                                      material
                                      );
                      }
              }
              else
              {
                      for(k3d::int32_t u = 0; u != u_segments; u += 2)
                      {
                              k3d::polyhedron::add_quadrilateral(
                                      Output,
                                      *polyhedron,
                                      0,
                                      (((v_segments - 2) * u_segments) + (u + 0) % u_segments) + 1,
                                      (((v_segments - 2) * u_segments) + (u + 1) % u_segments) + 1,
                                      (((v_segments - 2) * u_segments) + (u + 2) % u_segments) + 1,
                                      points.size() - 1,
                                      material
                                      );
                      }
              }

              break;
      }
      case SPHEREIZED_CYLINDER:
      {
              boost::scoped_ptr<k3d::polyhedron::primitive> polyhedron(k3d::polyhedron::create(Output));
              polyhedron->shell_types.push_back(k3d::polyhedron::POLYGONS);

              // Create a cylinder ...
              k3d::polyhedron::add_cylinder(Output, *polyhedron, 0, v_segments, u_segments, material);

              // Cap the top of the cylinder with a single polygon ...
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

                      polyhedron->vertex_points.push_back(u_segments - u - 1);
                      polyhedron->vertex_selections.push_back(0);
              }
              polyhedron->clockwise_edges.back() = polyhedron->loop_first_edges.back();

              // Cap the bottom of the cylinder with a single polygon ...
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

                      polyhedron->vertex_points.push_back((v_segments * u_segments) + u);
                      polyhedron->vertex_selections.push_back(0);
              }
              polyhedron->clockwise_edges.back() = polyhedron->loop_first_edges.back();

              break;
      }
    }
    return EXIT_NORMAL;
  }

  int updateMeshGeometry(k3d::mesh& Output){
    //Declare Inputs
    INPUT(primitive_t,primitive,args);
    INPUT(k3d::double_t,radius,args);
    INPUT(k3d::double_t,u_power,args);
    INPUT_VALIDATED_DEFAULT(k3d::int32_t,u_segments,args, u_segments >= 3, 3);
    INPUT(k3d::double_t,v_power,args);
    INPUT_VALIDATED_DEFAULT(k3d::int32_t,v_segments,args, v_segments >= 3, 3);

    const k3d::double_t inv_u_power = u_power ? 1.0 / u_power : 1.0;
    const k3d::double_t inv_v_power = v_power ? 1.0 / v_power : 1.0;

    k3d::mesh::points_t& points = Output.points.writable();

    switch(primitive)
    {
      case SPHERE:
      case QUAD_ONLY_SPHERE:
      {
              points[0] = k3d::point3(0, 0, radius);

              for(k3d::int32_t v = 1; v < v_segments; ++v)
              {
                      const k3d::double_t phi = k3d::pi() * k3d::ratio(v, v_segments);
                      const k3d::double_t varying_radius = k3d::mix(radius * 0.001, radius, sin(phi));

                      k3d::double_t z = cos(phi);
                      z = radius * k3d::sign(z) * std::pow(std::abs(z), inv_v_power);

                      for(k3d::int32_t u = 0; u != u_segments; ++u)
                      {
                              const k3d::double_t theta = k3d::pi_times_2() * k3d::ratio(u, u_segments);

                              k3d::double_t x = cos(theta);
                              k3d::double_t y = -sin(theta);

                              x = varying_radius * k3d::sign(x) * std::pow(std::abs(x), inv_u_power);
                              y = varying_radius * k3d::sign(y) * std::pow(std::abs(y), inv_u_power);

                              points[((v - 1) * u_segments) + u + 1] = k3d::point3(x, y, z);
                      }
              }

              points[points.size() - 1] = k3d::point3(0, 0, -radius);

              break;
      }
      case SPHEREIZED_CYLINDER:
      {
              for(k3d::int32_t v = 0; v <= v_segments; ++v)
              {
                      const k3d::double_t phi = k3d::pi() * k3d::ratio(v, v_segments);
                      const k3d::double_t varying_radius = k3d::mix(radius * 0.001, radius, sin(phi));

                      k3d::double_t z = cos(phi);
                      z = radius * k3d::sign(z) * std::pow(std::abs(z), inv_v_power);

                      for(k3d::int32_t u = 0; u != u_segments; ++u)
                      {
                              const k3d::double_t theta = k3d::pi_times_2() * k3d::ratio(u, u_segments);

                              k3d::double_t x = cos(theta);
                              k3d::double_t y = -sin(theta);

                              x = varying_radius * k3d::sign(x) * std::pow(std::abs(x), inv_u_power);
                              y = varying_radius * k3d::sign(y) * std::pow(std::abs(y), inv_u_power);

                              points[(v * u_segments) + u] = k3d::point3(x, y, z);
                      }
              }
              break;
      }
    }

    return EXIT_NORMAL;
  }

};

EXPORT_METHOD(PolySphere,updateMeshTopology);
EXPORT_METHOD(PolySphere,updateMeshGeometry);
