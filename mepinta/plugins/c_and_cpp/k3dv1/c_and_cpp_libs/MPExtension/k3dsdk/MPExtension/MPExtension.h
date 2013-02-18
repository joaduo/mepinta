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

#ifndef MPEXTENSION_H_
#define MPEXTENSION_H_

#include <k3dsdk/mesh.h>

#define mesh_updated(mesh) false

namespace k3d {
  class UpdateTopologyGeometry{
  public:
    //Check if mesh need to update topology or reset the whole mesh
    void update_reset_output(const mesh& Input, mesh& Output);
  private:
    //Update topology
    void update_output(const mesh& Input, mesh& Output);
  };
}

#endif /* MPEXTENSION_H_ */
