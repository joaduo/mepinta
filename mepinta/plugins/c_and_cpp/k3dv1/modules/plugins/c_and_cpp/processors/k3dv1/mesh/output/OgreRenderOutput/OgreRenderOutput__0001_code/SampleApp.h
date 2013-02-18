// ----------------------------------------------------------------------------
// Include the main OGRE header files
// Ogre.h just expands to including lots of individual OGRE header files
// ----------------------------------------------------------------------------
#include <Ogre.h>
// ----------------------------------------------------------------------------
// Include the OGRE example framework
// This includes the classes defined to make getting an OGRE application running
// a lot easier. It automatically sets up all the main objects and allows you to
// just override the bits you want to instead of writing it all from scratch.
// ----------------------------------------------------------------------------
#include "ExampleApp.h"
//#include <SdkTrays.h>
//#include "BaseApplication.h"

// ----------------------------------------------------------------------------
// Define the application object
// This is derived from ExampleApplication which is the class OGRE provides to
// make it easier to set up OGRE without rewriting the same code all the time.
// You can override extra methods of ExampleApplication if you want to further
// specialise the setup routine, otherwise the only mandatory override is the
// 'createScene' method which is where you set up your own personal scene.
// ----------------------------------------------------------------------------
//ExampleApplication
class SampleApp : public ExampleApp
{
public:
    // Basic constructor
    SampleApp()
    {
      mNinjaNode = NULL;
    }

    Ogre::ManualObject* getManualObject(Ogre::String object_name);

    void operationNinja(double x, double y, double z);

    void createManualObject();

    bool createOgreNode(Ogre::MeshPtr ogre_mesh_ptr);

protected:

    void createCamera(void);

    // Just override the mandatory create scene method
    void createScene(void);

    void createViewports(void);

private:
    Ogre::SceneNode* mNinjaNode;
};

