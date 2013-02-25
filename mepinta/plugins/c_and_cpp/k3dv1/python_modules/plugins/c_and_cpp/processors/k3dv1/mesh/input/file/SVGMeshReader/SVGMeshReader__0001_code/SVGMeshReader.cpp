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
        Code based on the SVGMeshReader plugin of the K-3D project.
*/

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/mesh/MeshReaderBase.h>
#include <k3dsdk/MPExtension/plugins/export_method.h>

//Included Data Types
#include <data_types/k3dv1/imaterial/imaterial.h>
#include <data_types/k3dv1/mesh/mesh.h>
#include <data_types/c/boehm_gc/charp/charp.h>

#include <k3dsdk/fstream.h>
#include <k3dsdk/nurbs_curve.h>
#include <k3dsdk/xml.h>

#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>

#include <stack>

#include "svg_parsing.h"

using namespace svg_parsing;

class SVGMeshReader:
  public k3d::MPExtension::plugins::processors::mesh::MeshReaderBase
{
private:
  int loadMesh(const k3d::filesystem::path& Path, k3d::mesh& Mesh, k3d::imaterial* material){
    try
    {
      k3d::filesystem::ifstream svg_stream(Path);
      k3d::xml::element svg;
      svg_stream >> svg;

      if(svg.name != "svg")
              throw std::runtime_error("Not an SVG file.");

      transform_stack transformation;
      transformation.push(k3d::identity3());

      //k3d::mesh::points_t& points = Mesh.points.create();
      //k3d::mesh::selection_t& point_selection = Mesh.point_selection.create();

      boost::scoped_ptr<k3d::nurbs_curve::primitive> primitive(k3d::nurbs_curve::create(Mesh));
      primitive->material.push_back(material);

      parse_graphics(svg, transformation, Mesh, *primitive);
    }
    catch(std::exception& e)
    {
      k3d::log() << error << "Caught exception: " << e.what() << std::endl;
    }
    catch(...)
    {
      k3d::log() << error << "Unknown exception" << std::endl;
    }
    return EXIT_NORMAL;
  }
};

EXPORT_METHOD(SVGMeshReader,loadMesh);
