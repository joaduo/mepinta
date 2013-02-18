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

#include "MPExtension.h"

namespace k3d {

  //Check if mesh need to update topology or reset the whole mesh
  void UpdateTopologyGeometry::update_reset_output(const mesh& Input, mesh& Output){
    if(!mesh_updated(Input)){
      Output = Input;
    }
    else{
      update_output(Input,Output);
    }
  }
  //Update topology
  void UpdateTopologyGeometry::update_output(const mesh& Input, mesh& Output)
  {
          if(!Input.points)
                  return;
          if(!Output.points)
                  return;
          return_if_fail(Input.points->size() == Output.points->size());

          return_if_fail(Output.point_selection);
          return_if_fail(Output.point_selection->size() == Output.points->size());

          //TODO: profiler "Copy points"
          //mesh::points_t& output_points =
          //Output.points.writable();
  }
}

