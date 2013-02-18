

#ifndef SIGNALDEMUXER_H_
#define SIGNALDEMUXER_H_

#include "MeshSignalDemuxer.h"

namespace k3d {
namespace MPExtension {
namespace plugins {
namespace processors {
namespace mesh {

  mesh_msg_t MeshSignalDemuxer::demuxSignal(k3d::mesh& Input){
  #if 0
    if( last_mesh == &Input and
        getSignalFromMesh(Input) > last_topology_changed_id ){
      last_topology_changed_id = signal;
      return topology_changed;
    }
  #endif
    return topology_changed;
  }

  MeshSignal& MeshSignalDemuxer::getSignalFromMesh(k3d::mesh& Input){
    static MeshSignal signal=0;
    return signal;
  }

}
}
}
}
}

#endif /* SIGNALDEMUXER_H_ */
