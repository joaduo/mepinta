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
        Code based on the ##pluginName plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/SimpleDeformationModifierBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>
##cppIncludes

namespace k3d{
##genericEnums
}

class ##pluginName:
  public k3d::MPExtension::plugins::processors::mesh::SimpleDeformationModifierBase
{
private:
  virtual int deformMesh(const k3d::mesh::points_t& InputPoints, const k3d::mesh::selection_t& PointSelection, k3d::mesh::points_t& OutputPoints){

    return EXIT_NORMAL;
  }
};

##processorFunctions

EXPORT_METHOD(##pluginName,demuxMeshSignal);
EXPORT_METHOD(##pluginName,deformMesh);
