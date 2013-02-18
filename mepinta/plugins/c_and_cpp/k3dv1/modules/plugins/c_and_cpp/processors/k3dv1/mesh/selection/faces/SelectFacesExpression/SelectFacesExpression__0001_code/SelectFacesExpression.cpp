/* Mepinta
  Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

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
        SelectFacesExpression plugin for K-3D.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/SimpleSelectExpressionBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>
#include <k3dsdk/MPExtension/expression/parse_expression.h>
#include <mepintasdk/cpp/iTypedPropertiesCollector.h>
#include <mepintasdk/cpp/TypedPropertiesCollector.h>
#include <mepintasdk/cpp/TypedCollectorManager.h>
#include <mepintasdk/cpp/expression/append_variable.h>

//Included Data Types
#include <data_types/cpp/std/string/string.h>
#include <data_types/mepinta/functum/functum.h>
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/c/builtin/double/double.h>
#include <data_types/c/builtin/int/int.h>

#include <k3dsdk/expression/parser.h>
#include <k3dsdk/polyhedron.h>
#include <boost/scoped_ptr.hpp>

class SelectFacesExpression:
  public k3d::MPExtension::plugins::processors::mesh::SimpleSelectExpressionBase
{
private:
  ///Updating the mesh selection
  int updateSelection(k3d::mesh& Input, k3d::mesh& Output ){
    //Declare Inputs
    INPUT_REF(k3d::string_t,face_index_name,args);
    INPUT(k3d::double_t,max_value,args);
    INPUT_REF(k3d::string_t,previous_selection_name,args);
    INPUT_REF(k3d::string_t,primitive_index_name,args);
    INPUT(k3d::double_t,time,args);                     TypedPropertiesCollector<double> values_collector(args);
    INPUT_REF(k3d::string_t,time_name,args);
    INPUT(k3d::int32_t,use_max_value,args);
    INPUT_REF(k3d::string_t,weight_expression,args);    TypedPropertiesCollector<k3d::string_t> variables_collector(args);

    //Collecting inputs, then declare the collector after all the inputs
    TypedCollectorManager collector_manager(args);
    collector_manager.appendCollector(&values_collector);
    collector_manager.appendCollector(&variables_collector);
    collector_manager.collectProperties();

    std::string variables("");
    uint variables_count = 0;
    std::vector<k3d::double_t> values(3, 0.0);
    const uint use_selection = append_variable(previous_selection_name,variables,values,0.0);
    variables_count += use_selection;
    const uint use_primitive_index = append_variable(primitive_index_name,variables,values,0.0);
    variables_count += use_primitive_index;
    const uint use_face_index = append_variable(face_index_name,variables,values,0.0);
    variables_count += use_face_index;
    variables_count += append_variable(time_name,variables,values,time);

    //Get the collected variables and do sanity checks
    std::vector<k3d::string_t> &collected_variables = *variables_collector.getPropertiesRef();
    std::vector<double> &collected_values = *values_collector.getPropertiesRef();
    k3d::uint_t end_size = std::min(collected_variables.size(),collected_values.size());
    k3d::uint_t custom_variables_count = 0;
    for(k3d::uint_t i=0; i < end_size ; ++i){
      custom_variables_count += append_variable(collected_variables[i],variables,values,collected_values[i]);
    }
    variables_count += custom_variables_count;

    //Do some health checking
    ASSERT_DEBUG_RETURN(values.size() == variables_count, EXIT_FAILURE);

    //Give the user some idea if there is something unormal
    if(collected_variables.size() != collected_values.size()){
      log_info("Mismatch in amount of custom variables and custom values. Evaluating anyway.\n");
    }
    if(collected_variables.size() != custom_variables_count){
      log_info("Some variables don't have a name, ignoring them. Evaluating anyway.\n");
    }

    //Parse expressions with given functions and variables. Exit on parse error
    k3d::expression::parser parser_weight;
    ASSERT_RETURN( parse_expression("face selection", parser_weight, weight_expression, variables), EXIT_NORMAL);

    //Set value indexes depending on the defined variables names
    k3d::uint_t value_index = 0;
    const k3d::uint_t selection_value_index = value_index;
    if(use_selection)
      ++value_index;

    const k3d::uint_t primitive_value_index = value_index;
    if(use_primitive_index)
      ++value_index;

    const k3d::uint_t face_value_index = value_index;

    //Iterate over primitives, flip those supported
    for(k3d::uint_t primitive_index = 0; primitive_index != Input.primitives.size(); ++primitive_index)
    {
      boost::scoped_ptr<k3d::polyhedron::const_primitive> input_polyhedron(k3d::polyhedron::validate(Input, *Input.primitives[primitive_index]));
      boost::scoped_ptr<k3d::polyhedron::primitive> output_polyhedron(k3d::polyhedron::validate(Output, Output.primitives[primitive_index]));
      if(!input_polyhedron | !output_polyhedron)
        continue;

      //Did the user put a name to the primitive index?
      if(use_primitive_index)
        values[primitive_value_index] = primitive_index; //Add the primitive index to the value list

      //better aliases
      k3d::mesh::selection_t & output_selection = output_polyhedron->face_selections;
      k3d::mesh::selection_t const & input_selection  = input_polyhedron->face_selections;
      //iterate over the polyhedron faces to select them
      for(k3d::uint_t face_index = 0; face_index != input_polyhedron->face_selections.size(); ++face_index){
        //Did the user put a name to the previous selection index?
        if(use_selection)
          values[selection_value_index] = input_selection[face_index]; //Add it to the values
        //Did the user put a name to the face index?
        if(use_face_index)
          values[face_value_index] = (double)face_index; //Add it to the values

        //Should we use a top value for selections (generally = 1.)
        if(use_max_value)
          output_selection[face_index] = std::min(parser_weight.evaluate(&values[0]),max_value);
        else
          output_selection[face_index] = parser_weight.evaluate(&values[0]);
      }
    }

    return EXIT_NORMAL;
  }
};

EXPORT_METHOD(SelectFacesExpression,demuxMeshSignal);
EXPORT_METHOD(SelectFacesExpression,updateSelection);
