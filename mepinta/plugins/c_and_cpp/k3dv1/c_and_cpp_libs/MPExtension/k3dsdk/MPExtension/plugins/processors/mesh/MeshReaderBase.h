/*
 * MeshReader.h
 *
 *  Created on: Jul 31, 2012
 *      Author: jduo
 */

#ifndef MESHREADER_H_
#define MESHREADER_H_

#include <mepintasdk/sdk.h>
#include <k3dsdk/MPExtension/plugins/processors/base/ProcessorBase.h>
#include <k3dsdk/mesh.h>
#include <k3dsdk/imaterial.h>
#include <k3dsdk/path.h>

namespace k3d {
namespace MPExtension {
namespace plugins {
namespace processors {
namespace mesh {
  class MeshReaderBase:
    public k3d::MPExtension::plugins::processors::base::ProcessorBase
  {
  public:
    //Unpacks args when creating vertices, edges and faces
    int loadMesh_unpackAndRun(){
      OUTPUT(k3d::mesh*,mesh,args);
      INPUT(k3d::imaterial*,material,args);
      INPUT(char*,file,args);
      //INPUT(filesystem::path*,file,args); //TODO add filesystem::path data type
      const k3d::ustring NativePath = k3d::ustring::from_utf8(k3d::string_t(file));
      const k3d::filesystem::path Path = k3d::filesystem::native_path(NativePath);

      //Check file existence
      if(!filesystem::exists(Path))
      {
        log() << warning << "filesystem path " << Path.native_console_string() << " doesn't exist" << std::endl;
        return EXIT_NORMAL;
      }

      //Run the plugin code
      try{
        return loadMesh(Path, *mesh, material);
      }
      catch(...){
        log_error("An unhandled exception occurred while loading the mesh.\n");
        return EXIT_ERROR_UNHANDLED_EXCEPTION;
      }
    }

  private:
    //Called when loading the 3d mesh file
    virtual int loadMesh(const k3d::filesystem::path& Path, k3d::mesh& Output, k3d::imaterial* material) = 0;
  };
}
}
}
}
}

#endif /* MESHREADER_H_ */
