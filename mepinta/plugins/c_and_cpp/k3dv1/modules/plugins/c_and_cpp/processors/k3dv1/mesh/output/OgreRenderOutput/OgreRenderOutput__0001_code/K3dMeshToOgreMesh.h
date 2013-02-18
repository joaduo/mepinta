
#include <mepintasdk/sdk.h>

#include <Ogre.h>
#include <algorithm>
#include <vector>

#include <k3dsdk/polyhedron.h>
#include <k3dsdk/triangulator.h>

class paint_triangles :
        public k3d::triangulator
{
public:
  Ogre::ManualObject* manual_object;
  paint_triangles(Ogre::ManualObject* manual_object, const k3d::mesh::points_t& Points, const k3d::mesh::selection_t& FaceSelections, const k3d::color& Color, const k3d::color& SelectedColor)
  :
  manual_object(manual_object)
  {
  }

  void add_triangle(k3d::uint_t Vertices[3], k3d::uint_t Edges[3])
  {
    log_debug("add_triangle %p \n",Vertices);
    manual_object->index(Vertices[0]);
    manual_object->index(Vertices[1]);
    manual_object->index(Vertices[2]);
  }
};

class K3dMeshToOgreMesh
{
public:
  // Basic constructor
  K3dMeshToOgreMesh()
  {

  }

  void convertMesh(const k3d::mesh& Mesh, Ogre::ManualObject* manual_object)
  {
    manual_object->clear();
    for(k3d::mesh::primitives_t::const_iterator primitive = Mesh.primitives.begin(); primitive != Mesh.primitives.end(); ++primitive)
    {
      boost::scoped_ptr<k3d::polyhedron::const_primitive> polyhedron(k3d::polyhedron::validate(Mesh, **primitive));
      if(!polyhedron.get())
              continue;

      if(k3d::polyhedron::is_sds(*polyhedron))
              continue;

      const k3d::color color(.7,.7,.7);
      const k3d::color selected_color(.7,0.,0.);

      paint_triangles painter(manual_object, *Mesh.points, polyhedron->face_selections, color, selected_color);

      manual_object->begin("Examples/Rockwall", Ogre::RenderOperation::OT_TRIANGLE_LIST);
      const k3d::mesh::points_t& InputPoints = *Mesh.points.get();
      const k3d::uint_t point_begin = 0;
      const k3d::uint_t point_end = point_begin + InputPoints.size();
      for(k3d::uint_t point_i = point_begin; point_i != point_end; ++point_i)
      {
        const k3d::point3& point = InputPoints[point_i];
        manual_object->position(point.n[0],point.n[1],point.n[2]);
      }
      painter.process(Mesh, *polyhedron);
      manual_object->end();
    }
  }

};

