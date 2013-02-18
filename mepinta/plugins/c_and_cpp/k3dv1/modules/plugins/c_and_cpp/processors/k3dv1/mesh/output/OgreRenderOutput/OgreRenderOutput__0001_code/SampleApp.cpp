
#include "SampleApp.h"

void SampleApp::operationNinja(double x, double y, double z){
//  mNinjaNode->setPosition(x,y,z);
}

Ogre::ManualObject* SampleApp::getManualObject(Ogre::String name){
  if(mSceneMgr->hasManualObject(name)){
    return mSceneMgr->getManualObject(name);
  }
  Ogre::ManualObject* manual = mSceneMgr->createManualObject(name);
  //manual->setMaterialName(0,"Examples/Rockwall");
  //manual->setMaterialName()
  mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(manual);

  return manual;
}

void SampleApp::createManualObject(){
//      ManualObject* manual = mSceneMgr->createManualObject("manual");
//      manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
//
//      manual->position(-100.0, -100.0, 0.0);  // start position
//      manual->position( 100.0, -100.0, 0.0);  // draw first line
//      manual->position( 100.0,  100.0, 0.0);
//      manual->position(-100.0,  100.0, 0.0);
//      manual->position(-100.0, -100.0, 0.0);  // draw fourth line
//
//      manual->end();
//      mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(manual);

  ManualObject* manual = mSceneMgr->createManualObject("manual");
  mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(manual);
  //manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
  //manual->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_STRIP);
  manual->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_LIST);

  // define vertex position of index 0..3
  manual->position(-100.0, -100.0, 0.0);
  manual->position( 100.0, -100.0, 0.0);
  manual->position( 100.0,  100.0, 0.0);
  manual->position(-100.0,  100.0, 0.0);

  // define usage of vertices by refering to the indexes
  manual->index(0);
  manual->index(1);
  manual->index(2);
//  manual->index(3);
//  manual->index(0);

  manual->end();

}

bool SampleApp::createOgreNode(Ogre::MeshPtr ogre_mesh_ptr){
  createManualObject();
//      Ogre::Entity* ogre_entity = mSceneMgr->createEntity(ogre_mesh_ptr);
//      //ogre_entity->setMaterialName("Examples/Rockwall");
//      Ogre::SceneNode* k3d_mesh = mSceneMgr->getRootSceneNode()->createChildSceneNode("K3dMesh");
//      k3d_mesh->attachObject(ogre_entity);

//  Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
//  //ogreHead
//  ogreHead->setMaterialName("Examples/Rockwall");

  // Create a SceneNode and attach the Entity to it
//  mNinjaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
//  mNinjaNode->attachObject(ogreHead);
//  mNinjaNode->setPosition(0.,0.,0.);
  return true;
}

void SampleApp::createCamera(void)
{
    // create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
    // set its position, direction
    mCamera->setPosition(Ogre::Vector3(0,10,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    // set the near clip distance
    mCamera->setNearClipDistance(5);

    //mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

// Just override the mandatory create scene method
void SampleApp::createScene(void)
{
    mSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox");
}

void SampleApp::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

