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
        Code based on the K3DMeshReader plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/MeshReaderBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/k3dv1/imaterial/imaterial.h>
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/c/boehm_gc/charp/charp.h>

#include <k3dsdk/data.h>
#include <k3dsdk/dependencies.h>
#include <k3dsdk/file_helpers.h>
#include <k3dsdk/fstream.h>
#include <k3dsdk/gzstream.h>
#include <k3dsdk/persistent_lookup.h>
#include <k3dsdk/serialization_xml.h>


class set_default_material
{
public:
        set_default_material(k3d::imaterial* Material) : m_material(Material) {}

        void operator()(const k3d::string_t&, const k3d::table&, const k3d::string_t& ArrayName, k3d::pipeline_data<k3d::array>& Array)
        {
                k3d::mesh::materials_t* const materials = dynamic_cast<k3d::mesh::materials_t*>(&Array.writable());
                if(!materials)
                {
                        return;
                }

                materials->assign(materials->size(), m_material);
        }

private:
        k3d::imaterial* m_material;
};

class K3DMeshReader:
  public k3d::MPExtension::plugins::processors::mesh::MeshReaderBase
{
private:
  int loadMesh(const k3d::filesystem::path& Path, k3d::mesh& Output, k3d::imaterial* material){
    Output = k3d::mesh();
    try
    {
      k3d::filesystem::igzstream file(Path);
      if(!file)
      {
        k3d::log() << error << k3d_file_reference << ": error opening [" << Path.native_console_string() << "]" << std::endl;
        return EXIT_NORMAL;
      }

      k3d::xml::element xml_document("k3dml");
      file >> xml_document;

      const k3d::filesystem::path root_path = Path.branch_path();
      k3d::persistent_lookup lookup;
      k3d::ipersistent::load_context context(root_path, lookup);

      if(k3d::xml::element* const xml_mesh_arrays = k3d::xml::find_element(xml_document, "mesh_arrays"))
              k3d::xml::load(Output, *xml_mesh_arrays, context);
    }
    catch(std::exception& e)
    {
            k3d::log() << error << k3d_file_reference << ": error opening [" << Path.native_console_string() << "]" << std::endl;
            k3d::log() << error << e.what() << std::endl;
            Output = k3d::mesh();
            return EXIT_NORMAL;
    }
    // Assign a default material
    k3d::mesh::visit_arrays(Output, set_default_material(material));
    return EXIT_NORMAL;
  }
};

EXPORT_METHOD(K3DMeshReader,loadMesh);
