//Mepinta
//Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar
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

#ifndef TYPEDCOLLECTORMANAGER_H_
#define TYPEDCOLLECTORMANAGER_H_

#include <mepintasdk/sdk.h>
#include "iTypedPropertiesCollector.h"
#include <vector>

//This class is used to collect properties with multiple types.
//Append many TypedPropertiesCollect instances and then run collectProperties.
//This will avoid looping on the properties for each type.
class TypedCollectorManager{
public:
  //args: Mepinta args
  //in_out_id: INPUT_PROPS, OUTPUT_PROPS //TODO: INPUT_OUTPUT_PROPS
  //last_prop_index: the last_prop_index of the declared variables
  // if it's -1 it will get the one from args
  TypedCollectorManager(MP_args* args, const int in_out_id=CUSTOM_INPUT_PROPS):
    args(args),in_out_id(in_out_id),first_prop_index(0) {}

  //append a TypedPropertiesCollector for a specific type
  void appendCollector(iTypedPropertiesCollector* collector);

  //pop the last TypedPropertiesCollector added
  iTypedPropertiesCollector* popCollector();

  //iterate over the properties to filter then for each required type
  int collectProperties();

private:
  //Typed Collectors added
  std::vector<iTypedPropertiesCollector*> collectors;
  //processor args
  MP_args* args;
  //Are we processing the inputs or the outputs (default is inputs)
  int in_out_id;
  //Where do we start to visit the properties?
  int first_prop_index;
};

#endif /* TYPEDCOLLECTORMANAGER_H_ */
