#include "CameraInterface.hpp"
#include <iostream>

CameraInterface::CameraInterface(camera CamType) : image_(), cam_type_(CamType)
{
  if(cam_type_ == IP_CAM) {
    cap_.open(STREAM_ADDR);
  } else if(cam_type_ == LOCAL_CAM) {
    cap_.open(0);
  }
  if(!cap_.isOpened()) {
    std::cout << "Could not open camera"  << std::endl;
  }
}
const cv::Mat& CameraInterface::getImage()
{
  cap_ >> image_;

  if(cam_type_ == IP_CAM) {
    cv::resize(image_,image_,cv::Size(width_, height_));
  }
  return image_;

}
void CameraInterface::setResolution(int width, int height)
{
  width_ = width;
  height_ = height;
  cap_.set(CV_CAP_PROP_FRAME_WIDTH, width);
  cap_.set(CV_CAP_PROP_FRAME_HEIGHT, height);
}
