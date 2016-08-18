#include "Utils/DisableWarnings.hpp"
#include "ImageViewer/ImageViewer.hpp"
#include "Utils/print.hpp"

int main(void)
{
  // Initialize Cameras
  CameraType camtypeL = DLINK_CAM_2;
  Camera camL;
  camL.ct = camtypeL;
  camL.img_width = 640;
  camL.img_height = 480;
  CameraType camtypeR = DLINK_CAM_1;
  Camera camR;
  camR.ct = camtypeR;
  camR.img_width = 640;
  camR.img_height = 480;

  //Image Viewer Instantiation
  ImageViewer iv("Main Window", camL, camR);
  iv.snapshots(BOTH);
  while(1) {}
}
