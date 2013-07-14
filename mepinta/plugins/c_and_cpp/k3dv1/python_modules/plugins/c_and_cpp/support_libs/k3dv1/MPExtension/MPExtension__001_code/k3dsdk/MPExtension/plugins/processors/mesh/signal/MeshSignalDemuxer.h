

#ifndef MESHSIGNALDEMUXER_H_
#define MESHSIGNALDEMUXER_H_

#include "MeshSignal.h"
#include <k3dsdk/mesh.h>

namespace k3d {
namespace MPExtension {
namespace plugins {
namespace processors {
namespace mesh {

  class MeshSignalDemuxer
  {
  public:
    MeshSignalDemuxer():
      last_topology_changed_id(0),
      last_mesh(NULL)
    {}

    mesh_msg_t demuxSignal(k3d::mesh& Input);

  private:
    MeshSignal& getSignalFromMesh(k3d::mesh& Input);

    int last_topology_changed_id;
    k3d::mesh* last_mesh;
  };

}
}
}
}
}

#endif /* SIGNALDEMUXER_H_ */
