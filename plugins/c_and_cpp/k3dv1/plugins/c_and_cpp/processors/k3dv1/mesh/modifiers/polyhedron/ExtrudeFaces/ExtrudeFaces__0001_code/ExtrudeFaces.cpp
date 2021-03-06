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
        Code based on the ExtrudeFaces plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/MeshModifierBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/mepinta/internal_any/internal_any.h>
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/c/builtin/int/int.h>
#include <data_types/c/builtin/double/double.h>

#include <k3dsdk/geometry.h>
#include <k3dsdk/polyhedron.h>
#include <k3dsdk/table_copier.h>

#include <boost/scoped_ptr.hpp>

class ExtrudeFaces:
  public k3d::MPExtension::plugins::processors::mesh::MeshModifierBase
{
private:
  ///
  virtual int createMesh(k3d::mesh& Input, k3d::mesh& Output ) {
    //Declare Inputs
    INPUT(k3d::bool_t,group_faces,args);
    INPUT(k3d::bool_t,group_normals,args);
    INPUT_VALIDATED_DEFAULT(k3d::int32_t,segments,args, segments >= 0, 0);
    INPUT(k3d::bool_t,select_new_faces,args);

    k3d::mesh::indices_t& point_map = getInternal<k3d::mesh::indices_t>("point_map");
    std::vector<extrude_vertex>& extrude_vertices =getInternal<std::vector<extrude_vertex> >("extrude_vertices");

    // Create output geometry ...
    Output = Input;

    if(!Output.points)
            return EXIT_SAFETY_CHECK;
    if(!Output.point_selection)
            return EXIT_SAFETY_CHECK;

    // Clear previously cached data ...
    extrude_vertices.clear();

    k3d::mesh::points_t& points = Output.points.writable();
    k3d::mesh::selection_t& point_selection = Output.point_selection.writable();

    // For each polyhedron ...
    for(k3d::mesh::primitives_t::iterator primitive = Output.primitives.begin(); primitive != Output.primitives.end(); ++primitive)
    {
            boost::scoped_ptr<k3d::polyhedron::primitive> polyhedron(k3d::polyhedron::validate(Output, *primitive));
            if(!polyhedron)
                    continue;

            // Get ready to copy attributes ...
            k3d::table_copier point_attributes(Output.point_attributes);
            k3d::table_copier edge_attributes(polyhedron->edge_attributes);
            k3d::table_copier vertex_attributes(polyhedron->vertex_attributes);
            k3d::table_copier face_attributes(polyhedron->face_attributes);

            // Compute a mapping from edges to faces ...
            k3d::mesh::indices_t edge_faces;
            k3d::polyhedron::create_edge_face_lookup(*polyhedron, edge_faces);

            // Compute links to adjacent edges ...
            k3d::mesh::bools_t boundary_edges;
            k3d::mesh::indices_t adjacent_edges;
            k3d::polyhedron::create_edge_adjacency_lookup(polyhedron->vertex_points, polyhedron->clockwise_edges, boundary_edges, adjacent_edges);

            // Identify edges that will be extruded ...
            const k3d::uint_t edge_begin = 0;
            const k3d::uint_t edge_end = edge_begin + polyhedron->clockwise_edges.size();
            k3d::mesh::bools_t extrusion_edges(polyhedron->clockwise_edges.size(), false);
            k3d::mesh::bools_t border_edges(polyhedron->clockwise_edges.size(), false);
            for(k3d::uint_t edge = edge_begin; edge != edge_end; ++edge)
            {
                    // Every edge that's adjacent to a selected face will be an extrusion edge ...
                    if(!polyhedron->face_selections[edge_faces[edge]])
                            continue;

                    extrusion_edges[edge] = true;

                    // Identify edges on the extrusion boundary ...
                    if(group_faces && !boundary_edges[edge] && polyhedron->face_selections[edge_faces[adjacent_edges[edge]]])
                            continue;

                    border_edges[edge] = true;
            }

            // Identify clockwise boundary edges ...
            k3d::mesh::indices_t clockwise_border_edges(polyhedron->clockwise_edges.size(), k3d::uint_t(-1));
            for(k3d::uint_t edge = edge_begin; edge != edge_end; ++edge)
            {
                    if(!border_edges[edge])
                            continue;

                    k3d::uint_t clockwise_edge = polyhedron->clockwise_edges[edge];
                    while(!border_edges[clockwise_edge])
                            clockwise_edge = polyhedron->clockwise_edges[adjacent_edges[clockwise_edge]];
                    clockwise_border_edges[edge] = clockwise_edge;
            }

            // Identify counterclockwise boundary edges ...
            k3d::mesh::indices_t counterclockwise_border_edges(polyhedron->clockwise_edges.size());
            for(k3d::uint_t edge = edge_begin; edge != edge_end; ++edge)
            {
                    if(!border_edges[edge])
                            continue;

                    counterclockwise_border_edges[clockwise_border_edges[edge]] = edge;
            }

            // Compute face normal vectors ...
            k3d::mesh::normals_t face_normals;
            k3d::polyhedron::create_face_normal_lookup(Output, *polyhedron, face_normals);

            // Compute the normal vector for each vertex ...
            const k3d::uint_t face_begin = 0;
            const k3d::uint_t face_end = face_begin + polyhedron->face_first_loops.size();
            k3d::mesh::vectors_t vertex_normals(polyhedron->clockwise_edges.size(), k3d::vector3(0, 0, 0));
            k3d::mesh::vectors_t point_normals(points.size(), k3d::vector3(0, 0, 0));
            if(group_faces)
            {
                    if(group_normals)
                    {
                            k3d::normal3 normal(0, 0, 0);
                            for(k3d::uint_t face = face_begin; face != face_end; ++face)
                            {
                                    if(!polyhedron->face_selections[face])
                                            continue;

                                    normal += face_normals[face];
                            }
                            std::fill(vertex_normals.begin(), vertex_normals.end(), k3d::to_vector(k3d::normalize(normal)));
                            std::fill(point_normals.begin(), point_normals.end(), k3d::to_vector(k3d::normalize(normal)));
                    }
                    else
                    {

                            for(k3d::uint_t edge = edge_begin; edge != edge_end; ++edge)
                                    point_normals[polyhedron->vertex_points[edge]] += k3d::to_vector(face_normals[edge_faces[edge]]);
                            for(k3d::uint_t i = 0; i != points.size(); ++i)
                                    point_normals[i] = k3d::normalize(point_normals[i]);
                            for(k3d::uint_t edge = edge_begin; edge != edge_end; ++edge)
                                    vertex_normals[edge] = point_normals[polyhedron->vertex_points[edge]];
                    }
            }
            else
            {
                    for(k3d::uint_t edge = edge_begin; edge != edge_end; ++edge)
                    {
                            vertex_normals[edge] = k3d::to_vector(k3d::normalize(face_normals[edge_faces[edge]]));
                    }
            }

            // Compute the inset direction for each edge ...
            k3d::mesh::vectors_t edge_insets(polyhedron->clockwise_edges.size());
            for(k3d::uint_t edge = edge_begin; edge != edge_end; ++edge)
            {
                    edge_insets[edge] = k3d::normalize((points[polyhedron->vertex_points[polyhedron->clockwise_edges[edge]]] - points[polyhedron->vertex_points[edge]]) ^ face_normals[edge_faces[edge]]);
            }

            // Keep track of a mapping from old vertex points to new vertex points ...
            k3d::mesh::indices_t vertex_point_map(polyhedron->vertex_points.size());
            for(k3d::uint_t edge = edge_begin; edge != edge_end; ++edge)
                    vertex_point_map[edge] = polyhedron->vertex_points[edge];

            // For each segment ...
            std::vector<k3d::mesh::indices_t> layer_vertex_points(segments + 1, polyhedron->vertex_points);
            for(k3d::int32_t segment = 0; segment != segments; ++segment)
            {
                    std::vector<boost::optional<k3d::uint_t> > layer_points(points.size());

                    // Create border-edge vertices ...
                    for(k3d::uint_t edge = edge_begin; edge != edge_end; ++edge)
                    {
                            if(!border_edges[edge])
                                    continue;

                            const k3d::uint_t old_point = polyhedron->vertex_points[edge];
                            const k3d::uint_t new_point = points.size();

                            layer_points[old_point] = new_point;
                            vertex_point_map[edge] = new_point;
                            layer_vertex_points[segment + 1][edge] = new_point;

                            const k3d::vector3 inset1 = edge_insets[edge];
                            const k3d::vector3 inset2 = edge_insets[counterclockwise_border_edges[edge]];

                            extrude_vertices.push_back(
                                    extrude_vertex(
                                            new_point,
                                            points[old_point],
                                            vertex_normals[edge],
                                            (-1 / std::cos(std::acos(inset1 * inset2) / 2)) * k3d::normalize(inset1 + inset2),
                                            k3d::ratio(segment + 1, segments)));

                            points.push_back(k3d::point3());
                            point_selection.push_back(0);
                            point_attributes.push_back(polyhedron->vertex_points[edge]);
                    }

                    // Create interior extrusion-edge vertices ...
                    for(k3d::uint_t edge = edge_begin; edge != edge_end; ++edge)
                    {
                            if(!extrusion_edges[edge])
                                    continue;

                            if(border_edges[edge])
                                    continue;

                            const k3d::uint_t old_point = polyhedron->vertex_points[edge];
                            if(group_faces && layer_points[old_point])
                            {
                                    vertex_point_map[edge] = *layer_points[old_point];
                                    layer_vertex_points[segment + 1][edge] = *layer_points[old_point];
                                    continue;
                            }

                            const k3d::uint_t new_point = points.size();

                            layer_points[old_point] = new_point;
                            vertex_point_map[edge] = new_point;
                            layer_vertex_points[segment + 1][edge] = new_point;

                            extrude_vertices.push_back(
                                    extrude_vertex(
                                            new_point,
                                            points[old_point],
                                            vertex_normals[edge],
                                            k3d::vector3(0, 0, 0),
                                            k3d::ratio(segment + 1, segments)));

                            points.push_back(k3d::point3());
                            point_selection.push_back(0);
                            point_attributes.push_back(polyhedron->vertex_points[edge]);
                    }
            }

            // Remap vertices to newly-created points ...
            for(k3d::uint_t edge = edge_begin; edge != edge_end; ++edge)
                    polyhedron->vertex_points[edge] = vertex_point_map[edge];

            // For each extrusion edge, create bevel faces ...
            for(k3d::int32_t segment = 0; segment != segments; ++segment)
            {
                    for(k3d::uint_t edge = edge_begin; edge != edge_end; ++edge)
                    {
                            if(!border_edges[edge])
                                    continue;

                            const k3d::uint_t new_first_edge = polyhedron->clockwise_edges.size();

                            polyhedron->clockwise_edges.push_back(polyhedron->clockwise_edges.size() + 1);
                            polyhedron->clockwise_edges.push_back(polyhedron->clockwise_edges.size() + 1);
                            polyhedron->clockwise_edges.push_back(polyhedron->clockwise_edges.size() + 1);
                            polyhedron->clockwise_edges.push_back(polyhedron->clockwise_edges.size() - 3);

                            polyhedron->edge_selections.push_back(0);
                            polyhedron->edge_selections.push_back(0);
                            polyhedron->edge_selections.push_back(0);
                            polyhedron->edge_selections.push_back(0);

                            edge_attributes.push_back(edge);
                            edge_attributes.push_back(edge);
                            edge_attributes.push_back(edge);
                            edge_attributes.push_back(edge);

                            polyhedron->vertex_points.push_back(layer_vertex_points[segment + 1][clockwise_border_edges[edge]]);
                            polyhedron->vertex_points.push_back(layer_vertex_points[segment + 1][edge]);
                            polyhedron->vertex_points.push_back(layer_vertex_points[segment][edge]);
                            polyhedron->vertex_points.push_back(layer_vertex_points[segment][clockwise_border_edges[edge]]);

                            vertex_attributes.push_back(clockwise_border_edges[edge]);
                            vertex_attributes.push_back(edge);
                            vertex_attributes.push_back(edge);
                            vertex_attributes.push_back(clockwise_border_edges[edge]);

                            polyhedron->vertex_selections.push_back(0);
                            polyhedron->vertex_selections.push_back(0);
                            polyhedron->vertex_selections.push_back(0);
                            polyhedron->vertex_selections.push_back(0);

                            polyhedron->face_shells.push_back(polyhedron->face_shells[edge_faces[edge]]);
                            polyhedron->face_first_loops.push_back(polyhedron->loop_first_edges.size());
                            polyhedron->face_loop_counts.push_back(1);
                            polyhedron->face_selections.push_back(select_new_faces ? 1 : 0);
                            polyhedron->face_materials.push_back(polyhedron->face_materials[edge_faces[edge]]);

                            face_attributes.push_back(edge_faces[edge]);

                            polyhedron->loop_first_edges.push_back(new_first_edge);
                    }
            }
    }

    k3d::mesh::bools_t unused_points;
    k3d::mesh::lookup_unused_points(Output, unused_points);
    k3d::mesh::delete_points(Output, unused_points, point_map);

    return EXIT_NORMAL;
  }
  ///
  virtual int updateMesh(k3d::mesh& Input, k3d::mesh& Output ) {
    //Declare Inputs
    INPUT(k3d::double_t,distance,args);
    INPUT(k3d::double_t,inset,args);

    k3d::mesh::indices_t& point_map = getInternal<k3d::mesh::indices_t>("point_map");
    std::vector<extrude_vertex>& extrude_vertices =getInternal<std::vector<extrude_vertex> >("extrude_vertices");

    k3d::mesh::points_t& points = Output.points.writable();

    const k3d::uint_t vertex_begin = 0;
    const k3d::uint_t vertex_end = vertex_begin + extrude_vertices.size();
    for(k3d::uint_t vertex_index = vertex_begin; vertex_index != vertex_end; ++vertex_index)
    {
            const extrude_vertex& vertex = extrude_vertices[vertex_index];

            points[point_map[vertex.point]] =
                    k3d::mix(vertex.start, vertex.start + (distance * vertex.extrude_direction) + (inset * vertex.inset_direction), vertex.ratio);
    }

    return EXIT_NORMAL;
  }

  /// Caches new points for better interactive performance
  class extrude_vertex
  {
  public:
          extrude_vertex(const k3d::uint_t Point, const k3d::point3& Start, const k3d::vector3& ExtrudeDirection, const k3d::vector3& InsetDirection, const k3d::double_t Ratio) :
                  point(Point),
                  start(Start),
                  extrude_direction(ExtrudeDirection),
                  inset_direction(InsetDirection),
                  ratio(Ratio)
          {
          }

          friend std::ostream& operator<<(std::ostream& Stream, const extrude_vertex& Value)
          {
                  Stream << Value.point << " | " << Value.start << " | " << Value.extrude_direction << " | " << Value.inset_direction << " | " << Value.ratio;
                  return Stream;
          }

          k3d::uint_t point;
          k3d::point3 start;
          k3d::vector3 extrude_direction;
          k3d::vector3 inset_direction;
          k3d::double_t ratio;
  };

};

EXPORT_METHOD(ExtrudeFaces,demuxMeshSignal);
EXPORT_METHOD(ExtrudeFaces,createMesh);
EXPORT_METHOD(ExtrudeFaces,updateMesh);
