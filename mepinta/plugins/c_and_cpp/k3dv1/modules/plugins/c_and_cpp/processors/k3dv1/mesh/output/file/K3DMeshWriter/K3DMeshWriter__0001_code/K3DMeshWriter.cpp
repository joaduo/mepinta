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
        Code based on the K3DMeshWriter plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/MeshWriterBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/c/boehm_gc/charp/charp.h>

#include <k3dsdk/data.h>
#include <k3dsdk/dependencies.h>
#include <k3dsdk/file_helpers.h>
#include <k3dsdk/fstream.h>
#include <k3dsdk/persistent_lookup.h>
#include <k3dsdk/serialization_xml.h>

class K3DMeshWriter:
  public k3d::MPExtension::plugins::processors::mesh::MeshWriterBase
{
private:
    int writeMesh(const k3d::mesh& Input, const k3d::filesystem::path& OutputPath, std::ostream& Output){
      const k3d::filesystem::path root_path(OutputPath.branch_path());
      k3d::dependencies dependencies;
      k3d::persistent_lookup lookup;
      k3d::ipersistent::save_context context(root_path, dependencies, lookup);

      k3d::xml::element xml("k3dml");
      k3d::xml::element& xml_mesh = xml.append(k3d::xml::element("mesh_arrays"));
      k3d::xml::save(Input, xml_mesh, context);

      Output << k3d::xml::declaration() << xml;
      return EXIT_NORMAL;
    }
};

EXPORT_METHOD(K3DMeshWriter,writeMesh);
