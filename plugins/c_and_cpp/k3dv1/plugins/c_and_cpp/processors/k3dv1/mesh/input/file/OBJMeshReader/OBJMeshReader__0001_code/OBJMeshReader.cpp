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
        Code based on the OBJMeshReader plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/MeshReaderBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/k3dv1/imaterial/imaterial.h>
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/c/boehm_gc/charp/charp.h>

#include "obj_parser.h"

#include <k3dsdk/fstream.h>
#include <k3dsdk/log.h>
#include <k3dsdk/nurbs_patch.h>
#include <k3dsdk/polyhedron.h>
#include <k3dsdk/types.h>

#include <boost/scoped_ptr.hpp>

class OBJMeshReader:
  public k3d::MPExtension::plugins::processors::mesh::MeshReaderBase
{
private:
  int loadMesh(const k3d::filesystem::path& Path, k3d::mesh& Output, k3d::imaterial* material){
    Output = k3d::mesh();

    k3d::filesystem::ifstream file(Path);
    if(!file)
    {
      k3d::log() << error << k3d_file_reference << ": error opening [" << Path.native_console_string() << "]" << std::endl;
      return EXIT_NORMAL;
    }

    my_parser parser(Output, material);
    parser.parse(file);
    return EXIT_NORMAL;
  }

  class my_parser :
    public module::obj::io::obj_parser
  {
  public:
    my_parser(k3d::mesh& Mesh, k3d::imaterial* const Material) :
      mesh(Mesh),
      material(Material),
      points(0),
      point_selection(0),
      u_order(0),
      v_order(0),
      s0(0),
      s1(0),
      t0(0),
      t1(0)
    {
    }

  private:
    k3d::mesh& mesh;
    k3d::imaterial* const material;
    k3d::mesh::points_t* points;
    k3d::mesh::selection_t* point_selection;
    boost::scoped_ptr<k3d::mesh::weights_t> point_weights; // Note: *not* part of the mesh!

    boost::scoped_ptr<k3d::polyhedron::primitive> polyhedron;
    boost::scoped_ptr<k3d::nurbs_patch::primitive> nurbs_patch;

    k3d::string_t curve_surface_type;
    k3d::uint_t u_order;
    k3d::uint_t v_order;
    k3d::double_t s0;
    k3d::double_t s1;
    k3d::double_t t0;
    k3d::double_t t1;
    k3d::mesh::indices_t vertex_coordinates;
    k3d::mesh::indices_t texture_coordinates;
    k3d::mesh::indices_t normal_coordinates;
    k3d::mesh::knots_t u_knots;
    k3d::mesh::knots_t v_knots;

    void on_vertex_coordinates(const k3d::point4& Vertex)
    {
      if(!points)
              points = &mesh.points.create();

      if(!point_selection)
              point_selection = &mesh.point_selection.create();

      if(!point_weights)
              point_weights.reset(new k3d::mesh::weights_t()); // Note: *not* part of the mesh!

      points->push_back(k3d::point3(Vertex[0], Vertex[1], Vertex[2]));
      point_selection->push_back(0.0);
      point_weights->push_back(Vertex[3]);
    }

#pragma GCC diagnostic ignored "-Wunused-parameter"

    void on_face(const k3d::mesh::indices_t& Points, const k3d::mesh::indices_t& TexturePoints, const k3d::mesh::indices_t& Normals)
    {
      if(!polyhedron)
      {
              polyhedron.reset(k3d::polyhedron::create(mesh));
              polyhedron->shell_types.push_back(k3d::polyhedron::POLYGONS);
      }

      polyhedron->face_shells.push_back(0);
      polyhedron->face_first_loops.push_back(polyhedron->loop_first_edges.size());
      polyhedron->face_loop_counts.push_back(1);
      polyhedron->face_selections.push_back(0.0);
      polyhedron->face_materials.push_back(material);
      polyhedron->loop_first_edges.push_back(polyhedron->clockwise_edges.size());

      const k3d::uint_t point_begin = 0;
      const k3d::uint_t point_end = point_begin + Points.size();
      const k3d::uint_t first_edge = polyhedron->clockwise_edges.size();
      for(k3d::uint_t point = point_begin; point != point_end; ++point)
      {
              polyhedron->clockwise_edges.push_back(polyhedron->clockwise_edges.size() + 1);
              polyhedron->edge_selections.push_back(0.0);
              polyhedron->vertex_points.push_back(Points[point]);
              polyhedron->vertex_selections.push_back(0.0);
      }
      polyhedron->clockwise_edges.back() = first_edge;
    }

    void on_curve_surface_type(const k3d::string_t& Type)
    {
      curve_surface_type = Type;
    }

    void on_degree(const k3d::uint_t& UDegree, const k3d::uint_t& VDegree)
    {
      u_order = UDegree + 1;
      v_order = VDegree + 1;
    }

    void on_surface(const k3d::double_t& S0, const k3d::double_t& S1, const k3d::double_t& T0, const k3d::double_t& T1, const k3d::mesh::indices_t& VertexCoordinates, const k3d::mesh::indices_t& TextureCoordinates, const k3d::mesh::indices_t& NormalCoordinates)
    {
      s0 = S0;
      s1 = S1;
      t0 = T0;
      t1 = T1;
      vertex_coordinates = VertexCoordinates;
      texture_coordinates = TextureCoordinates;
      normal_coordinates = NormalCoordinates;
    }

    void on_parameter(const k3d::string_t& Direction, const k3d::mesh::knots_t& Knots)
    {
      if(Direction == "u")
      {
              u_knots = Knots;
              return;
      }
      else if(Direction == "v")
      {
              v_knots = Knots;
              return;
      }

      throw std::runtime_error("unknown knot direction: " + Direction);
    }

    void on_curve_surface_end()
    {
      if(curve_surface_type != "bspline")
              throw std::runtime_error("unknown surface type [" + curve_surface_type + "] will be ignored");

      const k3d::uint_t expected_vertex_count = (u_knots.size() - u_order) * (v_knots.size() - v_order);
      if(expected_vertex_count != vertex_coordinates.size())
              throw std::runtime_error("invalid vertex count for bspline surface");

      if(!nurbs_patch)
              nurbs_patch.reset(k3d::nurbs_patch::create(mesh));

      nurbs_patch->patch_first_points.push_back(nurbs_patch->patch_points.size());
      nurbs_patch->patch_u_point_counts.push_back(u_knots.size() - u_order);
      nurbs_patch->patch_v_point_counts.push_back(v_knots.size() - v_order);
      nurbs_patch->patch_u_orders.push_back(u_order);
      nurbs_patch->patch_v_orders.push_back(v_order);
      nurbs_patch->patch_u_first_knots.push_back(nurbs_patch->patch_u_knots.size());
      nurbs_patch->patch_v_first_knots.push_back(nurbs_patch->patch_v_knots.size());
      nurbs_patch->patch_selections.push_back(0);
      nurbs_patch->patch_materials.push_back(static_cast<k3d::imaterial*>(0));
      nurbs_patch->patch_points.insert(nurbs_patch->patch_points.end(), vertex_coordinates.begin(), vertex_coordinates.end());

      for(k3d::uint_t i = 0; i != vertex_coordinates.size(); ++i)
              nurbs_patch->patch_point_weights.push_back((*point_weights)[vertex_coordinates[i]]);

      nurbs_patch->patch_u_knots.insert(nurbs_patch->patch_u_knots.end(), u_knots.begin(), u_knots.end());
      nurbs_patch->patch_v_knots.insert(nurbs_patch->patch_v_knots.end(), v_knots.begin(), v_knots.end());

      nurbs_patch->patch_trim_loop_counts.push_back(0);
      nurbs_patch->patch_first_trim_loops.push_back(0);

      curve_surface_type.clear();
      u_order = 0;
      v_order = 0;
      s0 = 0;
      s1 = 0;
      t0 = 0;
      t1 = 0;
      vertex_coordinates.clear();
      texture_coordinates.clear();
      normal_coordinates.clear();
      u_knots.clear();
      v_knots.clear();
    }
  };
};

EXPORT_METHOD(OBJMeshReader,loadMesh);
