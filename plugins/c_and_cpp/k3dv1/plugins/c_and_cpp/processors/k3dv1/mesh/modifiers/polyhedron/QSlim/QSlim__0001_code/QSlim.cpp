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
        Code based on the QSlim plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/SimpleMeshModifierBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/k3dv1/imaterial/imaterial.h>
#include <data_types/c/builtin/int/int.h>
#include <data_types/c/builtin/double/double.h>

#include "MxQSlim.h"
#include <k3dsdk/polyhedron.h>
#include <k3dsdk/triangulator.h>

#include <boost/scoped_ptr.hpp>

//Generic enum contraction_type_t
typedef enum
{
  EDGE=0,
  FACE=1
} contraction_type_t;
//Generic enum quadric_weighting_t
typedef enum
{
  UNIFORM=0,
  AREA=1,
  ANGLE=2
} quadric_weighting_t;
//Generic enum placement_policy_t
typedef enum
{
  OPTIMAL=0,
  LINE=1,
  ENDORMID=2,
  ENDPOINTS=3
} placement_policy_t;

class qslim_convert :
        public k3d::triangulator
{
public:
        qslim_convert(MxStdModel& Model) :
                model(Model)
        {
        }

private:
        void add_vertex(const k3d::point3& Coordinates, k3d::uint_t Vertices[4], k3d::uint_t Edges[4], k3d::double_t Weights[4], k3d::uint_t NewVertex)
        {
                NewVertex = model.vert_count();
                model.add_vertex(-Coordinates[0], Coordinates[1], Coordinates[2]);
        }

        void add_triangle(k3d::uint_t Vertices[3], k3d::uint_t Edges[3])
        {
                model.add_face(Vertices[0], Vertices[1], Vertices[2]);
        }

        MxStdModel& model;
};

/// Converts a K-3D polyhedron to a QSlim model
MxStdModel* convert(const k3d::mesh& Mesh, const k3d::polyhedron::const_primitive& Primitive)
{
    // Create a new QSlim model ...
    MxStdModel* const model = new MxStdModel(100, 100);

    // Add mesh points to the model ...
    return_val_if_fail(Mesh.points, model);
    const k3d::mesh::points_t& points = *Mesh.points;

    const k3d::uint_t point_begin = 0;
    const k3d::uint_t point_end = point_begin + points.size();
    for(k3d::uint_t point = point_begin; point != point_end; ++point)
            model->add_vertex(-points[point][0], points[point][1], points[point][2]);

    // Convert polygons to triangles ...
    qslim_convert(*model).process(Mesh, Primitive);

    return model;
}

/// Appends a QSlim model to a K-3D mesh as a polyhedron primitive.
static void append(const k3d::polyhedron::const_primitive& InputPolyhedron, MxStdModel& Model, k3d::mesh& Mesh, k3d::imaterial* const Material)
{
    k3d::mesh::points_t& points = Mesh.points.writable();
    k3d::mesh::selection_t& point_selection = Mesh.point_selection.writable();
    const k3d::uint_t point_offset = points.size();
    for(unsigned int v = 0; v < Model.vert_count(); ++v)
    {
        k3d::point3 position(Model.vertex(v));
        position[0] = -position[0];
        points.push_back(position);
        point_selection.push_back(0);
    }

    boost::scoped_ptr<k3d::polyhedron::primitive> polyhedron(k3d::polyhedron::create(Mesh));
    polyhedron->constant_attributes = InputPolyhedron.constant_attributes;

    for(unsigned int f = 0; f != Model.face_count(); ++f)
    {
        if(!Model.face_is_valid(f))
            continue;

        polyhedron->face_shells.push_back(0);
        polyhedron->face_first_loops.push_back(polyhedron->loop_first_edges.size());
        polyhedron->face_loop_counts.push_back(1);
        polyhedron->face_selections.push_back(0);
        polyhedron->face_materials.push_back(Material);

        polyhedron->loop_first_edges.push_back(polyhedron->clockwise_edges.size());

        polyhedron->clockwise_edges.push_back(polyhedron->clockwise_edges.size() + 1);
        polyhedron->edge_selections.push_back(0);
        polyhedron->vertex_points.push_back(point_offset + Model.face(f).v[0]);
        polyhedron->vertex_selections.push_back(0);

        polyhedron->clockwise_edges.push_back(polyhedron->clockwise_edges.size() + 1);
        polyhedron->edge_selections.push_back(0);
        polyhedron->vertex_points.push_back(point_offset + Model.face(f).v[1]);
        polyhedron->vertex_selections.push_back(0);

        polyhedron->clockwise_edges.push_back(polyhedron->loop_first_edges.back());
        polyhedron->edge_selections.push_back(0);
        polyhedron->vertex_points.push_back(point_offset + Model.face(f).v[2]);
        polyhedron->vertex_selections.push_back(0);
    }

    polyhedron->shell_types.push_back(k3d::polyhedron::POLYGONS);
}

namespace k3d{

//TODO: should go to the k3dsdk core
//Empty a primitive polyhedron setting all its array to cero
void empty_polyhedron(polyhedron::primitive& Polyhedron){
  const uint_t cero_uint = 0;
  Polyhedron.shell_types.resize(cero_uint);
  Polyhedron.face_shells.resize(cero_uint);
  Polyhedron.face_first_loops.resize(cero_uint);
  Polyhedron.face_loop_counts.resize(cero_uint);
  Polyhedron.face_selections.resize(cero_uint);
  Polyhedron.face_materials.resize(cero_uint);
  Polyhedron.loop_first_edges.resize(cero_uint);
  Polyhedron.clockwise_edges.resize(cero_uint);
  Polyhedron.edge_selections.resize(cero_uint);
  Polyhedron.vertex_points.resize(cero_uint);
  Polyhedron.vertex_selections.resize(cero_uint);
  Polyhedron.constant_attributes.set_row_count(cero_uint);
  Polyhedron.face_attributes.set_row_count(cero_uint);
  Polyhedron.edge_attributes.set_row_count(cero_uint);
  Polyhedron.vertex_attributes.set_row_count(cero_uint);
}

}

class QSlim:
  public k3d::MPExtension::plugins::processors::mesh::SimpleMeshModifierBase
{
private:
  int createMesh(k3d::mesh& Input, k3d::mesh& Output ){
    //Declare Inputs
    INPUT(k3d::double_t,boundary_weight,args);
    INPUT(k3d::double_t,compactness_ratio,args);
    INPUT(contraction_type_t,contraction_type,args);
    INPUT_VALIDATED_DEFAULT(k3d::int32_t,face_count,args, face_count > 0, 1);
    INPUT(k3d::imaterial*,material,args);
    INPUT(k3d::mesh*,mesh,args);
    INPUT(k3d::double_t,meshing_penalty,args);
    INPUT(placement_policy_t,placement_policy,args);
    INPUT(quadric_weighting_t,quadric_weighting,args);

    Output.points = Input.points;
    Output.point_selection = Input.point_selection;

    // For each primitive ...
    for(k3d::mesh::primitives_t::const_iterator primitive = Input.primitives.begin(); primitive != Input.primitives.end(); ++primitive)
    {
        boost::scoped_ptr<k3d::polyhedron::const_primitive> polyhedron(k3d::polyhedron::validate(Input, **primitive));
        if(!polyhedron)
        {
            Output.primitives.push_back(*primitive);
            continue;
        }

        // Convert polyhedron to a QSlim model ...
        boost::scoped_ptr<MxStdModel> model(convert(Output, *polyhedron));

        //const k3d::int32_t face_number = std::max(0, std::min(static_cast<k3d::int32_t>(model->face_count()), face_count));

        boost::scoped_ptr<MxQSlim> slim;
        switch(contraction_type)
        {
            case EDGE:
                slim.reset(new MxEdgeQSlim(*model));
                break;
            case FACE:
                slim.reset(new MxFaceQSlim(*model));
                break;
        }

        switch(placement_policy)
        {
            case ENDPOINTS:
                slim->placement_policy = 0;
                break;
            case ENDORMID:
                slim->placement_policy = 1;
                break;
            case LINE:
                slim->placement_policy = 2;
                break;
            case OPTIMAL:
                slim->placement_policy = 3;
                break;
        }

        slim->boundary_weight = boundary_weight;

        switch(quadric_weighting)
        {
            case UNIFORM:
                slim->weighting_policy = 0;
                break;
            case AREA:
                slim->weighting_policy = 1;
                break;
            case ANGLE:
                slim->weighting_policy = 2;
                break;
        }

        slim->compactness_ratio = compactness_ratio;
        slim->meshing_penalty = meshing_penalty;
        slim->will_join_only = false;

        // Make it happen ...
        slim->initialize();
        slim->decimate(face_count);

        append(*polyhedron, *model, Output, material);
    }

    k3d::mesh::bools_t unused_points;
    k3d::mesh::lookup_unused_points(Output, unused_points);
    k3d::mesh::delete_points(Output, unused_points);

    return EXIT_NORMAL;
  }
};

EXPORT_METHOD(QSlim,createMesh);
