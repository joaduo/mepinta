/*
 * MeshSignal.h
 *
 *  Created on: Aug 7, 2012
 *      Author: jduo
 */

#ifndef MESHSIGNAL_H_
#define MESHSIGNAL_H_

namespace k3d {
namespace MPExtension {
namespace plugins {
namespace processors {
namespace mesh {

  typedef enum{
    topology_changed,
    geometry_changed
  } mesh_msg_t;

  typedef int MeshSignal;

}
}
}
}
}

#endif /* MESHSIGNAL_H_ */
