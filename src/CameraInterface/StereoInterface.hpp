#include "CameraInterface.hpp"
class StereoInterface
{
public:
  StereoInterface(Camera cameraLeft, Camera cameraRight);
  cv::Mat getRightImage();
  cv::Mat getLeftImage();

private:
  CameraInterface camera_interface_left_;
  CameraInterface camera_interface_right_;
};
