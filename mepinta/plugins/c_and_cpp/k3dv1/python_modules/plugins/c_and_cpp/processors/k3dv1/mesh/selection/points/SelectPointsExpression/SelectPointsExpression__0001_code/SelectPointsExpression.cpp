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
        Code based on the SelectPointsExpression plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <mepintasdk/cpp/TypedPropertiesCollector.h>
#include <mepintasdk/cpp/TypedCollectorManager.h>
#include <mepintasdk/cpp/expression/append_variable.h>

#include <k3dsdk/MPExtension/plugins/processors/mesh/SimpleGeometryModifierBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/cpp/std/string/string.h>
#include <data_types/mepinta/functum/functum.h>
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/c/builtin/double/double.h>
#include <data_types/c/builtin/int/int.h>

#include <k3dsdk/expression/parser.h>


class SelectPointsExpression:
  public k3d::MPExtension::plugins::processors::mesh::SimpleGeometryModifierBase
{
private:
  //Update the mesh geometry
  int updateMesh(k3d::mesh& Input, k3d::mesh& Output ){
    //Declare inputs
    INPUT(k3d::double_t,max_value,args)
    INPUT_REF(k3d::string_t,previous_selection_name, args);
    INPUT(k3d::double_t,time,args);                  TypedPropertiesCollector<k3d::double_t> values_collector(args);
    INPUT_REF(k3d::string_t,time_name, args);
    INPUT(k3d::int32_t,use_max_value,args);
    INPUT_REF(k3d::string_t,vertex_index_name,args);
    INPUT_REF(k3d::string_t,weight_expression,args); TypedPropertiesCollector<k3d::string_t> variables_collector(args);

    //Create the collector
    TypedCollectorManager collector_manager(args);

    collector_manager.appendCollector(&values_collector);
    collector_manager.appendCollector(&variables_collector);
    collector_manager.collectProperties();

    k3d::string_t variables("x,y,z");
    k3d::uint_t variables_count = 3;
    std::vector<k3d::double_t> values(3, 0.0);
    const k3d::uint_t use_selection = append_variable(previous_selection_name,variables,values,0.0);
    variables_count += use_selection;
    const k3d::uint_t use_vertex_index = append_variable(vertex_index_name,variables,values,0.0);
    variables_count += use_vertex_index;
    variables_count += append_variable(time_name,variables,values,time);

    k3d::uint_t end_size = std::min(variables_collector.properties.size(),values_collector.properties.size());
    k3d::uint_t custom_variables_count = 0;
    for(k3d::uint_t i=0; i < end_size ; ++i){
      custom_variables_count += append_variable(variables_collector.properties[i],variables,values,values_collector.properties[i]);
    }
    variables_count += custom_variables_count;

    //Do some health checking
    ASSERT_DEBUG_RETURN(values.size() == variables_count, EXIT_FAILURE);

    //Give the user some idea of what's happening
    if(variables_collector.properties.size() != values_collector.properties.size()){
      log_info("Mismatch in amount of custom variables and custom values. Evaluating anyway.\n");
    }
    if(variables_collector.properties.size() != custom_variables_count){
      log_info("Some variables don't have a name, ignoring them. Evaluating anyway.\n");
    }

    k3d::expression::parser parser_weight;
    if(!parser_weight.parse(weight_expression, variables))
    {
      k3d::log() << error << ": function parsing for selection expression failed: " << parser_weight.last_parse_error() << std::endl;
      return EXIT_NORMAL;
    }

    if(Output.point_selection && Output.point_selection->size() == Output.points->size()){
      //Get the working selection
      k3d::mesh::selection_t& output_selection = Output.point_selection.writable();
      //Input points selection will be used if the previous selection is used in the expression
      const k3d::mesh::selection_t& input_selection = *Input.point_selection;
      k3d::mesh::points_t& OutputPoints = Output.points.writable();
      //For each point evaluate the selection expression
      const k3d::uint_t point_begin = 0;
      const k3d::uint_t point_end = point_begin + Output.points->size();
      for(k3d::uint_t point = point_begin; point != point_end; ++point)
      {
        values[0] = OutputPoints[point].n[0];
        values[1] = OutputPoints[point].n[1];
        values[2] = OutputPoints[point].n[2];
        if(use_selection & use_vertex_index){
          values[3] = input_selection[point];
          values[4] = (double)point;
        }
        else if(use_selection){
          values[3] = input_selection[point];
        }
        else if(use_vertex_index){
          values[3] = (double)point;
        }

        if(use_max_value){
          output_selection[point] = std::min(parser_weight.evaluate(&values[0]),max_value);
        }
        else{
          output_selection[point] = parser_weight.evaluate(&values[0]);
        }
      }
    }
    else{
      k3d::log() << error << "There is no selection or selection doesn't match points' size." << std::endl;
    }

    return EXIT_NORMAL;
  }
};

EXPORT_METHOD(SelectPointsExpression,demuxMeshSignal);
EXPORT_METHOD(SelectPointsExpression,updateMesh);
