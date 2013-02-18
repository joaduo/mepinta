/*
 * MeshReader.h
 *
 *  Created on: Jul 31, 2012
 *      Author: jduo
 */

#ifndef MESHREADER_H_
#define MESHREADER_H_

#include <k3dsdk/MPExtension/plugins/processors/base/ProcessorBase.h>
#include <k3dsdk/mesh.h>
#include <k3dsdk/imaterial.h>
#include <k3dsdk/path.h>
#include <k3dsdk/fstream.h>

namespace k3d {
namespace MPExtension {
namespace plugins {
namespace processors {
namespace mesh {
  class MeshWriterBase:
    public k3d::MPExtension::plugins::processors::base::ProcessorBase
  {
  public:
    //Unpacks args when creating vertices, edges and faces
    int writeMesh_unpackAndRun(){
      INPUT(k3d::mesh*,mesh,args);
      INPUT(char*,file,args);
      //INPUT(filesystem::path*,file,args); //TODO add filesystem::path data type
      const k3d::ustring NativePath = k3d::ustring::from_utf8(k3d::string_t(file));
      const k3d::filesystem::path path = k3d::filesystem::native_path(NativePath);

      if(!mesh || path.empty()){
        log_debug("No mesh or file path empy.\n");
        return EXIT_NORMAL;
      }


      log() << info << "Writing " << path.native_console_string() << std::endl;
      k3d::filesystem::ofstream stream(path);
      if(!stream){
        k3d::log() << error << k3d_file_reference << ": error opening [" << path.native_console_string() << "] for writing." << std::endl;
        return EXIT_NORMAL;
      }

      #if 0
      //Review this
      if(!mesh->points){
        log_debug("Empty mesh, skipping writing.\n");
        return EXIT_NORMAL;
      }
      #endif

      return writeMesh(*mesh, path, stream);
    }

  private:
    //Called when writing the 3d mesh file
    virtual int writeMesh(const k3d::mesh& Input, const k3d::filesystem::path& OutputPath, std::ostream& Output) = 0;
  };

}
}
}
}
}

#endif /* MESHREADER_H_ */
