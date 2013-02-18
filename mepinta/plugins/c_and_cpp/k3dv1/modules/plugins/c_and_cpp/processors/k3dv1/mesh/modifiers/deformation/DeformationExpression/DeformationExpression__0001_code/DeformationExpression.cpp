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
        Code based on the DeformationExpression plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/SimpleDeformationModifierBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>
#include <k3dsdk/MPExtension/expression/parse_expression.h>
#include <mepintasdk/cpp/TypedPropertiesCollector.h>
#include <mepintasdk/cpp/TypedCollectorManager.h>
#include <mepintasdk/cpp/expression/append_variable.h>

//Included Data Types
#include <data_types/cpp/std/string/string.h>
#include <data_types/mepinta/functum/functum.h>
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/c/builtin/double/double.h>

#include <k3dsdk/expression/parser.h>

class DeformationExpression:
  public k3d::MPExtension::plugins::processors::mesh::SimpleDeformationModifierBase
{
private:
  int deformMesh(const k3d::mesh::points_t& InputPoints, const k3d::mesh::selection_t& PointSelection, k3d::mesh::points_t& OutputPoints)
  {
    //Declare Inputs
    INPUT_REF(k3d::string_t,selection_name,args);
    INPUT(k3d::double_t,time,args);                    TypedPropertiesCollector<k3d::double_t> values_collector(args);
    INPUT_REF(k3d::string_t,time_name,args);
    INPUT_REF(k3d::string_t,vertex_index_name,args);
    INPUT_REF(k3d::string_t,x_function,args);
    INPUT_REF(k3d::string_t,y_function,args);
    INPUT_REF(k3d::string_t,z_function,args);   TypedPropertiesCollector<k3d::string_t*> variables_collector(args);

    //Collecting inputs, then declare the collector after all the inputs
    TypedCollectorManager collector_manager(args);
    collector_manager.appendCollector(&values_collector);
    collector_manager.appendCollector(&variables_collector);
    collector_manager.collectProperties();

    std::string variables("x,y,z");
    uint variables_count = 3;
    std::vector<k3d::double_t> values(3, 0.0);
    const uint use_selection = append_variable(selection_name,variables,values,0.0);
    variables_count += use_selection;
    const uint use_vertex_index = append_variable(vertex_index_name,variables,values,0.0);
    variables_count += use_vertex_index;
    variables_count += append_variable(time_name,variables,values,time);

    std::vector<k3d::string_t*> &collected_variables = *variables_collector.getPropertiesRef();
    std::vector<double> &collected_values = *values_collector.getPropertiesRef();
    k3d::uint_t end_size = std::min(collected_variables.size(),collected_values.size());
    k3d::uint_t custom_variables_count = 0;
    for(k3d::uint_t i=0; i < end_size ; ++i){
      custom_variables_count += append_variable(*collected_variables[i],variables,values,collected_values[i]);
    }
    variables_count += custom_variables_count;

    //Do some health checking
    ASSERT_DEBUG_RETURN(values.size() == variables_count, EXIT_FAILURE);

    //Give the user some idea if there is something unormal
    if(collected_variables.size() != collected_values.size()){
      log_info("Mismatch in amount of custom variables(%d) and custom values(%d). Evaluating anyway.\n",
                                    collected_variables.size(), collected_values.size());
    }
    if(collected_variables.size() != custom_variables_count){
      log_info("Some variables don't have a name, ignoring them. Evaluating anyway.\n");
    }

    //Declare parser used to determine a point's position
    k3d::expression::parser parser_x_component;
    k3d::expression::parser parser_y_component;
    k3d::expression::parser parser_z_component;

    //Parse expressions with given functions and variables. Exit on parse error
    ASSERT_RETURN( parse_expression("x", parser_x_component, x_function, variables), EXIT_NORMAL);
    ASSERT_RETURN( parse_expression("y", parser_y_component, y_function, variables), EXIT_NORMAL);
    ASSERT_RETURN( parse_expression("z", parser_z_component, z_function, variables), EXIT_NORMAL);

    //Copy input points to the output
    OutputPoints = InputPoints;

    //Evaluate functions for each point.
    const k3d::uint_t point_begin = 0;
    const k3d::uint_t point_end = point_begin + OutputPoints.size();
    if(use_selection){ //Use the selection as a value for the expression
      for(k3d::uint_t point = point_begin; point != point_end; ++point)
      {
        values[0] = OutputPoints[point].n[0];
        values[1] = OutputPoints[point].n[1];
        values[2] = OutputPoints[point].n[2];
        values[3] = PointSelection[point];
        if(use_vertex_index)
          values[4] = (double)point;

        OutputPoints[point] = k3d::point3(
                                  parser_x_component.evaluate(&values[0]),
                                  parser_y_component.evaluate(&values[0]),
                                  parser_z_component.evaluate(&values[0])
                                );
      }
    }
    else{//Selection is not integrated in the expression
      for(k3d::uint_t point = point_begin; point != point_end; ++point)
      {
        k3d::double_t selection = PointSelection[point];
        if(!selection) //simple optimization
          continue;

        values[0] = OutputPoints[point].n[0];
        values[1] = OutputPoints[point].n[1];
        values[2] = OutputPoints[point].n[2];
        if(use_vertex_index)
          values[3] = (double)point;

        //Adding selection for consistency with optimization
        OutputPoints[point] += selection * (k3d::point3(
                                  parser_x_component.evaluate(&values[0]),
                                  parser_y_component.evaluate(&values[0]),
                                  parser_z_component.evaluate(&values[0])
                                ) - OutputPoints[point]);
      }
    }

    return EXIT_NORMAL;
  }
};

EXPORT_METHOD(DeformationExpression,demuxMeshSignal);
EXPORT_METHOD(DeformationExpression,deformMesh);
