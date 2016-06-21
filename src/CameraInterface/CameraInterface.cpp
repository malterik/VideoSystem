#include "CameraInterface.hpp"
#include <iostream>
#include "../Utils/print.hpp"

CameraInterface::CameraInterface(CameraType CamType) : image_(), cam_type_(CamType)
{
  if(cam_type_ == IP_CAM1) {
    print(LogLevel::DEBUG, "IP_CAM1");
    cap_.open(STREAM_ADDR1);
  } else if(cam_type_ == IP_CAM2) {
    print(LogLevel::DEBUG, "IP_CAM2");
    cap_.open(STREAM_ADDR2);
  } else if(cam_type_ == LOCAL_CAM) {
    cap_.open(0);
  } else if(cam_type_ == DLINK_CAM) {
    cap_.open(DLINK_STREAM_ADDR);
  }
  if(!cap_.isOpened()) {
    std::cout << "Could not open camera"  << std::endl;
  }
}
const cv::Mat& CameraInterface::getImage()
{
  cap_ >> image_;

  if(cam_type_ == IP_CAM1 || cam_type_ == IP_CAM2) {
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
void CameraInterface::reset(CameraType cameraToUse) {
  cam_type_ = cameraToUse;
  if(cam_type_ == IP_CAM1) {
    cap_.open(STREAM_ADDR1);
  } else if(cam_type_ == IP_CAM2) {
    cap_.open(STREAM_ADDR2);
  } else if(cam_type_ == LOCAL_CAM) {
    cap_.open(0);
  } else if(cam_type_ == DLINK_CAM) {
    cap_.open(DLINK_STREAM_ADDR);
  }
  if(cap_.isOpened()) {
    cap_.release();
  }
  if(!cap_.isOpened()) {
    std::cout << "Could not open camera"  << std::endl;
  }
}
