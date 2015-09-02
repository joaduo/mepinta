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
        Code based on the PolyCube plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/MeshSourceBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/k3dv1/imaterial/imaterial.h>
#include <data_types/c/builtin/int/int.h>
#include <data_types/c/builtin/double/double.h>

#include <k3dsdk/log.h>
#include <k3dsdk/polyhedron.h>
#include <k3dsdk/types.h>

#include <boost/scoped_ptr.hpp>

class PolyCube:
  public k3d::MPExtension::plugins::processors::mesh::MeshSourceBase
{
private:
  //Called when creating vertices, edges and faces
  int updateMeshTopology(k3d::mesh& Output, k3d::imaterial* material){
    //Declare Inputs
    INPUT_VALIDATED_DEFAULT(k3d::int32_t,columns,args, columns > 0,1);
    INPUT_VALIDATED_DEFAULT(k3d::int32_t,rows,args, rows > 0,1);
    INPUT_VALIDATED_DEFAULT(k3d::int32_t,slices,args, slices > 0,1);

    Output = k3d::mesh();

    const k3d::int32_t point_columns = columns + 1;
    const k3d::int32_t point_slices = slices + 1;

    const k3d::int32_t circumference = 2 * (rows + columns);
    const k3d::int32_t cylinder_point_count = point_slices * circumference;
    const k3d::int32_t cap_point_count = (rows - 1) * (columns - 1);

    // We model a cube as a cylinder ...
    boost::scoped_ptr<k3d::polyhedron::primitive> polyhedron(k3d::polyhedron::create(Output));

    polyhedron->shell_types.push_back(k3d::polyhedron::POLYGONS);
    k3d::polyhedron::add_cylinder(Output, *polyhedron, 0, slices, circumference, material);

    k3d::mesh::points_t& points = Output.points.writable();
    k3d::mesh::selection_t& point_selection = Output.point_selection.writable();

    // Create the cube "top" points ...
    points.insert(points.end(), cap_point_count, k3d::point3());
    point_selection.insert(point_selection.end(), cap_point_count, 0);

    // Create a lookup table to simplify creating the "top" faces ...
    k3d::mesh::indices_t top_map;
    for(k3d::int32_t column = 0; column != point_columns; ++column)
            top_map.push_back(columns - column);

    for(k3d::int32_t row = 1; row != rows; ++row)
    {
            top_map.push_back(columns + row);

            for(k3d::int32_t column = 1; column != columns; ++column)
                    top_map.push_back(cylinder_point_count + ((row - 1) * (columns - 1)) + (column - 1));

            top_map.push_back(circumference - row);
    }

    for(k3d::int32_t column = 0; column != point_columns; ++column)
            top_map.push_back(column + columns + rows);

    // Create the "top" faces ...
    for(k3d::int32_t row = 0; row != rows; ++row)
    {
            for(k3d::int32_t column = 0; column != columns; ++column)
            {
                    k3d::polyhedron::add_quadrilateral(
                            Output,
                            *polyhedron,
                            0,
                            top_map[(row + 0) * point_columns + (column + 0)],
                            top_map[(row + 0) * point_columns + (column + 1)],
                            top_map[(row + 1) * point_columns + (column + 1)],
                            top_map[(row + 1) * point_columns + (column + 0)],
                            material);
            }
    }

    // Create the cube "bottom" points ...
    points.insert(points.end(), cap_point_count, k3d::point3());
    point_selection.insert(point_selection.end(), cap_point_count, 0);

    // Create a lookup table to simplify creating the "bottom" faces ...
    k3d::mesh::indices_t bottom_map;
    for(k3d::int32_t column = 0; column != point_columns; ++column)
            bottom_map.push_back((slices * circumference) + column);

    for(k3d::int32_t row = 1; row != rows; ++row)
    {
            bottom_map.push_back((slices * circumference) + circumference - row);

            for(k3d::int32_t column = 1; column != columns; ++column)
                    bottom_map.push_back(cylinder_point_count + cap_point_count + ((row - 1) * (columns - 1)) + (column - 1));

            bottom_map.push_back((slices * circumference) + columns + row);
    }

    for(k3d::int32_t column = 0; column != point_columns; ++column)
            bottom_map.push_back((slices * circumference) + columns + rows + columns - column);

    // Create the "bottom" faces ...
    for(k3d::int32_t row = 0; row != rows; ++row)
    {
            for(k3d::int32_t column = 0; column != columns; ++column)
            {
                    k3d::polyhedron::add_quadrilateral(
                            Output,
                            *polyhedron,
                            0,
                            bottom_map[(row + 0) * point_columns + (column + 0)],
                            bottom_map[(row + 0) * point_columns + (column + 1)],
                            bottom_map[(row + 1) * point_columns + (column + 1)],
                            bottom_map[(row + 1) * point_columns + (column + 0)],
                            material);
            }
    }

    return EXIT_NORMAL;
  }
  
  //Called when updating the vertices positions
  int updateMeshGeometry(k3d::mesh& Output){
    //Declare Inputs
    INPUT_VALIDATED_DEFAULT(k3d::int32_t,columns,args, columns > 0,1);
    INPUT_VALIDATED_DEFAULT(k3d::int32_t,rows,args, rows > 0,1);
    INPUT_VALIDATED_DEFAULT(k3d::int32_t,slices,args, slices > 0,1);
    INPUT(k3d::double_t,width,args);
    INPUT(k3d::double_t,height,args);
    INPUT(k3d::double_t,depth,args);

    const k3d::int32_t circumference = 2 * (rows + columns);
    const k3d::int32_t cylinder_point_count = (slices + 1) * circumference;
    const k3d::int32_t cap_point_count = (rows - 1) * (columns - 1);

    k3d::mesh::points_t& points = Output.points.writable();

    // Create a mapping from an index around the "circumference" of the cube to point coordinates
    k3d::mesh::points_t square_map;
    for(k3d::int32_t i = 0; i != columns; ++i)
    {
            square_map.push_back(
                    k3d::point3(k3d::mix(-width/2, width/2, k3d::ratio(i, columns)), height/2, 0));
    }
    for(k3d::int32_t i = 0; i != rows; ++i)
    {
            square_map.push_back(
                    k3d::point3(width/2, k3d::mix(height/2, -height/2, k3d::ratio(i, rows)), 0));
    }
    for(k3d::int32_t i = 0; i != columns; ++i)
    {
            square_map.push_back(
                    k3d::point3(k3d::mix(width/2, -width/2, k3d::ratio(i, columns)), -height/2, 0));
    }
    for(k3d::int32_t i = 0; i != rows; ++i)
    {
            square_map.push_back(
                    k3d::point3(-width/2, k3d::mix(-height/2, height/2, k3d::ratio(i, rows)), 0));
    }

    // Assign coordinates to the "body" of the cube ...
    for(k3d::int32_t i = 0; i <= slices; ++i)
    {
            const k3d::vector3 offset(0, 0, k3d::mix(depth/2, -depth/2, k3d::ratio(i, slices)));
            for(k3d::int32_t j = 0; j != circumference; ++j)
            {
                    points[(i * circumference) + j] = offset + square_map[j];
            }
    }

    // Assign coordinates to the top of the cube ...
    for(k3d::int32_t row = 1; row < rows; ++row)
    {
            for(k3d::int32_t column = 1; column < columns; ++column)
            {
                    points[cylinder_point_count + ((row - 1) * (columns - 1)) + (column - 1)] =
                            k3d::point3(
                                    k3d::mix(width/2, -width/2, k3d::ratio(column, columns)),
                                    k3d::mix(height/2, -height/2, k3d::ratio(row, rows)),
                                    depth/2);
            }
    }

    // Assign coordinates to the bottom of the cube ...
    for(k3d::int32_t row = 1; row < rows; ++row)
    {
            for(k3d::int32_t column = 1; column < columns; ++column)
            {
                    points[cylinder_point_count + cap_point_count + ((row - 1) * (columns - 1)) + (column - 1)] =
                            k3d::point3(
                                    k3d::mix(-width/2, width/2, k3d::ratio(column, columns)),
                                    k3d::mix(height/2, -height/2, k3d::ratio(row, rows)),
                                    -depth/2);
            }
    }

    return EXIT_NORMAL;
  }
};

EXPORT_METHOD(PolyCube,updateMeshTopology);
EXPORT_METHOD(PolyCube,updateMeshGeometry);
