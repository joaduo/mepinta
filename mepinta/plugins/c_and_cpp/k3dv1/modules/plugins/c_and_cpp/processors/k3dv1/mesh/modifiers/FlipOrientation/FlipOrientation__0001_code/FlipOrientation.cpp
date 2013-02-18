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
        Code based on the FlipOrientation plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/MeshModifierBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/mepinta/functum/functum.h>
#include <data_types/k3dv1/mesh/mesh.h>

#include <k3dsdk/bicubic_patch.h>
#include <k3dsdk/bilinear_patch.h>
#include <k3dsdk/polyhedron.h>
#include <boost/scoped_ptr.hpp>

namespace detail
{

void flip_polyhedron(k3d::polyhedron::primitive& Output, const k3d::polyhedron::const_primitive& Input)
{
        const k3d::uint_t edge_count = Input.clockwise_edges.size();
        k3d::mesh::indices_t counter_clockwise_edges(edge_count);
        for(k3d::uint_t edge = 0; edge != edge_count; ++edge)
        {
                counter_clockwise_edges[Input.clockwise_edges[edge]] = edge;
        }
        for(k3d::uint_t face = 0; face != Input.face_first_loops.size(); ++face)
        {
                if(!Output.face_selections[face])
                        continue;
                const k3d::uint_t loop_begin = Input.face_first_loops[face];
                const k3d::uint_t loop_end = loop_begin + Input.face_loop_counts[face];
                for(k3d::uint_t loop = loop_begin; loop != loop_end; ++loop)
                {
                        const k3d::uint_t first_edge = Input.loop_first_edges[loop];
                        for(k3d::uint_t edge = first_edge; ;)
                        {
                                Output.vertex_points[edge] = Input.vertex_points[Input.clockwise_edges[edge]];
                                Output.clockwise_edges[edge] = counter_clockwise_edges[edge];

                                edge = Input.clockwise_edges[edge];
                                if(edge == first_edge)
                                        break;
                        }
                }
        }
}

void flip_bilinear_patch(k3d::bilinear_patch::primitive& Output)
{
        for(k3d::uint_t patch = 0; patch != Output.patch_selections.size(); ++patch)
        {
                if(!Output.patch_selections[patch])
                        continue;
                const k3d::uint_t patch_start = 4*patch;
                std::swap(Output.patch_points[patch_start], Output.patch_points[patch_start + 1]);
                std::swap(Output.patch_points[patch_start + 2], Output.patch_points[patch_start + 3]);
        }
}

void flip_bicubic_patch(k3d::bicubic_patch::primitive& Output)
{
        for(k3d::uint_t patch = 0; patch != Output.patch_selections.size(); ++patch)
        {
                if(!Output.patch_selections[patch])
                        continue;
                const k3d::uint_t patch_start = 16*patch;
                std::swap(Output.patch_points[patch_start], Output.patch_points[patch_start + 3]);
                std::swap(Output.patch_points[patch_start + 1], Output.patch_points[patch_start + 2]);
                std::swap(Output.patch_points[patch_start + 4], Output.patch_points[patch_start + 7]);
                std::swap(Output.patch_points[patch_start + 5], Output.patch_points[patch_start + 6]);
                std::swap(Output.patch_points[patch_start + 8], Output.patch_points[patch_start + 11]);
                std::swap(Output.patch_points[patch_start + 9], Output.patch_points[patch_start + 10]);
                std::swap(Output.patch_points[patch_start + 12], Output.patch_points[patch_start + 15]);
                std::swap(Output.patch_points[patch_start + 13], Output.patch_points[patch_start + 14]);
        }
}

} // namespace detail

class FlipOrientation:
  public k3d::MPExtension::plugins::processors::mesh::MeshModifierBase
{
private:
  int createMesh(k3dv1::mesh &Input, k3dv1::mesh &Output){
    //Copy input into output
    Output= Input;

    //Iterate over primitives, flip those supported
    for(k3d::uint_t i = 0; i != Input.primitives.size(); ++i)
    {
            boost::scoped_ptr<k3d::polyhedron::const_primitive> input_polyhedron(k3d::polyhedron::validate(Input, *Input.primitives[i]));
            boost::scoped_ptr<k3d::bilinear_patch::const_primitive> input_bilinear_patch(k3d::bilinear_patch::validate(Input, *Input.primitives[i]));
            boost::scoped_ptr<k3d::bicubic_patch::const_primitive> input_bicubic_patch(k3d::bicubic_patch::validate(Input, *Input.primitives[i]));
            if(input_polyhedron)
            {
                    boost::scoped_ptr<k3d::polyhedron::primitive> output_polyhedron(k3d::polyhedron::validate(Output, Output.primitives[i]));
                    ASSERT_RETURN(output_polyhedron, EXIT_NORMAL);
                    detail::flip_polyhedron(*output_polyhedron, *input_polyhedron);
            }
            else if(input_bilinear_patch)
            {
                    boost::scoped_ptr<k3d::bilinear_patch::primitive> output_patch(k3d::bilinear_patch::validate(Output, Output.primitives[i]));
                    ASSERT_RETURN(output_patch,EXIT_NORMAL);
                    detail::flip_bilinear_patch(*output_patch);
            }
            else if(input_bicubic_patch)
            {
                    boost::scoped_ptr<k3d::bicubic_patch::primitive> output_patch(k3d::bicubic_patch::validate(Output, Output.primitives[i]));
                    ASSERT_RETURN(output_patch,EXIT_NORMAL);
                    detail::flip_bicubic_patch(*output_patch);
            }
    }

    return EXIT_NORMAL;
  }

  int updateMesh(k3dv1::mesh &Input, k3dv1::mesh &Output){
    //Do nothing, moving the points won't affect
    return EXIT_NORMAL;
  }
};

EXPORT_METHOD(FlipOrientation,demuxMeshSignal);
EXPORT_METHOD(FlipOrientation,createMesh);
EXPORT_METHOD(FlipOrientation,updateMesh);
