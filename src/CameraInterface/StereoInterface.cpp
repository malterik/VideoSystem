#include "StereoInterface.hpp"
#include "../Utils/Utils.hpp"

StereoInterface::StereoInterface( Camera cameraLeft, Camera cameraRight) :
  camera_interface_left_(cameraLeft.ct),
  camera_interface_right_(cameraRight.ct)
{
  camera_interface_left_.setResolution(cameraLeft.img_width, cameraLeft.img_height);
  camera_interface_right_.setResolution(cameraRight.img_width, cameraLeft.img_height);

}

cv::Mat StereoInterface::getRightImage() {
  return camera_interface_left_.getImage();
}
cv::Mat StereoInterface::getLeftImage() {
  return camera_interface_right_.getImage();
}
